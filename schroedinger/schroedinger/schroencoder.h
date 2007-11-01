
#ifndef __SCHRO_ENCODER_H__
#define __SCHRO_ENCODER_H__

#include <schroedinger/schroutils.h>
#include <schroedinger/schropack.h>
#include <schroedinger/schrobuffer.h>
#include <schroedinger/schroparams.h>
#include <schroedinger/schroframe.h>
#include <schroedinger/schroasync.h>
#include <schroedinger/schroqueue.h>
#include <schroedinger/schromotion.h>
#include <schroedinger/schrohistogram.h>
#include <schroedinger/schrolist.h>

SCHRO_BEGIN_DECLS

typedef struct _SchroEncoder SchroEncoder;
typedef struct _SchroEncoderParams SchroEncoderParams;
typedef struct _SchroEncoderFrame SchroEncoderFrame;

/* forward reference */
typedef struct _SchroPredictionVector SchroPredictionVector;
typedef struct _SchroPredictionList SchroPredictionList;

typedef enum {
  SCHRO_PREF_ENGINE,
  SCHRO_PREF_QUANT_ENGINE,
  SCHRO_PREF_REF_DISTANCE,
  SCHRO_PREF_TRANSFORM_DEPTH,
  SCHRO_PREF_INTRA_WAVELET,
  SCHRO_PREF_INTER_WAVELET,
  SCHRO_PREF_LAMBDA,
  SCHRO_PREF_PSNR,
  SCHRO_PREF_BITRATE,
  SCHRO_PREF_NOARITH,
  SCHRO_PREF_MD5,
  SCHRO_PREF_LAST
} SchroPrefEnum;

typedef enum {
  SCHRO_STATE_NEED_FRAME,
  SCHRO_STATE_HAVE_BUFFER,
  SCHRO_STATE_AGAIN,
  SCHRO_STATE_END_OF_STREAM
} SchroStateEnum;

typedef enum {
  SCHRO_ENCODER_FRAME_STATE_NEW,
  SCHRO_ENCODER_FRAME_STATE_INITED,
  SCHRO_ENCODER_FRAME_STATE_ANALYSE,
  SCHRO_ENCODER_FRAME_STATE_PREDICT,
  SCHRO_ENCODER_FRAME_STATE_ENCODING,
  SCHRO_ENCODER_FRAME_STATE_RECONSTRUCT,
  SCHRO_ENCODER_FRAME_STATE_POSTANALYSE,
  SCHRO_ENCODER_FRAME_STATE_DONE,
  SCHRO_ENCODER_FRAME_STATE_ENGINE_1,
  SCHRO_ENCODER_FRAME_STATE_FREE
} SchroEncoderFrameStateEnum;

typedef enum {
  SCHRO_ENCODER_PERCEPTUAL_CONSTANT,
  SCHRO_ENCODER_PERCEPTUAL_CCIR959,
  SCHRO_ENCODER_PERCEPTUAL_MOO
} SchroEncoderPerceptualEnum;

struct _SchroEncoderParams {
  int ignore;
};

#ifdef SCHRO_ENABLE_UNSTABLE_API
struct _SchroEncoderFrame {
  /*< private >*/
  int refcount;
  SchroEncoderFrameStateEnum state;
  int busy;

  /* Bits telling the engine stages which stuff needs to happen */
  unsigned int need_downsampling;
  unsigned int need_filtering;
  unsigned int need_average_luma;

  /* bits indicating that a particular analysis has happened.  Mainly
   * for verification */
  unsigned int have_estimate_tables;
  unsigned int have_histograms;
  unsigned int have_scene_change_score;
  unsigned int have_downsampling;
  unsigned int have_average_luma;

  /* other stuff */

  int start_access_unit;

  SchroPictureNumber frame_number;
  SchroFrame *original_frame;
  SchroFrame *filtered_frame;
  SchroFrame *downsampled_frames[5];
  SchroUpsampledFrame *reconstructed_frame;

  SchroBuffer *access_unit_buffer;
  SchroList *inserted_buffers;
  int output_buffer_size;
  SchroBuffer *output_buffer;
  int presentation_frame;
  int slot;
  int last_frame;

  int is_ref;
  int num_refs;
  SchroPictureNumber picture_number_ref0;
  SchroPictureNumber picture_number_ref1;
  int n_retire;
  SchroPictureNumber retire[SCHRO_LIMIT_REFERENCE_FRAMES];

  int16_t slice_y_dc_values[100];
  int16_t slice_u_dc_values[100];
  int16_t slice_v_dc_values[100];
  int slice_y_n;
  int slice_uv_n;
  int slice_y_bits;
  int slice_uv_bits;
  int slice_y_trailing_zeros;
  int slice_uv_trailing_zeros;

  /* from the old SchroEncoderTask */

  int stats_dc;
  int stats_global;
  int stats_motion;

  int estimated_entropy;

  int subband_size;
  SchroBuffer *subband_buffer;

  int16_t *quant_data;

  int16_t *tmpbuf;
  int16_t *tmpbuf2;

  int quant_index[3][1+SCHRO_LIMIT_TRANSFORM_DEPTH*3];
  double est_entropy[3][1+SCHRO_LIMIT_TRANSFORM_DEPTH*3][60];
  double est_error[3][1+SCHRO_LIMIT_TRANSFORM_DEPTH*3][60];
  double subband_info[3][1+SCHRO_LIMIT_TRANSFORM_DEPTH*3];
  SchroPack *pack;
  SchroParams params;
  SchroEncoder *encoder;
  SchroFrame *iwt_frame;
  SchroFrame *prediction_frame;

  SchroEncoderFrame *ref_frame0;
  SchroEncoderFrame *ref_frame1;

  SchroMotionField *motion_field;
  SchroMotionField *motion_fields[32];

  SchroHistogram subband_hists[3][SCHRO_LIMIT_SUBBANDS];
  SchroHistogram hist_test;

  int allocated_bits;
  double allocation_modifier;
  int actual_bits;
  int actual_mc_bits;
  double average_luma;

  double scene_change_score;

  double base_lambda;
};

struct _SchroEncoder {
  /*< private >*/
  SchroAsync *async;

  SchroPictureNumber next_frame_number;

  SchroQueue *frame_queue;

  SchroQueue *reference_queue;

  int need_rap;

  int version_major;
  int version_minor;
  int profile;
  int level;

  SchroVideoFormat video_format;
  SchroEncoderParams encoder_params;

  int end_of_stream;
  int end_of_stream_handled;
  int end_of_stream_pulled;
  int completed_eos;
  int prev_offset;

  SchroPictureNumber au_frame;
  int au_distance;
  int next_slot;

  int output_slot;

  SchroList *inserted_buffers;
  int queue_depth;
  int queue_changed;

  int engine_init;
  int engine;
  int quantiser_engine;

  int prefs[SCHRO_PREF_LAST];

  /* configuration flags */
  schro_bool internal_testing;
  schro_bool calculate_psnr;
  schro_bool calculate_ssim;
  schro_bool enable_filtering;

  double pixels_per_degree_horiz;
  double pixels_per_degree_vert;
  double pixels_per_degree_diag;

  double subband_weights[SCHRO_N_WAVELETS][SCHRO_LIMIT_TRANSFORM_DEPTH][SCHRO_LIMIT_SUBBANDS];

  int buffer_size;
  int buffer_level;
  int bits_per_picture;

  /* statistics */

  double average_psnr;
  double average_arith_context_ratio;

  /* engine specific stuff */

  int gop_picture;

  int last_ref;
  int ref_distance;
  int next_ref;
  int mid1_ref;
  int mid2_ref;
};
#endif

struct _SchroEncoderSettings {
  int transform_depth;
  int wavelet_filter_index;

  /* stuff we don't handle yet */
  int profile;
  int level;

  int xbsep_luma;
  int ybsep_luma;
  int xblen_luma;
  int yblen_luma;
};

enum {
  SCHRO_MOTION_FIELD_HIER_REF0,
  SCHRO_MOTION_FIELD_HIER1_REF0,
  SCHRO_MOTION_FIELD_HIER2_REF0,
  SCHRO_MOTION_FIELD_HIER3_REF0,
  SCHRO_MOTION_FIELD_HIER_REF1,
  SCHRO_MOTION_FIELD_HIER1_REF1,
  SCHRO_MOTION_FIELD_HIER2_REF1,
  SCHRO_MOTION_FIELD_HIER3_REF1,
  SCHRO_MOTION_FIELD_PHASECORR_REF0,
  SCHRO_MOTION_FIELD_PHASECORR_REF1,
  SCHRO_MOTION_FIELD_DC,
  SCHRO_MOTION_FIELD_GLOBAL_REF0,
  SCHRO_MOTION_FIELD_GLOBAL_REF1,
  SCHRO_MOTION_FIELD_ZERO_REF0,
  SCHRO_MOTION_FIELD_ZERO_REF1,
  SCHRO_MOTION_FIELD_LAST
};

SchroEncoder * schro_encoder_new (void);
void schro_encoder_free (SchroEncoder *encoder);
SchroVideoFormat * schro_encoder_get_video_format (SchroEncoder *encoder);
void schro_encoder_set_video_format (SchroEncoder *encoder,
    SchroVideoFormat *video_format);
void schro_encoder_end_of_stream (SchroEncoder *encoder);
int schro_encoder_push_ready (SchroEncoder *encoder);
void schro_encoder_push_frame (SchroEncoder *encoder, SchroFrame *frame);

SchroBuffer * schro_encoder_encode_auxiliary_data (SchroEncoder *encoder,
    SchroAuxiliaryDataID id, void *data, int size);
void schro_encoder_copy_to_frame_buffer (SchroEncoder *encoder, SchroBuffer *buffer);
void schro_encoder_encode_access_unit_header (SchroEncoder *encoder, SchroPack *bits);
void schro_encoder_encode_parse_info (SchroPack *bits, int parse_code);
void schro_encoder_insert_buffer (SchroEncoder *encoder, SchroBuffer *buffer);
void schro_encoder_frame_insert_buffer (SchroEncoderFrame *frame, SchroBuffer *buffer);
void schro_encoder_start (SchroEncoder *encoder);

int schro_encoder_preference_get_range (SchroEncoder *encoder,
    SchroPrefEnum pref, int *min, int *max);
int schro_encoder_preference_get (SchroEncoder *encoder, SchroPrefEnum pref);
int schro_encoder_preference_set (SchroEncoder *encoder, SchroPrefEnum pref,
    int value);

SchroStateEnum schro_encoder_wait (SchroEncoder *encoder);
SchroBuffer * schro_encoder_pull (SchroEncoder *encoder,
    int *n_decodable_frames);

#ifdef SCHRO_ENABLE_UNSTABLE_API

void schro_encoder_set_default_subband_weights (SchroEncoder *encoder);
void schro_encoder_calculate_subband_weights (SchroEncoder *encoder,
        double (*perceptual_weight)(double));
void schro_encoder_use_perceptual_weighting (SchroEncoder *encoder,
    SchroEncoderPerceptualEnum type, double dist);
double schro_encoder_perceptual_weight_constant (double ppd);
double schro_encoder_perceptual_weight_ccir959 (double ppd);
double schro_encoder_perceptual_weight_moo (double ppd);

void schro_encoder_init_subbands (SchroEncoderFrame *frame);
void schro_encoder_encode_subband (SchroEncoderFrame *frame, int component, int index);
void schro_encoder_encode_subband_noarith (SchroEncoderFrame *frame, int component, int index);

void schro_encoder_analyse_picture (SchroEncoderFrame *frame);
void schro_encoder_predict_picture (SchroEncoderFrame *frame);
void schro_encoder_encode_picture (SchroEncoderFrame *frame);
void schro_encoder_reconstruct_picture (SchroEncoderFrame *frame);
void schro_encoder_postanalyse_picture (SchroEncoderFrame *frame);
void schro_encoder_encode_picture_all (SchroEncoderFrame *frame);

SchroFrame * schro_encoder_frame_queue_get (SchroEncoder *encoder,
    SchroPictureNumber frame_number);
void schro_encoder_frame_queue_remove (SchroEncoder *encoder,
    SchroPictureNumber frame_number);
void schro_encoder_reference_add (SchroEncoder *encoder, SchroEncoderFrame *encoder_frame);
SchroEncoderFrame * schro_encoder_reference_get (SchroEncoder *encoder,
    SchroPictureNumber frame_number);
void schro_encoder_encode_picture_header (SchroEncoderFrame *frame);
SchroBuffer * schro_encoder_encode_end_of_stream (SchroEncoder *encoder);
void schro_encoder_clean_up_transform (SchroEncoderFrame *frame);
void schro_encoder_init_subbands (SchroEncoderFrame *frame);
void schro_encoder_choose_quantisers (SchroEncoderFrame *frame);
void schro_encoder_encode_subband (SchroEncoderFrame *frame, int component, int index);
SchroBuffer * schro_encoder_encode_access_unit (SchroEncoder *encoder);
void schro_encoder_output_push (SchroEncoder *encoder,
    SchroBuffer *buffer, int slot, int presentation_frame);

SchroEncoderFrame * schro_encoder_frame_new (SchroEncoder *encoder);
void schro_encoder_frame_ref (SchroEncoderFrame *frame);
void schro_encoder_frame_unref (SchroEncoderFrame *frame);

void schro_encoder_encode_lowdelay_transform_data (SchroEncoderFrame *frame);
void schro_encoder_estimate_entropy (SchroEncoderFrame *frame);
void schro_encoder_recalculate_allocations (SchroEncoder *encoder);

void schro_encoder_calculate_test_info (SchroEncoderFrame *frame);

#endif

SCHRO_END_DECLS

#endif

