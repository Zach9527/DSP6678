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
extern Uint32 program_boot_to_flash(void);
void main(void) {
	 CSL_PllcHandle  hPllc;
	 hPllc =CSL_PLLC_open (0);



	 CSL_PLLC_setPllSecCtrlReg (hPllc, 0x80);//set BYPASS enable
	 Set_Pll1(7);//10Ö÷ÆµÅäÖÃÎª1GHz
	 printf("PLL init finished! core clk = %dMHz\n",getcore_clk ());
	 TSCL=0;
	 //printf("1\n");
	 if( CSL_SOK != SetDDR3PllConfig() )
	 {
		 printf("SetDDR3PllConfig error prosess be kill\n");
		 goto END_LOOP;
	 }

EMIF16_INIT_LOOP:
	 //printf("2\n");
	 if( FAIL == emif16_init () )
	 {
		 printf("emif16_init error\n=>Restart emif16_init\n");
		 goto EMIF16_INIT_LOOP;
	 }

	 //printf("3\n");
	 xmc_setup();

	 //printf("4\n");
	 /*if( CSL_SOK != DDR3Init() )
	 {
		 printf("DDR3Init error prosess be kill\n");
		 goto END_LOOP;
	 }*/
	 //printf("5\n");
	 qryShow();
	 program_boot_to_flash();
	 printf("program finish!!!!\n");

END_LOOP:
	 while(1);
}


