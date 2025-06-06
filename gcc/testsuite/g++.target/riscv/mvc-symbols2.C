/* { dg-do compile } */
/* { dg-require-ifunc "" } */
/* { dg-options "-O0 -march=rv64gc -mabi=lp64" } */

__attribute__((target_clones("default", "arch=+v", "arch=+zba,+zbb")))
int foo ()
{
  return 1;
}

__attribute__((target_clones("arch=+zba,+zbb", "arch=+v", "default")))
int foo (int)
{
  return 2;
}

/* When updating any of the symbol names in these tests, make sure to also
   update any tests for their absence in mvc-symbolsN.C */

/* { dg-final { scan-assembler ".attribute arch, \"rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0_zmmul1p0_zaamo1p0_zalrsc1p0_zca1p0_zcd1p0\"" } } */
/* { dg-final { scan-assembler-times ".option arch, rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_v1p0_zicsr2p0_zifencei2p0_zmmul1p0_zaamo1p0_zalrsc1p0_zca1p0_zcd1p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0" 2 } } */
/* { dg-final { scan-assembler-times ".option arch, rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0_zmmul1p0_zaamo1p0_zalrsc1p0_zca1p0_zcd1p0_zba1p0_zbb1p0" 2 } } */

/* { dg-final { scan-assembler-times "\n_Z3foov\.default:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n_Z3foov\.arch__v:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n_Z3foov\.arch__zba__zbb:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n_Z3foov\.resolver:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n\t\.type\t_Z3foov, @gnu_indirect_function\n" 1 } } */
/* { dg-final { scan-assembler-times "\n\t\.set\t_Z3foov,_Z3foov\.resolver\n" 1 } } */

/* { dg-final { scan-assembler-times "\n_Z3fooi\.default:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n_Z3fooi\.arch__v:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n_Z3fooi\.arch__zba__zbb:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n_Z3fooi\.resolver:\n" 1 } } */
/* { dg-final { scan-assembler-times "\n\t\.type\t_Z3fooi, @gnu_indirect_function\n" 1 } } */
/* { dg-final { scan-assembler-times "\n\t\.set\t_Z3fooi,_Z3fooi\.resolver\n" 1 } } */
