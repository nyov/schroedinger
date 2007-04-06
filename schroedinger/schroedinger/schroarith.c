
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

#include <schroedinger/schroarith.h>
#include <schroedinger/schrotables.h>
#include <schroedinger/schrodebug.h>

#define USE_NEWEST_CODER

static int __schro_arith_context_decode_bit (SchroArith *arith, int i);

SchroArith *
schro_arith_new (void)
{
  SchroArith *arith;
  
  arith = malloc (sizeof(*arith));
  memset (arith, 0, sizeof(*arith));

  /* FIXME wtf? */
  (void)&__schro_arith_context_decode_bit;

  return arith;
}

void
schro_arith_free (SchroArith *arith)
{
  free(arith);
}

void
schro_arith_decode_init (SchroArith *arith, SchroBuffer *buffer)
{
  memset(arith, 0, sizeof(SchroArith));
  arith->range[0] = 0;
  arith->range[1] = 0x10000;
  arith->code = 0;

  arith->buffer = buffer;

  arith->dataptr = arith->buffer->data;
  arith->code = arith->dataptr[0] << 8;
  arith->code |= arith->dataptr[1];
  arith->offset = 2;
}

void
schro_arith_encode_init (SchroArith *arith, SchroBuffer *buffer)
{
  memset(arith, 0, sizeof(SchroArith));
  arith->range[0] = 0;
  arith->range[1] = 0x10000;
  arith->code = 0;

  arith->buffer = buffer;
  arith->offset = 0;
  arith->dataptr = arith->buffer->data;
}

void
schro_arith_flush (SchroArith *arith)
{
  while (arith->cntr < 8) {
    arith->range[0] <<= 1;
    arith->cntr++;
  }

  if (arith->range[0] >= (1<<24)) {
    arith->dataptr[arith->offset-1]++;
    while (arith->carry) {
      arith->dataptr[arith->offset] = 0x00;
      arith->carry--;
      arith->offset++;
    }
  } else {
    while (arith->carry) {
      arith->dataptr[arith->offset] = 0xff;
      arith->carry--;
      arith->offset++;
    }
  }

  arith->dataptr[arith->offset] = arith->range[0] >> 16;
  arith->offset++;
  arith->dataptr[arith->offset] = arith->range[0] >> 8;
  arith->offset++;
  arith->dataptr[arith->offset] = arith->range[0] >> 0;
  arith->offset++;
}

static const int next_list[] = {
  0,
  SCHRO_CTX_QUANTISER_CONT,
  0,
  0,
  SCHRO_CTX_ZP_F2,
  SCHRO_CTX_ZP_F2,
  SCHRO_CTX_ZP_F3,
  SCHRO_CTX_ZP_F4,
  SCHRO_CTX_ZP_F5,
  SCHRO_CTX_ZP_F6p,
  SCHRO_CTX_ZP_F6p,
  SCHRO_CTX_NP_F2,
  SCHRO_CTX_NP_F2,
  SCHRO_CTX_NP_F3,
  SCHRO_CTX_NP_F4,
  SCHRO_CTX_NP_F5,
  SCHRO_CTX_NP_F6p,
  SCHRO_CTX_NP_F6p,
  0,
  0,
  0,
  0,

  SCHRO_CTX_SB_F2,
  SCHRO_CTX_SB_F2,
  0,
  0,
  0,
  0,
  SCHRO_CTX_LUMA_DC_CONT_BIN2,
  SCHRO_CTX_LUMA_DC_CONT_BIN2,
  0,
  0,
  SCHRO_CTX_CHROMA1_DC_CONT_BIN2,
  SCHRO_CTX_CHROMA1_DC_CONT_BIN2,
  0,
  0,
  SCHRO_CTX_CHROMA2_DC_CONT_BIN2,
  SCHRO_CTX_CHROMA2_DC_CONT_BIN2,
  0,
  0,
  SCHRO_CTX_MV_REF1_H_CONT_BIN2,
  SCHRO_CTX_MV_REF1_H_CONT_BIN3,
  SCHRO_CTX_MV_REF1_H_CONT_BIN4,
  SCHRO_CTX_MV_REF1_H_CONT_BIN5,
  SCHRO_CTX_MV_REF1_H_CONT_BIN5,
  0,
  0,
  SCHRO_CTX_MV_REF1_V_CONT_BIN2,
  SCHRO_CTX_MV_REF1_V_CONT_BIN3,
  SCHRO_CTX_MV_REF1_V_CONT_BIN4,
  SCHRO_CTX_MV_REF1_V_CONT_BIN5,
  SCHRO_CTX_MV_REF1_V_CONT_BIN5,
  0,
  0,
  SCHRO_CTX_MV_REF2_H_CONT_BIN2,
  SCHRO_CTX_MV_REF2_H_CONT_BIN3,
  SCHRO_CTX_MV_REF2_H_CONT_BIN4,
  SCHRO_CTX_MV_REF2_H_CONT_BIN5,
  SCHRO_CTX_MV_REF2_H_CONT_BIN5,
  0,
  0,
  SCHRO_CTX_MV_REF2_V_CONT_BIN2,
  SCHRO_CTX_MV_REF2_V_CONT_BIN3,
  SCHRO_CTX_MV_REF2_V_CONT_BIN4,
  SCHRO_CTX_MV_REF2_V_CONT_BIN5,
  SCHRO_CTX_MV_REF2_V_CONT_BIN5,
  0,
  0,
  0,
};
  
void
schro_arith_init_contexts (SchroArith *arith)
{
  int i;
  for(i=0;i<SCHRO_CTX_LAST;i++){
    arith->contexts[i].count[0] = 1;
    arith->contexts[i].count[1] = 1;
    arith->contexts[i].next = next_list[i];
    arith->contexts[i].n = 1;
    arith->contexts[i].probability = 0x8000;
  }
}

void
schro_arith_halve_all_counts (SchroArith *arith)
{
  int i;
  for(i=0;i<SCHRO_CTX_LAST;i++) {
#if DIRAC_COMPAT
    if (arith->contexts[i].count[0] + arith->contexts[i].count[1] > 16) {
      arith->contexts[i].count[0] >>= 1;
      arith->contexts[i].count[0]++;
      arith->contexts[i].count[1] >>= 1;
      arith->contexts[i].count[1]++;
    }
#else
    arith->contexts[i].count[0] >>= 1;
    arith->contexts[i].count[0]++;
    arith->contexts[i].count[1] >>= 1;
    arith->contexts[i].count[1]++;
#endif
  }
}

int
_schro_arith_context_decode_bit (SchroArith *arith, int i)
{
  return __schro_arith_context_decode_bit (arith, i);
}

#ifdef USE_NEWEST_CODER
static const unsigned int lut[256] = {
  //LUT corresponds to window = 16 @ p0=0.5 & 256 @ p=1.0
     0,    2,    5,    8,   11,   15,   20,   24,
    29,   35,   41,   47,   53,   60,   67,   74,
    82,   89,   97,  106,  114,  123,  132,  141,
   150,  160,  170,  180,  190,  201,  211,  222,
   233,  244,  256,  267,  279,  291,  303,  315,
   327,  340,  353,  366,  379,  392,  405,  419,
   433,  447,  461,  475,  489,  504,  518,  533,
   548,  563,  578,  593,  609,  624,  640,  656,
   672,  688,  705,  721,  738,  754,  771,  788,
   805,  822,  840,  857,  875,  892,  910,  928,
   946,  964,  983, 1001, 1020, 1038, 1057, 1076,
  1095, 1114, 1133, 1153, 1172, 1192, 1211, 1231,
  1251, 1271, 1291, 1311, 1332, 1352, 1373, 1393,
  1414, 1435, 1456, 1477, 1498, 1520, 1541, 1562,
  1584, 1606, 1628, 1649, 1671, 1694, 1716, 1738,
  1760, 1783, 1806, 1828, 1851, 1874, 1897, 1920,
  1935, 1942, 1949, 1955, 1961, 1968, 1974, 1980,
  1985, 1991, 1996, 2001, 2006, 2011, 2016, 2021,
  2025, 2029, 2033, 2037, 2040, 2044, 2047, 2050,
  2053, 2056, 2058, 2061, 2063, 2065, 2066, 2068,
  2069, 2070, 2071, 2072, 2072, 2072, 2072, 2072,
  2072, 2071, 2070, 2069, 2068, 2066, 2065, 2063,
  2060, 2058, 2055, 2052, 2049, 2045, 2042, 2038,
  2033, 2029, 2024, 2019, 2013, 2008, 2002, 1996,
  1989, 1982, 1975, 1968, 1960, 1952, 1943, 1934,
  1925, 1916, 1906, 1896, 1885, 1874, 1863, 1851,
  1839, 1827, 1814, 1800, 1786, 1772, 1757, 1742,
  1727, 1710, 1694, 1676, 1659, 1640, 1622, 1602,
  1582, 1561, 1540, 1518, 1495, 1471, 1447, 1422,
  1396, 1369, 1341, 1312, 1282, 1251, 1219, 1186,
  1151, 1114, 1077, 1037,  995,  952,  906,  857,
   805,  750,  690,  625,  553,  471,  376,  255
};

static int
__schro_arith_context_decode_bit (SchroArith *arith, int i)
{
  unsigned int range;
  unsigned int probability0;
  unsigned int range_x_prob;
  unsigned int count;
  int value;

  probability0 = arith->contexts[i].probability;
  count = arith->code - arith->range[0] + 1;
  range = arith->range[1];
  range_x_prob = (range * probability0) >> 16;

  value = (count > range_x_prob);
  if (value) {
    arith->range[0] = arith->range[0] + range_x_prob;
    arith->range[1] -= range_x_prob;
    arith->contexts[i].probability -= lut[arith->contexts[i].probability>>8];
  } else {
    arith->range[1] = range_x_prob;
    arith->contexts[i].probability += lut[255-(arith->contexts[i].probability>>8)];
  }

  while (arith->range[1] < 0x1000) {
    arith->range[0] <<= 1;
    arith->range[1] <<= 1;

    arith->code <<= 1;
    arith->code |= (arith->dataptr[arith->offset] >> (7-arith->cntr))&1;

    arith->cntr++;

    if (arith->cntr == 8) {
      arith->offset++;
      arith->range[0] &= 0xffff;
      arith->code &= 0xffff;

      if (arith->code < arith->range[0]) {
        arith->code |= (1<<16);
      }
      arith->cntr = 0;
    }
  }

  return value;
}

void
_schro_arith_context_encode_bit (SchroArith *arith, int i, int value)
{
  unsigned int range;
  unsigned int probability0;
  unsigned int range_x_prob;

  probability0 = arith->contexts[i].probability;
  range = arith->range[1];
  range_x_prob = (range * probability0) >> 16;

  if (value) {
    arith->range[0] = arith->range[0] + range_x_prob;
    arith->range[1] -= range_x_prob;
    arith->contexts[i].probability -= lut[arith->contexts[i].probability>>8];
  } else {
    arith->range[1] = range_x_prob;
    arith->contexts[i].probability += lut[255-(arith->contexts[i].probability>>8)];
  }

  while (arith->range[1] < 0x1000) {
    arith->range[0] <<= 1;
    arith->range[1] <<= 1;
    arith->cntr++;

    if (arith->cntr == 8) {
      if (arith->range[0] < (1<<24) &&
          (arith->range[0] + arith->range[1]) >= (1<<24)) {
        arith->carry++;
      } else {
        if (arith->range[0] >= (1<<24)) {
          arith->dataptr[arith->offset-1]++;
          while (arith->carry) {
            arith->dataptr[arith->offset] = 0x00;
            arith->carry--;
            arith->offset++;
          }
        } else {
          while (arith->carry) {
            arith->dataptr[arith->offset] = 0xff;
            arith->carry--;
            arith->offset++;
          }
        }
        arith->dataptr[arith->offset] = arith->range[0] >> 16;
        arith->offset++;
      }

      arith->range[0] &= 0xffff;
      arith->cntr = 0;
    }
  }
}
#else
static int
__schro_arith_context_decode_bit (SchroArith *arith, int i)
{
  unsigned int range;
  unsigned int probability0;
  unsigned int range_x_prob;
  unsigned int count;
  int value;

  probability0 = arith->contexts[i].probability;
  count = arith->code - arith->range[0] + 1;
  range = arith->range[1];
  range_x_prob = (range * probability0) >> 16;

  value = (count > range_x_prob);
  if (value) {
    arith->range[0] = arith->range[0] + range_x_prob;
    arith->range[1] -= range_x_prob;
  } else {
    arith->range[1] = range_x_prob;
  }
  arith->contexts[i].count[value]++;
  arith->contexts[i].n--;
  if (arith->contexts[i].n == 0) {
    unsigned int scaler;
    unsigned int weight;

    if (arith->contexts[i].count[0] + arith->contexts[i].count[1] > 255) {
      arith->contexts[i].count[0] >>= 1;
      arith->contexts[i].count[0]++;
      arith->contexts[i].count[1] >>= 1;
      arith->contexts[i].count[1]++;
    }
    weight = arith->contexts[i].count[0] + arith->contexts[i].count[1];
    scaler = schro_table_division_factor[weight];
    arith->contexts[i].probability = arith->contexts[i].count[0] * scaler;

    if (weight > 16) {
      arith->contexts[i].n = 16;
    } else {
      arith->contexts[i].n = 1;
    }
  }

  while (arith->range[1] < 0x1000) {
    arith->range[0] <<= 1;
    arith->range[1] <<= 1;

    arith->code <<= 1;
    arith->code |= (arith->dataptr[arith->offset] >> (7-arith->cntr))&1;

    arith->cntr++;

    if (arith->cntr == 8) {
      arith->offset++;
      arith->range[0] &= 0xffff;
      arith->code &= 0xffff;

      if (arith->code < arith->range[0]) {
        arith->code |= (1<<16);
      }
      arith->cntr = 0;
    }
  }

  return value;
}

void
_schro_arith_context_encode_bit (SchroArith *arith, int i, int value)
{
  unsigned int range;
  unsigned int probability0;
  unsigned int range_x_prob;

  probability0 = arith->contexts[i].probability;
  range = arith->range[1];
  range_x_prob = (range * probability0) >> 16;

  if (value) {
    arith->range[0] = arith->range[0] + range_x_prob;
    arith->range[1] -= range_x_prob;
  } else {
    arith->range[1] = range_x_prob;
  }
  arith->contexts[i].count[value]++;
  arith->contexts[i].n--;
  if (arith->contexts[i].n == 0) {
    unsigned int scaler;
    unsigned int weight;

    if (arith->contexts[i].count[0] + arith->contexts[i].count[1] > 255) {
      arith->contexts[i].count[0] >>= 1;
      arith->contexts[i].count[0]++;
      arith->contexts[i].count[1] >>= 1;
      arith->contexts[i].count[1]++;
    }
    weight = arith->contexts[i].count[0] + arith->contexts[i].count[1];
    scaler = schro_table_division_factor[weight];
    arith->contexts[i].probability = arith->contexts[i].count[0] * scaler;

    if (weight > 16) {
      arith->contexts[i].n = 16;
    } else {
      arith->contexts[i].n = 1;
    }
  }

  while (arith->range[1] < 0x1000) {
    arith->range[0] <<= 1;
    arith->range[1] <<= 1;
    arith->cntr++;

    if (arith->cntr == 8) {
      if (arith->range[0] < (1<<24) &&
          (arith->range[0] + arith->range[1]) >= (1<<24)) {
        arith->carry++;
      } else {
        if (arith->range[0] >= (1<<24)) {
          arith->dataptr[arith->offset-1]++;
          while (arith->carry) {
            arith->dataptr[arith->offset] = 0x00;
            arith->carry--;
            arith->offset++;
          }
        } else {
          while (arith->carry) {
            arith->dataptr[arith->offset] = 0xff;
            arith->carry--;
            arith->offset++;
          }
        }
        arith->dataptr[arith->offset] = arith->range[0] >> 16;
        arith->offset++;
      }

      arith->range[0] &= 0xffff;
      arith->cntr = 0;
    }
  }
}
#endif

static int
maxbit (unsigned int x)
{
  int i;
  for(i=0;x;i++){
    x >>= 1;
  }
  return i;
}

void
_schro_arith_context_encode_uint (SchroArith *arith, int cont_context,
    int value_context, int value)
{
  int i;
  int n_bits;

  value++;
  n_bits = maxbit(value);
  for(i=0;i<n_bits - 1;i++){
    _schro_arith_context_encode_bit (arith, cont_context, 0);
    _schro_arith_context_encode_bit (arith, value_context,
        (value>>(n_bits - 2 - i))&1);
    cont_context = arith->contexts[cont_context].next;
  }
  _schro_arith_context_encode_bit (arith, cont_context, 1);
}

void
_schro_arith_context_encode_sint (SchroArith *arith, int cont_context,
    int value_context, int sign_context, int value)
{
  int sign;

  if (value < 0) {
    sign = 1;
    value = -value;
  } else {
    sign = 0;
  }
  _schro_arith_context_encode_uint (arith, cont_context, value_context, value);
  if (value) {
    _schro_arith_context_encode_bit (arith, sign_context, sign);
  }
}

int
_schro_arith_context_decode_uint (SchroArith *arith, int cont_context,
    int value_context)
{
  int bits;
  int count=0;

  bits = 0;
  while(!__schro_arith_context_decode_bit (arith, cont_context)) {
    bits <<= 1;
    bits |= __schro_arith_context_decode_bit (arith, value_context);
    cont_context = arith->contexts[cont_context].next;
    count++;

    /* FIXME being careful */
    if (count == 30) break;
  }
  return (1<<count) - 1 + bits;
}

int
_schro_arith_context_decode_sint (SchroArith *arith, int cont_context,
    int value_context, int sign_context)
{
  int bits;
  int count=0;
  int value;

  bits = 0;
  while(!__schro_arith_context_decode_bit (arith, cont_context)) {
    bits <<= 1;
    bits |= __schro_arith_context_decode_bit (arith, value_context);
    cont_context = arith->contexts[cont_context].next;
    count++;

    /* FIXME being careful */
    if (count == 30) break;
  }
  value = (1<<count) - 1 + bits;

  if (value) {
    if (__schro_arith_context_decode_bit (arith, sign_context)) {
      value = -value;
    }
  }

  return value;
}

/* wrappers */

void
schro_arith_context_encode_bit (SchroArith *arith, int i, int value)
{
  _schro_arith_context_encode_bit (arith, i, value);
}

void
schro_arith_context_encode_uint (SchroArith *arith, int cont_context,
    int value_context, int value)
{
  _schro_arith_context_encode_uint (arith, cont_context, value_context, value);
}

void
schro_arith_context_encode_sint (SchroArith *arith, int cont_context,
    int value_context, int sign_context, int value)
{
  _schro_arith_context_encode_sint (arith, cont_context, value_context,
      sign_context, value);
}

int
schro_arith_context_decode_bit (SchroArith *arith, int context)
{
  return __schro_arith_context_decode_bit (arith, context);
}

int
schro_arith_context_decode_uint (SchroArith *arith, int cont_context,
    int value_context)
{
  return _schro_arith_context_decode_uint (arith, cont_context, value_context);
}

int
schro_arith_context_decode_sint (SchroArith *arith, int cont_context,
    int value_context, int sign_context)
{
  return _schro_arith_context_decode_sint (arith, cont_context,
      value_context, sign_context);
}

