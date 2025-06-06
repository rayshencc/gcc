/* { dg-do run { target { riscv_v } } } */
/* { dg-additional-options "-std=c99" } */

#include "sat_arith.h"

#define T              uint16_t
#define WT             uint64_t
#define RUN_SAT_BINARY RUN_SAT_U_ADD_FMT_7_FROM_U64_WRAP

DEF_SAT_U_ADD_FMT_7_WRAP(WT, T)

T test_data[][3] = {
  /* arg_0, arg_1, expect */
  {      0,     0,      0, },
  {      0,     1,      1, },
  {      1,     1,      2, },
  {      0, 65534,  65534, },
  {      1, 65534,  65535, },
  {      2, 65534,  65535, },
  {      0, 65535,  65535, },
  {      1, 65535,  65535, },
  {      2, 65535,  65535, },
  {  65535, 65535,  65535, },
};

#include "scalar_sat_binary.h"
