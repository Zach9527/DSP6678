/*
 * main.c
 */
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <c6x.h>
#include <ti/csl/csl_pllc.h>
#include <ti/csl/csl_pllcAux.h>
#include <ti/csl/csl_error.h>

#include "types.h"

extern int Set_Pll1( int pll_multiplier);
extern unsigned int getcore_clk ();
extern unsigned int emif16_init (void);
extern CSL_Status SetDDR3PllConfig(void);
extern void xmc_setup(void);
extern CSL_Status  DDR3Init(void);
extern Uint32 program_code_to_flash(unsigned char code_type);
void main(void) {
	 CSL_PllcHandle  hPllc;
	 hPllc =CSL_PLLC_open (0);



	 CSL_PLLC_setPllSecCtrlReg (hPllc, 0x80);//set BYPASS enable
	 Set_Pll1(7);//10主频配置为1GHz
	 printf("PLL init finished! core clk = %dMHz\n",getcore_clk ());
	 TSCL=0;

EMIF16_INIT_LOOP:
	 if( FAIL == emif16_init () )
	 {
		 printf("emif16_init error\n=>Restart emif16_init\n");
		 goto EMIF16_INIT_LOOP;
	 }

	 program_code_to_flash(0);//烧写core0的程序
//	 program_code_to_flash(1);//烧写core1的程序
//	 program_code_to_flash(2);//烧写core2的程序
	 printf("program finish!!!!\n");

	 while(1);
}


