
#ifndef __SCHRO_PARAMS_H__
#define __SCHRO_PARAMS_H__

#include <schroedinger/schrobitstream.h>
#include <schroedinger/schroframe.h>
#include <schroedinger/schrolimits.h>
#include <schroedinger/schro-stdint.h>
#include <schroedinger/schrovideoformat.h>

SCHRO_BEGIN_DECLS

typedef struct _SchroParams SchroParams;
typedef struct _SchroGlobalMotion SchroGlobalMotion;

#ifdef SCHRO_ENABLE_UNSTABLE_API

struct _SchroGlobalMotion {
  int shift;
  int b0;
  int b1;
  int a_exp;
  int a00;
  int a01;
  int a10;
  int a11;
  int c_exp;
  int c0;
  int c1;
};

struct _SchroParams {
  /*< private >*/
  SchroVideoFormat *video_format;
  int is_noarith;

  /* transform parameters */
  int wavelet_filter_index;
  int transform_depth;
  int spatial_partition_flag;
  int nondefault_partition_flag;
  int horiz_codeblocks[SCHRO_LIMIT_TRANSFORM_DEPTH + 1];
  int vert_codeblocks[SCHRO_LIMIT_TRANSFORM_DEPTH + 1];
  int codeblock_mode_index;

  /* motion prediction parameters */
  int num_refs;
  int have_global_motion;
  int xblen_luma;
  int yblen_luma;
  int xbsep_luma;
  int ybsep_luma;
  int mv_precision;
  SchroGlobalMotion global_motion[2];
  int picture_pred_mode;
  int picture_weight_bits;
  int picture_weight_1;
  int picture_weight_2;

  /* DiracPro parameters */
  int is_lowdelay;
  int slice_width_exp;
  int slice_height_exp;
  int slice_bytes_num;
  int slice_bytes_denom;
  int quant_matrix[3*SCHRO_LIMIT_TRANSFORM_DEPTH+1];
  int luma_quant_offset;
  int chroma1_quant_offset;
  int chroma2_quant_offset;

  /* calculated sizes */
  int iwt_chroma_width;
  int iwt_chroma_height;
  int iwt_luma_width;
  int iwt_luma_height;
  int mc_chroma_width;
  int mc_chroma_height;
  int mc_luma_width;
  int mc_luma_height;
  int x_num_blocks;
  int y_num_blocks;
};

#define SCHRO_SUBBAND_IS_HORIZONTALLY_ORIENTED(position) (((position)&3) == 2)
#define SCHRO_SUBBAND_IS_VERTICALLY_ORIENTED(position) (((position)&3) == 1)
#define SCHRO_SUBBAND_SHIFT(position) ((position)>>2)

extern const int16_t schro_zero[];
extern const int schro_tables_lowdelay_quants[7][4][9];

void schro_params_init (SchroParams *params, int video_format);

void schro_params_calculate_iwt_sizes (SchroParams *params);
void schro_params_calculate_mc_sizes (SchroParams *params);

void schro_params_set_block_params (SchroParams *params, int index);
int schro_params_get_block_params (SchroParams *params);

void schro_params_set_default_codeblock (SchroParams *params);

void schro_subband_get_frame_data (SchroFrameData *dest,
    SchroFrame *frame, int component, int position, SchroParams *params);
void schro_subband_get (SchroFrame *frame, int component, int position,
    SchroParams *params, int16_t **data, int *stride, int *width, int *height);
int schro_subband_get_position (int index);

/* FIXME should be SchroFrameFormat */
int schro_params_get_frame_format (int depth,
    SchroChromaFormat chroma_format);

/* FIXME should be moved */
void schro_frame_iwt_transform (SchroFrame *frame, SchroParams *params,
    int16_t *tmp);
void schro_frame_inverse_iwt_transform (SchroFrame *frame, SchroParams *params,
    int16_t *tmp);
void schro_params_init_lowdelay_quantisers (SchroParams *params);

#endif

SCHRO_END_DECLS

#endif

