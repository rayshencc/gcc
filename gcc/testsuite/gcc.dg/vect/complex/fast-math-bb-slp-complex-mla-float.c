/* { dg-do compile } */
/* { dg-require-effective-target vect_complex_add_float } */
/* { dg-additional-options "-ffast-math -fdump-tree-vect-details" } */
/* { dg-add-options arm_v8_3a_complex_neon } */

#define TYPE float
#define N 16
#include "complex-mla-template.c"
/* { dg-final { scan-tree-dump "Found COMPLEX_FMA_CONJ" "vect" } } */
/* { dg-final { scan-tree-dump "Found COMPLEX_FMA" "vect" } } */
