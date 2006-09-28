
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <schroedinger/schro.h>
#include <schroedinger/schroarith.h>

#define BUFFER_SIZE 10000

int debug=1;
int verbose = 0;

void
decode(uint8_t *dest, uint8_t *src, int n_bytes)
{
  SchroArith *a;
  SchroBuffer *buffer;
  int i;
  int j;
  int value;
  int bit;

  a = schro_arith_new();

  buffer = schro_buffer_new_with_data (src, n_bytes);
  schro_arith_decode_init (a, buffer);
  schro_arith_init_contexts (a);

  for(i=0;i<n_bytes;i++){
    value = 0;
    if (verbose) printf("%d:\n", i);
    for(j=0;j<8;j++){
      if (verbose) printf("[%04x %04x] %04x -> ", a->range[0], a->range[1], a->code);
      bit = schro_arith_context_decode_bit (a, 0);
      if (verbose) printf("%d\n", bit);
      value |= bit << (7-j);
    }
    dest[i] = value;
  }

  schro_arith_free(a);
}

void
encode (uint8_t *dest, uint8_t *src, int n_bytes)
{
  SchroArith *a;
  SchroBuffer *buffer;
  int i;
  int j;
  int bit;

  a = schro_arith_new();

  buffer = schro_buffer_new_with_data (dest, BUFFER_SIZE);
  schro_arith_encode_init (a, buffer);
  schro_arith_init_contexts (a);

  for(i=0;i<n_bytes;i++){
    if (verbose) printf("%d:\n", i);
    for(j=0;j<8;j++){
      bit = (src[i]>>(7-j))&1;
      if (verbose) printf("[%04x %04x] %d\n", a->range[0], a->range[1], bit);
      schro_arith_context_encode_bit (a, 0, bit);
    }
  }
  schro_arith_flush (a);

  schro_arith_free(a);
}

uint8_t buffer1[BUFFER_SIZE];
uint8_t buffer2[BUFFER_SIZE];
uint8_t buffer3[BUFFER_SIZE];

int
check (int n)
{

  encode(buffer2, buffer1, n);
#if 0
  for(i=0;i<4;i++){
    printf("%02x\n", buffer2[i]);
  }
#endif
  decode(buffer3, buffer2, n);

  if (memcmp (buffer1, buffer3, n)) {
    return 0;
  }
  return 1;
}

int
main (int argc, char *argv[])
{
  int i;
  int n;
  int fail=0;
  int j;

  schro_init();

  for (j = 0; j < 40; j++){
    int value;
    value = 0xff & random();

    for(i=0;i<100;i++){
      buffer1[i] = value;
    }

    for(n=0;n<100;n++){
      if (debug) {
        printf("Checking: encoding/decoding constant array (size=%d value=%d)\n",
            n, value);
      }
      if (!check(n)){
        printf("Failed: encoding/decoding constant array (size=%d value=%d)\n",
            n, value);
        fail = 1;
      }
    }
  }

  for (j = 0; j < 8; j++) {
    int mask;
    mask = (1<<(j+1)) - 1;
    for(i=0;i<100;i++){
      buffer1[i] = mask & random();
    }

    for(n=0;n<100;n++){
      if (debug) {
        printf("Checking: encoding/decoding masked random array (size=%d mask=%02x)\n",
            n, mask);
      }
      if (!check(n)){
        printf("Failed: encoding/decoding masked random array (size=%d mask=%02x)\n",
            n, mask);
        fail = 1;
      }
    }
  }

  for (j = 0; j < 8; j++) {
    int mask;
    mask = (1<<(j+1)) - 1;
    for(i=0;i<100;i++){
      buffer1[i] = mask & random();
    }

    for(n=0;n<100;n++){
      if (debug) {
        printf("Checking: encoding/decoding masked random array (size=%d mask=%02x)\n",
            n, mask);
      }
      if (!check(n)){
        printf("Failed: encoding/decoding masked random array (size=%d mask=%02x)\n",
            n, mask);
        fail = 1;
      }
    }
  }

  return fail;
}
