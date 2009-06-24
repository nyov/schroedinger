
/* autogenerated from schro.orc */

#include <orc/orc.h>
#include <orc-test/orctest.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
  int error = FALSE;

  orc_test_init ();

  /* orc_add2_rshift_add_s16_22 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add2_rshift_add_s16_22:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add2_rshift_add_s16_22");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_constant (p, 2, 2, "c1");
    orc_program_add_constant (p, 2, 2, "c2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2);
    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_C1);
    orc_program_append (p, "shrsw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_C2);
    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_add2_rshift_sub_s16_22 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add2_rshift_sub_s16_22:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add2_rshift_sub_s16_22");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_constant (p, 2, 2, "c1");
    orc_program_add_constant (p, 2, 2, "c2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2);
    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_C1);
    orc_program_append (p, "shrsw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_C2);
    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_add2_rshift_add_s16_11 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add2_rshift_add_s16_11:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add2_rshift_add_s16_11");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "avgsw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2);
    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_add2_rshift_sub_s16_11 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add2_rshift_sub_s16_11:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add2_rshift_sub_s16_11");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "avgsw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2);
    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_add_const_rshift_s16_11 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add_const_rshift_s16_11:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add_const_rshift_s16_11");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_constant (p, 2, 1, "c1");
    orc_program_add_constant (p, 2, 1, "c2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_C1);
    orc_program_append (p, "shrsw", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_C2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_add_const_rshift_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add_const_rshift_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add_const_rshift_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_parameter (p, 2, "p1");
    orc_program_add_parameter (p, 2, "p2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_P1);
    orc_program_append (p, "shrsw", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_P2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_add_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");

    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_S2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_addc_rshift_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_addc_rshift_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_addc_rshift_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_parameter (p, 2, "p1");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2);
    orc_program_append (p, "shrsw", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_P1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_lshift1_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_lshift1_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_lshift1_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_constant (p, 2, 1, "c1");

    orc_program_append (p, "shlw", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_C1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_lshift2_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_lshift2_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_lshift2_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_constant (p, 2, 2, "c1");

    orc_program_append (p, "shlw", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_C1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_lshift_s16_ip */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_lshift_s16_ip:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_lshift_s16_ip");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_parameter (p, 2, "p1");

    orc_program_append (p, "shlw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_P1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_mas2_add_s16_ip */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_mas2_add_s16_ip:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_mas2_add_s16_ip");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_parameter (p, 2, "p1");
    orc_program_add_parameter (p, 4, "p2");
    orc_program_add_parameter (p, 4, "p3");
    orc_program_add_temporary (p, 2, "t1");
    orc_program_add_temporary (p, 4, "t2");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2);
    orc_program_append (p, "mulswl", ORC_VAR_T2, ORC_VAR_T1, ORC_VAR_P1);
    orc_program_append (p, "addl", ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_P2);
    orc_program_append (p, "shrsl", ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_P3);
    orc_program_append (p, "convlw", ORC_VAR_T1, ORC_VAR_T2, ORC_VAR_D1);
    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_mas2_sub_s16_ip */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_mas2_sub_s16_ip:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_mas2_sub_s16_ip");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_parameter (p, 2, "p1");
    orc_program_add_parameter (p, 4, "p2");
    orc_program_add_parameter (p, 4, "p3");
    orc_program_add_temporary (p, 2, "t1");
    orc_program_add_temporary (p, 4, "t2");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_S2);
    orc_program_append (p, "mulswl", ORC_VAR_T2, ORC_VAR_T1, ORC_VAR_P1);
    orc_program_append (p, "addl", ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_P2);
    orc_program_append (p, "shrsl", ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_P3);
    orc_program_append (p, "convlw", ORC_VAR_T1, ORC_VAR_T2, ORC_VAR_D1);
    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_mas4_across_add_s16_1991_ip */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_mas4_across_add_s16_1991_ip:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_mas4_across_add_s16_1991_ip");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_source (p, 2, "s3");
    orc_program_add_source (p, 2, "s4");
    orc_program_add_constant (p, 2, 9, "c1");
    orc_program_add_parameter (p, 4, "p1");
    orc_program_add_parameter (p, 4, "p2");
    orc_program_add_temporary (p, 2, "t1");
    orc_program_add_temporary (p, 2, "t2");
    orc_program_add_temporary (p, 4, "t3");
    orc_program_add_temporary (p, 4, "t4");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S2, ORC_VAR_S3);
    orc_program_append (p, "mulswl", ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_C1);
    orc_program_append (p, "addw", ORC_VAR_T2, ORC_VAR_S1, ORC_VAR_S4);
    orc_program_append (p, "convswl", ORC_VAR_T4, ORC_VAR_T2, ORC_VAR_D1);
    orc_program_append (p, "subl", ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_T4);
    orc_program_append (p, "addl", ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_P1);
    orc_program_append (p, "shrsl", ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_P2);
    orc_program_append (p, "convlw", ORC_VAR_T1, ORC_VAR_T3, ORC_VAR_D1);
    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_mas4_across_sub_s16_1991_ip */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_mas4_across_sub_s16_1991_ip:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_mas4_across_sub_s16_1991_ip");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_source (p, 2, "s3");
    orc_program_add_source (p, 2, "s4");
    orc_program_add_constant (p, 2, 9, "c1");
    orc_program_add_parameter (p, 4, "p1");
    orc_program_add_parameter (p, 4, "p2");
    orc_program_add_temporary (p, 2, "t1");
    orc_program_add_temporary (p, 2, "t2");
    orc_program_add_temporary (p, 4, "t3");
    orc_program_add_temporary (p, 4, "t4");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S2, ORC_VAR_S3);
    orc_program_append (p, "mulswl", ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_C1);
    orc_program_append (p, "addw", ORC_VAR_T2, ORC_VAR_S1, ORC_VAR_S4);
    orc_program_append (p, "convswl", ORC_VAR_T4, ORC_VAR_T2, ORC_VAR_D1);
    orc_program_append (p, "subl", ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_T4);
    orc_program_append (p, "addl", ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_P1);
    orc_program_append (p, "shrsl", ORC_VAR_T3, ORC_VAR_T3, ORC_VAR_P2);
    orc_program_append (p, "convlw", ORC_VAR_T1, ORC_VAR_T3, ORC_VAR_D1);
    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_subtract_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_subtract_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_subtract_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");

    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_S2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_memcpy */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_memcpy:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_memcpy");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_source (p, 1, "s1");

    orc_program_append (p, "copyb", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_add_s16_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_add_s16_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_add_s16_u8");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 1, "s2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "convubw", ORC_VAR_T1, ORC_VAR_S2, ORC_VAR_D1);
    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_S1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_convert_s16_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_convert_s16_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_convert_s16_u8");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 1, "s1");

    orc_program_append (p, "convubw", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_convert_u8_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_convert_u8_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_convert_u8_s16");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_source (p, 2, "s1");

    orc_program_append (p, "convsuswb", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_offsetconvert_u8_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_offsetconvert_u8_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_offsetconvert_u8_s16");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_constant (p, 2, 128, "c1");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_C1);
    orc_program_append (p, "convsuswb", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_offsetconvert_s16_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_offsetconvert_s16_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_offsetconvert_s16_u8");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 1, "s1");
    orc_program_add_constant (p, 2, 128, "c1");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "convubw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_C1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_subtract_s16_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_subtract_s16_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_subtract_s16_u8");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 1, "s2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "convubw", ORC_VAR_T1, ORC_VAR_S2, ORC_VAR_D1);
    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_multiply_and_add_s16_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_multiply_and_add_s16_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_multiply_and_add_s16_u8");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 1, "s2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "convubw", ORC_VAR_T1, ORC_VAR_S2, ORC_VAR_D1);
    orc_program_append (p, "mullw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_S1);
    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_splat_s16_ns */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_splat_s16_ns:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_splat_s16_ns");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_parameter (p, 2, "p1");

    orc_program_append (p, "copyw", ORC_VAR_D1, ORC_VAR_P1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_splat_u8_ns */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_splat_u8_ns:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_splat_u8_ns");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_parameter (p, 1, "p1");

    orc_program_append (p, "copyb", ORC_VAR_D1, ORC_VAR_P1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_average_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_average_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_average_u8");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_source (p, 1, "s1");
    orc_program_add_source (p, 1, "s2");

    orc_program_append (p, "avgub", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_S2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_rrshift6_s16_ip */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_rrshift6_s16_ip:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_rrshift6_s16_ip");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_constant (p, 2, 8160, "c1");
    orc_program_add_constant (p, 2, 6, "c2");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "subw", ORC_VAR_T1, ORC_VAR_D1, ORC_VAR_C1);
    orc_program_append (p, "shrsw", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_C2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_unpack_yuyv_y */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_unpack_yuyv_y:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_unpack_yuyv_y");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_source (p, 2, "s1");

    orc_program_append (p, "select0wb", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_unpack_yuyv_u */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_unpack_yuyv_u:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_unpack_yuyv_u");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_source (p, 4, "s1");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "select0lw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "select1wb", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_unpack_yuyv_v */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_unpack_yuyv_v:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_unpack_yuyv_v");
    orc_program_add_destination (p, 1, "d1");
    orc_program_add_source (p, 4, "s1");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "select1lw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "select1wb", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_packyuyv */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_packyuyv:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_packyuyv");
    orc_program_add_destination (p, 4, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 1, "s2");
    orc_program_add_source (p, 1, "s3");
    orc_program_add_temporary (p, 1, "t1");
    orc_program_add_temporary (p, 1, "t2");
    orc_program_add_temporary (p, 2, "t3");
    orc_program_add_temporary (p, 2, "t4");
    orc_program_add_temporary (p, 2, "t5");

    orc_program_append (p, "copyw", ORC_VAR_T5, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "select0wb", ORC_VAR_T1, ORC_VAR_T5, ORC_VAR_D1);
    orc_program_append (p, "select1wb", ORC_VAR_T2, ORC_VAR_T5, ORC_VAR_D1);
    orc_program_append (p, "mergebw", ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_S2);
    orc_program_append (p, "mergebw", ORC_VAR_T4, ORC_VAR_T2, ORC_VAR_S3);
    orc_program_append (p, "mergewl", ORC_VAR_D1, ORC_VAR_T3, ORC_VAR_T4);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_interleave2_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_interleave2_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_interleave2_s16");
    orc_program_add_destination (p, 4, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");

    orc_program_append (p, "mergewl", ORC_VAR_D1, ORC_VAR_S1, ORC_VAR_S2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_interleave2_rrshift1_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_interleave2_rrshift1_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_interleave2_rrshift1_s16");
    orc_program_add_destination (p, 4, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_source (p, 2, "s2");
    orc_program_add_constant (p, 2, 1, "c1");
    orc_program_add_constant (p, 2, 1, "c2");
    orc_program_add_constant (p, 2, 1, "c3");
    orc_program_add_constant (p, 2, 1, "c4");
    orc_program_add_temporary (p, 2, "t1");
    orc_program_add_temporary (p, 2, "t2");

    orc_program_append (p, "addw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_C1);
    orc_program_append (p, "shrsw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_C2);
    orc_program_append (p, "addw", ORC_VAR_T2, ORC_VAR_S2, ORC_VAR_C3);
    orc_program_append (p, "shrsw", ORC_VAR_T2, ORC_VAR_T2, ORC_VAR_C4);
    orc_program_append (p, "mergewl", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_T2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_deinterleave2_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_deinterleave2_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_deinterleave2_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_destination (p, 2, "d2");
    orc_program_add_source (p, 4, "s1");
    orc_program_add_temporary (p, 4, "t1");

    orc_program_append (p, "copyl", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "select0lw", ORC_VAR_D1, ORC_VAR_T1, ORC_VAR_D1);
    orc_program_append (p, "select1lw", ORC_VAR_D2, ORC_VAR_T1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_deinterleave2_lshift1_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_deinterleave2_lshift1_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_deinterleave2_lshift1_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_destination (p, 2, "d2");
    orc_program_add_source (p, 4, "s1");
    orc_program_add_constant (p, 2, 1, "c1");
    orc_program_add_constant (p, 2, 1, "c2");
    orc_program_add_temporary (p, 4, "t1");
    orc_program_add_temporary (p, 2, "t2");
    orc_program_add_temporary (p, 2, "t3");

    orc_program_append (p, "copyl", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "select0lw", ORC_VAR_T2, ORC_VAR_T1, ORC_VAR_D1);
    orc_program_append (p, "shlw", ORC_VAR_D1, ORC_VAR_T2, ORC_VAR_C1);
    orc_program_append (p, "select1lw", ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_D1);
    orc_program_append (p, "shlw", ORC_VAR_D2, ORC_VAR_T3, ORC_VAR_C2);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_haar_sub_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_haar_sub_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_haar_sub_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");

    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_S1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_haar_add_half_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_haar_add_half_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_haar_add_half_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_constant (p, 2, 0, "c1");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "avgsw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_C1);
    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_haar_add_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_haar_add_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_haar_add_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");

    orc_program_append (p, "addw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_S1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_haar_sub_half_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_haar_sub_half_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_haar_sub_half_s16");
    orc_program_add_destination (p, 2, "d1");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_constant (p, 2, 0, "c1");
    orc_program_add_temporary (p, 2, "t1");

    orc_program_append (p, "avgsw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_C1);
    orc_program_append (p, "subw", ORC_VAR_D1, ORC_VAR_D1, ORC_VAR_T1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_sum_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_sum_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_sum_u8");
    orc_program_add_source (p, 1, "s1");
    orc_program_add_accumulator (p, 4, "a1");
    orc_program_add_temporary (p, 2, "t1");
    orc_program_add_temporary (p, 4, "t2");

    orc_program_append (p, "convubw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "convuwl", ORC_VAR_T2, ORC_VAR_T1, ORC_VAR_D1);
    orc_program_append (p, "accl", ORC_VAR_A1, ORC_VAR_T2, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_sum_s16 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_sum_s16:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_sum_s16");
    orc_program_add_source (p, 2, "s1");
    orc_program_add_accumulator (p, 4, "a1");
    orc_program_add_temporary (p, 4, "t1");

    orc_program_append (p, "convswl", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "accl", ORC_VAR_A1, ORC_VAR_T1, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }

  /* orc_sum_square_diff_u8 */
  {
    OrcProgram *p = NULL;
    int ret;

    OrcCompileResult result;

    printf("orc_sum_square_diff_u8:\n");
    p = orc_program_new ();
    orc_program_set_name (p, "orc_sum_square_diff_u8");
    orc_program_add_source (p, 1, "s1");
    orc_program_add_source (p, 1, "s2");
    orc_program_add_accumulator (p, 4, "a1");
    orc_program_add_temporary (p, 2, "t1");
    orc_program_add_temporary (p, 2, "t2");
    orc_program_add_temporary (p, 4, "t3");

    orc_program_append (p, "convubw", ORC_VAR_T1, ORC_VAR_S1, ORC_VAR_D1);
    orc_program_append (p, "convubw", ORC_VAR_T2, ORC_VAR_S2, ORC_VAR_D1);
    orc_program_append (p, "subw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T2);
    orc_program_append (p, "mullw", ORC_VAR_T1, ORC_VAR_T1, ORC_VAR_T1);
    orc_program_append (p, "convuwl", ORC_VAR_T3, ORC_VAR_T1, ORC_VAR_D1);
    orc_program_append (p, "accl", ORC_VAR_A1, ORC_VAR_T3, ORC_VAR_D1);

    ret = orc_test_compare_output (p);
    if (!ret) error = TRUE;

    orc_program_free (p);
  }


  if (error) return 1;
  return 0;
}