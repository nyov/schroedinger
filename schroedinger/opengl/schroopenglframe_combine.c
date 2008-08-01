
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <schroedinger/schro.h>
#include <schroedinger/opengl/schroopengl.h>
#include <schroedinger/opengl/schroopenglcanvas.h>
#include <schroedinger/opengl/schroopenglframe.h>
#include <schroedinger/opengl/schroopenglshader.h>
#include <liboil/liboil.h>

typedef void (*SchroOpenGLFrameBinaryFunc) (SchroFrame *dest, SchroFrame *src);

struct FormatToFunction {
  SchroFrameFormat dest;
  SchroFrameFormat src;
  SchroOpenGLFrameBinaryFunc func;
};

static void schro_opengl_frame_add_s16_u8 (SchroFrame *dest,
    SchroFrame *src);
static void schro_opengl_frame_add_s16_s16 (SchroFrame *dest,
    SchroFrame *src);

static struct FormatToFunction schro_opengl_frame_add_func_list[] = {
  /* U8 -> S16 */
  { SCHRO_FRAME_FORMAT_S16_444, SCHRO_FRAME_FORMAT_U8_444,
      schro_opengl_frame_add_s16_u8 },
  { SCHRO_FRAME_FORMAT_S16_422, SCHRO_FRAME_FORMAT_U8_422,
      schro_opengl_frame_add_s16_u8 },
  { SCHRO_FRAME_FORMAT_S16_420, SCHRO_FRAME_FORMAT_U8_420,
      schro_opengl_frame_add_s16_u8 },

  /* S16 -> S16 */
  { SCHRO_FRAME_FORMAT_S16_444, SCHRO_FRAME_FORMAT_S16_444,
      schro_opengl_frame_add_s16_s16 },
  { SCHRO_FRAME_FORMAT_S16_422, SCHRO_FRAME_FORMAT_S16_422,
      schro_opengl_frame_add_s16_s16 },
  { SCHRO_FRAME_FORMAT_S16_420, SCHRO_FRAME_FORMAT_S16_420,
      schro_opengl_frame_add_s16_s16 },

  { 0, 0, NULL }
};

void
schro_opengl_frame_add (SchroFrame *dest, SchroFrame *src)
{
  int i;

  SCHRO_ASSERT (dest != NULL);
  SCHRO_ASSERT (src != NULL);
  SCHRO_ASSERT (SCHRO_FRAME_IS_OPENGL (dest));
  SCHRO_ASSERT (SCHRO_FRAME_IS_OPENGL (src));

  for (i = 0; schro_opengl_frame_add_func_list[i].func; ++i) {
    if (schro_opengl_frame_add_func_list[i].dest == dest->format
        && schro_opengl_frame_add_func_list[i].src == src->format) {
      schro_opengl_frame_add_func_list[i].func (dest, src);
      return;
    }
  }

  SCHRO_ERROR ("addition unimplemented (%d -> %d)", src->format,
      dest->format);
  SCHRO_ASSERT (0);
}

static void schro_opengl_frame_subtract_s16_u8 (SchroFrame *dest,
    SchroFrame *src);
static void schro_opengl_frame_subtract_s16_s16 (SchroFrame *dest,
    SchroFrame *src);

static struct FormatToFunction schro_opengl_frame_subtract_func_list[] = {
  /* U8 -> S16 */
  { SCHRO_FRAME_FORMAT_S16_444, SCHRO_FRAME_FORMAT_U8_444,
      schro_opengl_frame_subtract_s16_u8 },
  { SCHRO_FRAME_FORMAT_S16_422, SCHRO_FRAME_FORMAT_U8_422,
      schro_opengl_frame_subtract_s16_u8 },
  { SCHRO_FRAME_FORMAT_S16_420, SCHRO_FRAME_FORMAT_U8_420,
      schro_opengl_frame_subtract_s16_u8 },

  /* S16 -> S16 */
  { SCHRO_FRAME_FORMAT_S16_444, SCHRO_FRAME_FORMAT_S16_444,
      schro_opengl_frame_subtract_s16_s16 },
  { SCHRO_FRAME_FORMAT_S16_422, SCHRO_FRAME_FORMAT_S16_422,
      schro_opengl_frame_subtract_s16_s16 },
  { SCHRO_FRAME_FORMAT_S16_420, SCHRO_FRAME_FORMAT_S16_420,
      schro_opengl_frame_subtract_s16_s16 },

  { 0, 0, NULL }
};

void
schro_opengl_frame_subtract (SchroFrame *dest, SchroFrame *src)
{
  int i;

  SCHRO_ASSERT (dest != NULL);
  SCHRO_ASSERT (src != NULL);
  SCHRO_ASSERT (SCHRO_FRAME_IS_OPENGL (dest));
  SCHRO_ASSERT (SCHRO_FRAME_IS_OPENGL (src));

  for (i = 0; schro_opengl_frame_subtract_func_list[i].func; ++i) {
    if (schro_opengl_frame_subtract_func_list[i].dest == dest->format
        && schro_opengl_frame_subtract_func_list[i].src == src->format) {
      schro_opengl_frame_subtract_func_list[i].func (dest, src);
      return;
    }
  }

  SCHRO_ERROR ("subtraction unimplemented (%d -> %d)", src->format,
      dest->format);
  SCHRO_ASSERT (0);
}

static void
schro_opengl_frame_combine_with_shader (SchroFrame *dest, SchroFrame *src,
    int shader_index)
{
  int i;
  int width, height;
  SchroOpenGLCanvas *dest_canvas = NULL;
  SchroOpenGLCanvas *src_canvas = NULL;
  SchroOpenGLShader *shader_copy_u8;
  SchroOpenGLShader *shader_copy_s16;
  SchroOpenGLShader *shader_combine;

  SCHRO_ASSERT (dest != NULL);
  SCHRO_ASSERT (src != NULL);
  SCHRO_ASSERT (SCHRO_FRAME_IS_OPENGL (dest));
  SCHRO_ASSERT (SCHRO_FRAME_IS_OPENGL (src));

  dest_canvas = SCHRO_OPNEGL_CANVAS_FROM_FRAMEDATA (dest->components + 0);
  src_canvas = SCHRO_OPNEGL_CANVAS_FROM_FRAMEDATA (src->components + 0);

  SCHRO_ASSERT (dest_canvas != NULL);
  SCHRO_ASSERT (src_canvas != NULL);
  SCHRO_ASSERT (dest_canvas->opengl == src_canvas->opengl);

  schro_opengl_lock_context (src_canvas->opengl);

  shader_copy_u8 = schro_opengl_shader_get (src_canvas->opengl,
      SCHRO_OPENGL_SHADER_COPY_U8);
  shader_copy_s16 = schro_opengl_shader_get (src_canvas->opengl,
      SCHRO_OPENGL_SHADER_COPY_S16);
  shader_combine = schro_opengl_shader_get (src_canvas->opengl, shader_index);

  SCHRO_ASSERT (shader_copy_u8);
  SCHRO_ASSERT (shader_copy_s16);
  SCHRO_ASSERT (shader_combine);

  for (i = 0; i < 3; ++i) {
    dest_canvas = SCHRO_OPNEGL_CANVAS_FROM_FRAMEDATA (dest->components + i);
    src_canvas = SCHRO_OPNEGL_CANVAS_FROM_FRAMEDATA (src->components + i);

    SCHRO_ASSERT (dest_canvas != NULL);
    SCHRO_ASSERT (src_canvas != NULL);

    width = MIN (dest->components[i].width, src->components[i].width);
    height = MIN (dest->components[i].height, src->components[i].height);

    schro_opengl_setup_viewport (width, height);

    glBindFramebufferEXT (GL_FRAMEBUFFER_EXT,
        dest_canvas->secondary->framebuffer);
    glBindTexture (GL_TEXTURE_RECTANGLE_ARB, dest_canvas->texture);

    switch (SCHRO_FRAME_FORMAT_DEPTH (dest_canvas->format)) {
      case SCHRO_FRAME_FORMAT_DEPTH_U8:
        glUseProgramObjectARB (shader_copy_u8->program);
        break;
      case SCHRO_FRAME_FORMAT_DEPTH_S16:
        glUseProgramObjectARB (shader_copy_s16->program);
        break;
      default:
        SCHRO_ASSERT (0);
        break;
    }

    schro_opengl_render_quad (0, 0, width, height);

    SCHRO_OPENGL_CHECK_ERROR

    glFlush ();

    glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, dest_canvas->framebuffer);

    glUseProgramObjectARB (shader_combine->program);

    glBindTexture (GL_TEXTURE_RECTANGLE_ARB, dest_canvas->secondary->texture);

    glActiveTextureARB (GL_TEXTURE1_ARB);
    glBindTexture (GL_TEXTURE_RECTANGLE_ARB, src_canvas->texture);

    glActiveTextureARB (GL_TEXTURE0_ARB);

    schro_opengl_render_quad (0, 0, width, height);

    glUseProgramObjectARB (0);

    SCHRO_OPENGL_CHECK_ERROR

    glFlush ();
  }

#if SCHRO_OPENGL_UNBIND_TEXTURES
  glBindTexture (GL_TEXTURE_RECTANGLE_ARB, 0);
  glActiveTextureARB (GL_TEXTURE1_ARB);
  glBindTexture (GL_TEXTURE_RECTANGLE_ARB, 0);
  glActiveTextureARB (GL_TEXTURE0_ARB);
#endif
  glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, 0);

  schro_opengl_unlock_context (src_canvas->opengl);
}

static void
schro_opengl_frame_add_s16_u8 (SchroFrame *dest, SchroFrame *src)
{
  schro_opengl_frame_combine_with_shader (dest, src,
      SCHRO_OPENGL_SHADER_ADD_S16_U8);
}

static void
schro_opengl_frame_add_s16_s16 (SchroFrame *dest, SchroFrame *src)
{
  schro_opengl_frame_combine_with_shader (dest, src,
      SCHRO_OPENGL_SHADER_ADD_S16_S16);
}

static void
schro_opengl_frame_subtract_s16_u8 (SchroFrame *dest, SchroFrame *src)
{
  schro_opengl_frame_combine_with_shader (dest, src,
      SCHRO_OPENGL_SHADER_SUBTRACT_S16_U8);
}

static void
schro_opengl_frame_subtract_s16_s16 (SchroFrame *dest, SchroFrame *src)
{
  schro_opengl_frame_combine_with_shader (dest, src,
      SCHRO_OPENGL_SHADER_SUBTRACT_S16_S16);
}

