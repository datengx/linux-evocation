/*---------------------------------------------------------------------------+
 |  fpu_etc.c                                                                |
 |                                                                           |
 | Implement a few FPU instructions.                                         |
 |                                                                           |
 | Copyright (C) 1992,1993                                                   |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail apm233m@vaxc.cc.monash.edu.au    |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#include "fpu_system.h"
#include "exception.h"
#include "fpu_emu.h"
#include "status_w.h"
#include "reg_constant.h"


static void fchs(void)
{
  if ( NOT_EMPTY_0 )
    {
      FPU_st0_ptr->sign ^= SIGN_POS^SIGN_NEG;
#ifdef PECULIAR_486
      /* Default, this conveys no information, but an 80486 does it. */
      clear_C1();
#endif PECULIAR_486
    }
  else
    stack_underflow();
}

static void fabs(void)
{
  if ( FPU_st0_tag ^ TW_Empty )
    {
      FPU_st0_ptr->sign = SIGN_POS;
#ifdef PECULIAR_486
      /* Default, this conveys no information, but an 80486 does it. */
      clear_C1();
#endif PECULIAR_486
    }
  else
    stack_underflow();
}


static void ftst_(void)
{
  switch (FPU_st0_tag)
    {
    case TW_Zero:
      setcc(SW_C3);
      break;
    case TW_Valid:
      if (FPU_st0_ptr->sign == SIGN_POS)
        setcc(0);
      else
        setcc(SW_C0);

#ifdef DENORM_OPERAND
      if ( (FPU_st0_ptr->exp <= EXP_UNDER) && (denormal_operand()) )
	{
#ifdef PECULIAR_486
	  /* This is wierd! */
	  if (FPU_st0_ptr->sign == SIGN_POS)
	    setcc(SW_C3);
#endif PECULIAR_486
	  return;
	}
#endif DENORM_OPERAND

      break;
    case TW_NaN:
      setcc(SW_C0|SW_C2|SW_C3);   /* Operand is not comparable */ 
      EXCEPTION(EX_Invalid);
      break;
    case TW_Infinity:
      if (FPU_st0_ptr->sign == SIGN_POS)
        setcc(0);
      else
        setcc(SW_C0);
      break;
    case TW_Empty:
      setcc(SW_C0|SW_C2|SW_C3);
      EXCEPTION(EX_StackUnder);
      break;
    default:
      setcc(SW_C0|SW_C2|SW_C3);   /* Operand is not comparable */ 
      EXCEPTION(EX_INTERNAL|0x14);
      break;
    }
}

static void fxam(void)
{
  int c=0;
  switch (FPU_st0_tag)
    {
    case TW_Empty:
      c = SW_C3|SW_C0;
      break;
    case TW_Zero:
      c = SW_C3;
      break;
    case TW_Valid:
      /* This will need to be changed if TW_Denormal is ever used. */
      if ( FPU_st0_ptr->exp <= EXP_UNDER )
        c = SW_C2|SW_C3;  /* Denormal */
      else
        c = SW_C2;
      break;
    case TW_NaN:
      c = SW_C0;
      break;
    case TW_Infinity:
      c = SW_C2|SW_C0;
      break;
    }
  if (FPU_st0_ptr->sign == SIGN_NEG)
    c |= SW_C1;
  setcc(c);
}

static FUNC fp_etc_table[] = {
  fchs, fabs, Un_impl, Un_impl, ftst_, fxam, Un_impl, Un_impl
};

void fp_etc()
{
  (fp_etc_table[FPU_rm])();
}
