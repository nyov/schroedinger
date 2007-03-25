
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <schroedinger/schro.h>
#include <schroedinger/schromotion.h>
#include <schroedinger/schrodebug.h>
#include <schroedinger/schroutils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <liboil/liboilrandom.h>

void
schro_frame_clear (SchroFrame *frame)
{
  memset(frame->components[0].data, 0, frame->components[0].length);
  memset(frame->components[1].data, 0, frame->components[1].length);
  memset(frame->components[2].data, 0, frame->components[2].length);
}

void
schro_frame_create_pattern (SchroFrame *frame, int type)
{
  int i,j,k;
  SchroFrameComponent *comp;

  switch (type) {
    case 0:
      oil_random_u8 (frame->components[0].data, frame->components[0].length);
      oil_random_u8 (frame->components[1].data, frame->components[1].length);
      oil_random_u8 (frame->components[2].data, frame->components[2].length);
      break;
    case 1:
      for(k=0;k<3;k++){
        comp = &frame->components[k];
        for(j=0;j<comp->height;j++){
          for(i=0;i<comp->width;i++){
            SCHRO_GET(comp->data, j*comp->stride + i, uint8_t) = i*4 + j*2;
          }
        }
      }

      break;
  }
}

int
schro_frame_compare (SchroFrame *a, SchroFrame *b)
{
  SchroFrameComponent *comp_a;
  SchroFrameComponent *comp_b;
  int k;
  int i,j;

  for(k=0;k<3;k++){
    comp_a = &a->components[k];
    comp_b = &b->components[k];
    for(j=0;j<comp_a->height;j++){
      for(i=0;i<comp_a->width;i++){
        if (SCHRO_GET(comp_a->data, j*comp_a->stride + i, uint8_t) !=
            SCHRO_GET(comp_b->data, j*comp_b->stride + i, uint8_t)) {
          SCHRO_ERROR("difference comp=%d x=%d y=%d", k, i, j);
          return FALSE;
        }
      }
    }
  }

  return TRUE;
}

void
schro_frame_dump (SchroFrame *frame)
{
  SchroFrameComponent *comp;
  int i,j;

  comp = &frame->components[0];
  for(j=0;j<20;j++){
    for(i=0;i<20;i++) {
      printf("%-3d ", SCHRO_GET(comp->data, j*comp->stride + i, uint8_t));
    }
    printf("\n");
  }
}

int
main (int argc, char *argv[])
{
  SchroFrame *dest;
  SchroFrame *dest_u8;
  SchroFrame *ref;
  SchroParams params;
  SchroVideoFormat video_format;
  SchroMotionVector *motion_vectors;
  int i,j;

  schro_init();

  video_format.width = 720;
  video_format.height = 480;
  video_format.chroma_format = SCHRO_CHROMA_420;
  schro_params_validate (&video_format);

  params.video_format = &video_format;
  params.xbsep_luma = 8;
  params.ybsep_luma = 8;
  params.xblen_luma = 12;
  params.yblen_luma = 12;

  schro_params_calculate_mc_sizes(&params);

  dest = schro_frame_new_and_alloc2 (SCHRO_FRAME_FORMAT_S16,
      params.mc_luma_width, params.mc_luma_height,
      params.mc_chroma_width, params.mc_chroma_height);
  ref = schro_frame_new_and_alloc2 (SCHRO_FRAME_FORMAT_U8,
      video_format.width, video_format.height,
      (video_format.width + 1)/2, (video_format.height + 1)/2);
  dest_u8 = schro_frame_new_and_alloc2 (SCHRO_FRAME_FORMAT_U8,
      video_format.width, video_format.height,
      (video_format.width + 1)/2, (video_format.height + 1)/2);

  schro_frame_clear(dest);
  schro_frame_create_pattern(ref,1);

  motion_vectors = malloc(sizeof(SchroMotionVector) *
      params.x_num_blocks * params.y_num_blocks);
  memset (motion_vectors, 0, sizeof(SchroMotionVector) *
      params.x_num_blocks * params.y_num_blocks);
  
  printf("sizeof(SchroMotionVector) = %lu\n",(unsigned long) sizeof(SchroMotionVector));
  printf("num blocks %d x %d\n", params.x_num_blocks, params.y_num_blocks);
  for(j=0;j<params.y_num_blocks;j++){
    int jj;
    jj = j * params.x_num_blocks;
    for(i=0;i<params.x_num_blocks;i++){
#if 0
      if (i == 0 || i == 2 || i == params.x_num_blocks*2) {
        motion_vectors[jj+i].u.dc[0] = 100;
        motion_vectors[jj+i].u.dc[1] = 100;
        motion_vectors[jj+i].u.dc[2] = 0;
        motion_vectors[jj+i].pred_mode = 0;
      } else {
        motion_vectors[jj+i].u.dc[0] = 0;
        motion_vectors[jj+i].u.dc[1] = 0;
        motion_vectors[jj+i].u.dc[2] = 0;
        motion_vectors[jj+i].pred_mode = 0;
      }
#endif
      motion_vectors[jj+i].u.xy.x = 0;
      motion_vectors[jj+i].u.xy.y = -8*i;
      motion_vectors[jj+i].pred_mode = 1;
      motion_vectors[jj+i].split = 2;
    }
  }

  {
    SchroMotion motion;

    motion.src1[0] = ref;
    motion.src1[1] = schro_frame_new_and_alloc2 (SCHRO_FRAME_FORMAT_U8,
        video_format.width, video_format.height,
        (video_format.width + 1)/2, (video_format.height + 1)/2);
    schro_frame_h_upsample (motion.src1[1], ref);
    motion.src1[2] = schro_frame_new_and_alloc2 (SCHRO_FRAME_FORMAT_U8,
        video_format.width, video_format.height,
        (video_format.width + 1)/2, (video_format.height + 1)/2);
    schro_frame_v_upsample (motion.src1[2], ref);
    motion.src1[3] = schro_frame_new_and_alloc2 (SCHRO_FRAME_FORMAT_U8,
        video_format.width, video_format.height,
        (video_format.width + 1)/2, (video_format.height + 1)/2);
    schro_frame_v_upsample (motion.src1[3], motion.src1[1]);
    motion.src2[0] = NULL;
    motion.src2[1] = NULL;
    motion.src2[2] = NULL;
    motion.src2[3] = NULL;
    motion.motion_vectors = motion_vectors;
    motion.params = &params;
    schro_frame_copy_with_motion (dest, &motion);
  }

  schro_frame_convert (dest_u8, dest);
  schro_frame_dump (dest_u8);
  //schro_frame_compare (ref, dest_u8);

  schro_frame_free (ref);
  schro_frame_free (dest);
  free (motion_vectors);

  return 0;
}

