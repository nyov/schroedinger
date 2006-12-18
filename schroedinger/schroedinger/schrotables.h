
#ifndef __SCHRO_SCHRO_TABLES_H__
#define __SCHRO_SCHRO_TABLES_H__

#include <schroedinger/schro-stdint.h>
#include <schroedinger/schroutils.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t schro_table_offset_1_4[61] SCHRO_INTERNAL;
extern uint32_t schro_table_offset_3_8[61] SCHRO_INTERNAL;
extern uint32_t schro_table_offset_1_2[61] SCHRO_INTERNAL;
extern uint32_t schro_table_quant[61] SCHRO_INTERNAL;
extern uint32_t schro_table_inverse_quant[61] SCHRO_INTERNAL;
extern uint16_t schro_table_division_factor[257] SCHRO_INTERNAL;
extern uint16_t schro_table_arith_shift[256];

#ifdef __cplusplus
}
#endif

#endif

