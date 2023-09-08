/*
 鏂囦欢鍚嶇О锛歱ll_dsp667x.c
鎽樿锛氫富瑕佸疄鐜皃ll_dsp667x鐨凱LL鐨勫垵濮嬪寲
*/
/* 淇敼鍘嗗彶:
2016.3.11,chengqb鍒涘缓鏂囦欢
*/

/* includes */
#include <common.h>
#include <c6x.h>
#include "datatype.h"
#include "delay.h"
#include "pll_dsp667x.h"
#include "reg_dsp667x.h"
#include "dsp667x.h"


#define CHIP_LEVEL_REG  0x02620000
#define KICK0			*(unsigned int*)(CHIP_LEVEL_REG + 0x0038)
#define KICK1			*(unsigned int*)(CHIP_LEVEL_REG + 0x003C)
#define KICK0_UNLOCK (0x83E70B13)
#define KICK1_UNLOCK (0x95A4F1E0)
#define KICK_LOCK    0

/* defines */
#define PLLC_DIVEN_PLLDIV2    (1)	//enable div2
#define PLLC_DIVDS_PLLDIV2    (0)	//disable div2
#define PLLC_DIVEN_PLLDIV5    (1)
#define PLLC_DIVDS_PLLDIV5    (0)
#define PLLC_DIVEN_PLLDIV8    (1)
#define PLLC_DIVDS_PLLDIV8    (0)

#define CRYSTALFREQ2CORE_MHZ                     		(156.25)		/*input ref clock 156.25*/
#define COREFREQ_MHZ                     		        (1093.75)

/* Clock rate */
#define PLATFORM_BASE_CLK_RATE_MHZ      CRYSTALFREQ2CORE_MHZ
/* PREDIV */
#define PLATFORM_PLL_PREDIV_val (1)
/* POSTDIV */
#define PLATFORM_PLL_POSTDIV_val (2)
/* Default PLL PLLM value (100/1*(20/2)) = 1.0GHz) */
#define  PLATFORM_PLL1_PLLM_val (16)

/* 1/x-rate clock for CorePac (emulation) and the ADTF module */
#define  PLATFORM_PLLDIV2_val  (3)
/* 1/y-rate clock for system trace module only */
#define  PLATFORM_PLLDIV5_val (5)
/* 1/z-rate clock is used as slow_sysclck in the system */
#define  PLATFORM_PLLDIV8_val (64)

#define PARAMTER_FLAG_MASK			(0x12345AA5)
#define PREDIV		0x1
#define PLLM		0xe
#define PLLDIV2		0x3
#define PLLDIV5		0x5
#define PLLDIV8		0x40
#define POSTDIV		0x2

/*typedef*/
typedef struct PllcHwSetup {
    CSL_BitMask32 divEnable;
    UINT32        pllM;
    UINT32        pllDiv2;
    UINT32        pllDiv5;
    UINT32        pllDiv8;
    UINT32        preDiv;
    UINT32        postDiv;
    void*         extendSetup;
} PllcHwSetup;

extern void serialPrintf (char *fmt, ...);
/* globals */     
                
/* locals */      
 float gDSP_Core_Speed_Hz= 1093.75;
/* local function declarations */
LOCAL void pllDelay(UINT32 ix);
LOCAL INT32 corePllcHwSetup (PllcHwSetup *hwSetup);
LOCAL INT32 pll1Init( void );
LOCAL INT32 pll2Init(void) ;
                  
/*global function define*/ 

/*local function define*/
LOCAL void pll_delay(uint32_t ix)
{
    while (ix--) {
        asm("   NOP");
    }
}



LOCAL INT32 pll0Init()	/*main pll*/
{
	PllcHwSetup             pllc_hwSetup;
	CSL_Status              status;

	#if 0
	if(pCfg->pllParamtertFlag != PARAMTER_FLAG_MASK) //浣跨敤榛樿鍙傛暟
	{
		pCfg->crystalFreq = PLATFORM_BASE_CLK_RATE_MHZ;	//
		pCfg->coreFreq = COREFREQ_MHZ;
	}	
	#endif

	
	memset(&pllc_hwSetup, 0, sizeof(PllcHwSetup));
	/* Setup PLLC hardware parameters */
	pllc_hwSetup.divEnable  = (CSL_BitMask32) (  PLLC_DIVEN_PLLDIV2 
	                                   			|PLLC_DIVEN_PLLDIV5
	                                   			|PLLC_DIVEN_PLLDIV8) ;

	pllc_hwSetup.pllM     = PLLM - 1;
	pllc_hwSetup.preDiv   = PREDIV - 1;
	pllc_hwSetup.pllDiv2  = PLATFORM_PLLDIV2_val - 1;
	pllc_hwSetup.pllDiv5  = PLATFORM_PLLDIV5_val - 1;
	pllc_hwSetup.pllDiv8  = PLATFORM_PLLDIV8_val - 1;
	pllc_hwSetup.postDiv  = PLATFORM_PLL_POSTDIV_val -1;
	status = corePllcHwSetup (&pllc_hwSetup);

	if (status != CSL_SOK) 
	{
		return (1);
	}

	return 0;
}

LOCAL void pllDelay(UINT32 ix)
{
	while (ix--) 
	{
		asm("   NOP");
	}
}

/*CLK=CLKIN*(PLLM+1)/(OUTPUT_DIVIDE*(PLLD+1))*/
#if 0
LOCAL CSL_Status corePllcHwSetup (PllcHwSetup *hwSetup)
{
	CSL_Status		status = CSL_SOK;
	VOLATILE UINT32 i, loopCount;
	UINT32 temp;
	
	dsp667x_bootCfgUnLock();

	#if 1 //alj2014_1_21 PLLdead
	MAINPLLCTL1_REG = MAINPLLCTL1_REG | 0x00000040; //In MAINPLLCTL1, write ENSAT = 1
	#endif
	
	temp = SECCTL_REG &  0x00800000; 						// Check if bypass 
	#if 0 //dlj2014_1_21 PLLdead
	//if (temp ==  0x00800000) 								//PLL BYPASS is enabled,
	#endif
	{
		#if 0 //dlj2014_1_21 PLLdead
		MAINPLLCTL1_REG = MAINPLLCTL1_REG | 0x00000040;	//In MAINPLLCTL1, write ENSAT = 1
		PLLCTL_REG &= ~(1 << 5);							//In PLLCTL, write PLLENSRC = 0
		#endif

		PLLCTL_REG &= ~(1 << 0);							//In PLLCTL, write PLLEN = 0
		pllDelay(225); 									//Wait 4 cycles of the reference clock CLKIN
		#if 0 //mlj2014_1_21 PLLdead
		PLLCTL_REG |= 0x00800000;						//In SECCTL, write BYPASS = 1
		#else 
		SECCTL_REG |= 0x00800000;						//In SECCTL, write BYPASS = 1
		#endif
		PLLCTL_REG |= 0x00000002; 						//In PLLCTL, write PLLPWRDN = 1
		pllDelay(14005);									//Wait for at least 5 us based on the reference clock
		PLLCTL_REG   &= ~(0x00000002); 					//In PLLCTL, write PLLPWRDN = 0
	}
	PLLCTL_REG |= 0x00000008;		//In PLLCTL, write PLLRST = 1 

	/* Set pll multipler (13 bit field) */
	PLLM_REG     = (hwSetup->pllM & 0x0000003F); /* bits[5:0]  */
	temp          = (hwSetup->pllM & 0x1FC0) >> 6;  /* bits[12:6] */
	MAINPLLCTL0_REG  &=~(0x0007F000);                /*Clear PLLM field */
	MAINPLLCTL0_REG  |=((temp << 12) & 0x0007F000);

	/* Set the BWADJ (12 bit field)*/
	temp = ((hwSetup->pllM + 1)>> 1) - 1; 		//Divide the pllm by 2
	MAINPLLCTL0_REG &=~(0xFF000000);  		//Clear the BWADJ Field 
	MAINPLLCTL0_REG |=  ((temp << 24) & 0xFF000000);
	MAINPLLCTL1_REG &=~(0x0000000F);   		//Clear the BWADJ field 
	MAINPLLCTL1_REG |= ((temp >> 8) & 0x0000000F);

	/* Set the pll divider (6 bit field)  * PLLD[5:0] is located in MAINPLLCTL0 */
	MAINPLLCTL0_REG   &= ~(0x0000003F);    
	MAINPLLCTL0_REG   |= (hwSetup->preDiv & 0x0000003F);

	/* Set the OUTPUT DIVIDE (4 bit field) in SECCTL */
	SECCTL_REG    &= ~(0x00780000);    
	SECCTL_REG   |= ((1 << 19) & 0x00780000) ;	//In SECCTL, write OD (Output Divide) = 1

	/* Set PLL dividers if needed */
	PLL1_DIV2 = (0x8000) | (hwSetup->pllDiv2);
	PLL1_DIV5 = (0x8000) | (hwSetup->pllDiv5);
	PLL1_DIV8 = (0x8000) | (hwSetup->pllDiv8);

	delay(10000);
	/* Set GOSET bit in PLLCMD to initiate the GO operation to change the divide  values and align the SYSCLKs as programmed*/
	PLLALNCTL_REG |= ( (1 << 1) | (1 << 4) | (1 << 7));
	PLLCMD_REG     |= 0x00000001;
	pllDelay (14006); //Wait for at least 7 渭s based on the reference clock CLKIN

	/*In PLLCTL, write PLLRST = 0 to bring PLL out of reset */
	PLLCTL_REG &= ~(0x00000008);
	/* Wait for at least 500 脳 CLKIN cycles 脳 (PLLD + 1)   */
	for (i = 0; i < 100; )
	{
		pllDelay(300);
		if ( (PLL1_STAT & 0x00000001) == 0 ) 
		{
			break;
		}
	}
	
	PLL1_SECCTL &= ~(0x00800000); 	//In SECCTL, write BYPASS = 0	
	#if 1//alj2014_4_10 PLL鍊嶉涓嶆垚鍔�
	PLLCTL_REG &= ~((UINT32)1<<5);
	#endif
	PLLCTL_REG |= (1 << 0);			//In PLLCTL, write PLLEN = 1

	return status;
}
#endif
/* PASS PLL settings for 1044 MHz */
#define PLLM_PASS 20
#define PLLD_PASS 0

LOCAL INT32 pll1Init( void ) 	/*pa pll*/
{
   uint32_t passclksel = (DEVSTAT_REG & PASSCLKSEL_MASK);
	uint32_t papllctl0val = PAPLLCTL0_REG;
	uint32_t obsclkval = OBSCLCTL_REG;
	uint32_t pa_pllm = PLLM_PASS;
	uint32_t pa_plld = PLLD_PASS;
	uint32_t temp;
	int pass_freq;
	int pass_freM,pass_freD;

//	if (passclksel == 0)
//	{
//		serialPrintf("SYSCLK/ALTCORECLK is the input to the PA PLL...\n");
//	}

	/* Unlock the Boot Config */
	CSL_BootCfgUnlockKicker();

	if (DNUM == 0)
	{
		/* Usage Note 9: For optimal PLL operation, the ENSAT bit in the PLL control *
		 * registers for the Main PLL, DDR3 PLL, and PA PLL should be set to 1.      *
		 * The PLL initialization sequence in the boot ROM sets this bit to 0 and    *
		 * could lead to non-optimal PLL operation. Software can set the bit to the  *
		 * optimal value of 1 after boot                                             *
		 * PAPLLCTL1_REG Bit map                                                     *
		 * |31...7   |6     |5 4       |3...0      |                                 *
		 * |Reserved |ENSAT |Reserved  |BWADJ[11:8]|                                 */

		PAPLLCTL1_REG |= 0x00000040;

		/* Wait for the PLL Reset time (min: 1000 ns)                                */
		/*pll_delay(1400);*/

		/* Put the PLL in Bypass Mode                                                *
		 * PAPLLCTL0_REG Bit map                                                     *
		 * |31...24    |23     |22...19       |18...6   |5...0 |                     *
		 * |BWADJ[7:0] |BYPASS |Reserved      |PLLM     |PLLD  |                     */

		PAPLLCTL0_REG |= 0x00800000; /* Set the Bit 23 */

		/*Wait 4 cycles for the slowest of PLLOUT or reference clock source (CLKIN)*/
		/*pll_delay(4);*/

		/* Wait for the PLL Reset time (min: 1000 ns)                                */
		/*pll_delay(1400);*/

		/* Program the necessary multipliers/dividers and BW adjustments             */
		/* Set the divider values */
		PAPLLCTL0_REG &= ~(0x0000003F);
		PAPLLCTL0_REG |= (pa_plld & 0x0000003F);

		/* Set the Multipler values */
		PAPLLCTL0_REG &= ~(0x0007FFC0);
		PAPLLCTL0_REG |= ((pa_pllm << 6) & 0x0007FFC0 );

		/* Set the BWADJ */
		temp = ((pa_pllm + 1) >> 1) - 1;
		PAPLLCTL0_REG &= ~(0xFF000000);
		PAPLLCTL0_REG |= ((temp << 24) & 0xFF000000);
		PAPLLCTL1_REG &= ~(0x0000000F);
		PAPLLCTL1_REG |= ((temp >> 8) & 0x0000000F);

		/* In PLL Controller, reset the PLL (bit 14) in PAPLLCTL1_REG register       */
		PAPLLCTL1_REG |= 0x00004000;

		/*Wait for PLL to lock min 5 micro seconds*/
		pll_delay(7000);

		/*In PAPLLCTL1_REG, write PLLSELECT = 1 (for selecting the output of PASS PLL as the input to PASS) */
		PAPLLCTL1_REG |= 0x00002000;

		/*In PAPLLCTL1_REG, write PLLRST = 0 to bring PLL out of reset */
		PAPLLCTL1_REG &= ~(0x00004000);

		/*Wait for PLL to lock min 50 micro seconds*/
		pll_delay(70000);

		/* Put the PLL in PLL Mode                                                   *
		 * PAPLLCTL0_REG Bit map                                                     *
		 * |31...24    |23     |22...19       |18...6   |5...0 |                     *
		 * |BWADJ[7:0] |BYPASS |Reserved      |PLLM     |PLLD  |                     */
		PAPLLCTL0_REG &= ~(0x00800000); /* ReSet the Bit 23 */

		papllctl0val = PAPLLCTL0_REG;

		/* Tells the multiplier value for the PA PLL */
		pa_pllm = (((papllctl0val & PA_PLL_CLKF_MASK) >> 6) + 1);
//		serialPrintf("PA PLL programmable multiplier = %d\n", pa_pllm);

		/* Tells the divider value for the PA PLL */
		pa_plld = (((papllctl0val & PA_PLL_CLKR_MASK) >> 0) +1);
//		serialPrintf("PA PLL programmable divider = %d\n", pa_plld);

		// Compute the real pass clk freq (*100)
		pass_freq = (12288 * (pa_pllm) / (pa_plld) / (1));

		// Displayed frequency in MHz
		pass_freM = pass_freq / 100;

		// passclk freq first decimal if freq expressed in MHz
		pass_freD = ((pass_freq - pass_freM * 100) + 5) / 10;

		// Add roundup unit to MHz displayed and reajust decimal value if necessary...
		if (pass_freD > 9)
		{
			pass_freD = pass_freD - 10;
			pass_freM = pass_freM + 1;
		}

//		serialPrintf("PLL3 Setup for PASSCLK @ %d.%d MHz... \n", pass_freM, pass_freD );
//		serialPrintf("PLL3 Setup... Done.\n" );

		return CSL_SOK;

	}
	else
	{
//		serialPrintf("DSP core #%d cannot set PA PLL \n",DNUM);
		return CSL_ESYS_FAIL;
	}

}

/*DDR3 PLL settings for 625 MHz so DDR2 RUN 1250MHz*/
/*ddr3Clk = DDRCLK_IN/PLLD*PLLM/2*/
#define PLLM_DDR3 		(9)
#define PLLD_DDR3 		(0)

INT32 pll2Init(void) /*ddr3 pll*/
{
	  uint32_t temp;

	/* Unlock the Boot Config */
	CSL_BootCfgUnlockKicker();

	/* Usage Note 9: For optimal PLL operation, the ENSAT bit in the PLL control *
	 * registers for the Main PLL, DDR3 PLL, and PA PLL should be set to 1.      *
	 * The PLL initialization sequence in the boot ROM sets this bit to 0 and    *
	 * could lead to non-optimal PLL operation. Software can set the bit to the  *
	 * optimal value of 1 after boot                                             *
	 * DDR3PLLCTL1_REG Bit map                                                   *
	 * |31...7   |6     |5 4       |3...0      |                                 *
	 * |Reserved |ENSAT |Reserved  |BWADJ[11:8]|                                 */

	DDR3PLLCTL1_REG |= 0x00000040;

	/* Wait for the PLL Reset time (min: 1000 ns)                                */
	/*pll_delay(1400);*/

	/* Put the PLL in Bypass Mode                                                *
	 * DDR3PLLCTL0_REG Bit map                                                     *
	 * |31...24    |23     |22...19       |18...6   |5...0 |                     *
	 * |BWADJ[7:0] |BYPASS |Reserved      |PLLM     |PLLD  |                     */

	DDR3PLLCTL0_REG |= 0x00800000; /* Set the Bit 23 */

	/*Wait 4 cycles for the slowest of PLLOUT or reference clock source (CLKIN)*/
	/*pll_delay(4);*/

	/* Wait for the PLL Reset time (min: 1000 ns)                                */
	/*pll_delay(1400);*/

	/* Program the necessary multipliers/dividers and BW adjustments             */
	/* Set the divider values */
	DDR3PLLCTL0_REG &= ~(0x0000003F);
	DDR3PLLCTL0_REG |= (PLLD_DDR3 & 0x0000003F);

	/* Set the Multipler values */
	DDR3PLLCTL0_REG &= ~(0x0007FFC0);
	DDR3PLLCTL0_REG |= ((PLLM_DDR3 << 6) & 0x0007FFC0);

	/* Set the BWADJ */
	temp = ((PLLM_DDR3 + 1) >> 1) - 1;
	DDR3PLLCTL0_REG &= ~(0xFF000000);
	DDR3PLLCTL0_REG |= ((temp << 24) & 0xFF000000);
	DDR3PLLCTL1_REG &= ~(0x0000000F);
	DDR3PLLCTL1_REG |= ((temp >> 8) & 0x0000000F);

	/* In PLL Controller, reset the PLL (bit 13) in DDR3PLLCTL1_REG register       */
	DDR3PLLCTL1_REG |= 0x00002000;

	/*Wait for PLL to lock min 5 micro seconds*/
	pll_delay(7000);

	/*In DDR3PLLCTL1_REG, write PLLRST = 0 to bring PLL out of reset */
	DDR3PLLCTL1_REG &= ~(0x00002000);

	/*Wait for PLL to lock min 50 micro seconds*/
	pll_delay(70000);

	/* Put the PLL in PLL Mode                                                   *
	 * DDR3PLLCTL0_REG Bit map                                                   *
	 * |31...24    |23     |22...19       |18...6   |5...0 |                     *
	 * |BWADJ[7:0] |BYPASS |Reserved      |PLLM     |PLLD  |                     */
	DDR3PLLCTL0_REG &= ~(0x00800000); /* ReSet the Bit 23 */

	return 0;
}









INT32 dsp667x_pllInit(void* pCfg)
{

    pll0Init();
    //PowerUpDomains();
	pll1Init();
	pll2Init();

	return 0x0;
}

unsigned int getcore_clk ()
{
	unsigned int pllM,preDiv,dsp_freq;
	unsigned int* pll_mult      = ( unsigned int* )PLL1_PLLM;
	unsigned int* pll_stat      = ( unsigned int* )PLL1_STAT;
    /* Unlock the Boot Config */
	KICK0 = KICK0_UNLOCK;
	KICK1 = KICK1_UNLOCK;


    pllM   = *pll_mult  & 0x3F;
    preDiv = MAINPLLCTL0_REG& 0x3F;

    /* Make sure no GO operation is pending*/
    while((*pll_stat) & 0x00000001);

	KICK0 = KICK_LOCK;
	KICK1 = KICK_LOCK;
	dsp_freq =(pllM+1)>>1;

	dsp_freq = (dsp_freq * PLATFORM_BASE_CLK_RATE_MHZ)/(preDiv + 1);
	return (dsp_freq);
 }



 LOCAL INT32 corePllcHwSetup(PllcHwSetup *hwSetup)
 {
     INT32 status = 0;
     volatile UINT32 i = 0,loopCount;
     UINT32 temp;
 
     dsp667x_bootCfgUnLock();;  //Unlock the Boot Config
     
     pllDelay(140056);           //Wait for Stabilization time (min 100 us)
 
     temp = SECCTL_REG & 0x00800000;
     if(temp != 0) /* PLL BYPASS is enabled, we assume if not in Bypass ENSAT = 1 */
     {
         MAINPLLCTL1_REG = MAINPLLCTL1_REG | 0x00000040;
         PLLCTL_REG &= ~(1 << 0);    //Bypass mode
         PLLCTL_REG &= ~(1 << 5);    //PLLEN bit is disabled
         pllDelay(225);              //Wait for 4 RefClks(to make sure the PLL controller mux switches properly to the bypass)
         SECCTL_REG |= 0x00800000;   //PLL Bypass enabled
         PLLCTL_REG |= 0x00000002;   //Power Down the PLL
         pllDelay(14005);            //Wait for at least 5 娓璼 based on the reference clock CLKIN
         PLLCTL_REG &= ~(0x00000002);    //Power up the PLL
     }
     else
     {
         PLLCTL_REG &= ~(1 << 0);    //Bypass mode
         PLLCTL_REG &= ~(1 << 5);    //PLLEN bit is disabled
         pllDelay(225);              //Wait for 4 RefClks(to make sure the PLL controller mux switches properly to the bypass)
     }
 
     PLLM_REG = (hwSetup->pllM & 0x0000003F);    //PLL multiplier bits
     temp = (hwSetup->pllM & 0x1FC0) >> 6;       //bits[12:6]
     MAINPLLCTL0_REG &= ~(0x0007F000);           //Clear PLLM field
     MAINPLLCTL0_REG |= ((temp << 12) & 0x0007F000);
 
     temp = ((hwSetup->pllM + 1)>> 1) - 1;       //BWADJ[7:0]
     MAINPLLCTL0_REG &= ~(0xFF000000);
     MAINPLLCTL0_REG |= ((temp << 24) & 0xFF000000);
     MAINPLLCTL1_REG &= ~(0x0000000F);
     MAINPLLCTL1_REG |= ((temp >> 8) & 0x0000000F);
 
     MAINPLLCTL0_REG &= ~(0x0000003F);           //Set the pll divider
     MAINPLLCTL0_REG |= (hwSetup->preDiv & 0x0000003F);
 
     SECCTL_REG &= ~(0x00780000);
     SECCTL_REG |= ((1 << 19) & 0x00780000);     //In SECCTL, write OD (Output Divide) = 1, Divide frequency by 2
 
     while(1)
     {
         pllDelay(300);
         if((PLL1_STAT & 0x00000001) == 0)
         {
             break;
         }
     }
 
     PLL1_DIV2 = (0x8000) | (hwSetup->pllDiv2);
     PLL1_DIV5 = (0x8000) | (hwSetup->pllDiv5);
     PLL1_DIV8 = (0x8000) | (hwSetup->pllDiv8);
     PLLALNCTL_REG |= ((1 << 1) | (1 << 4) | (1 << 7));  //Program ALNCTLn
     PLLCMD_REG |= 0x00000001;
 
     while(1)
     {
         pllDelay(300);
         if((PLL1_STAT & 0x00000001) == 0)
         {
             break;
         }
     }
 
     PLLCTL_REG |= 0x00000008;       //Place PLL in Reset
     pllDelay(14006);                //Wait for at least 7 娓璼 based on the reference clock CLKIN
     PLLCTL_REG &= ~(0x00000008);    //PLL reset is de-asserted
 
     pllDelay(140056 >> 1);          //Wait for at least 500 鑴�CLKIN cycles 鑴�(PLLD + 1) (PLL lock time)
 
     SECCTL_REG &= ~(0x00800000);    //Release Bypass
     PLLCTL_REG |= (1 << 0);         //PLL enable
 
     return status;
 }
 
