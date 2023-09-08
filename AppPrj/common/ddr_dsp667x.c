/*


 文件名称：ddr_dsp6678.c
摘要：主要实现dsp6678的DDR3初始化控制
*/
/* 修改历史:
2016.3.12,chengqb创建文件
*/

/* includes */ 

#include "KeyStone_common.h"
#include "datatype.h"
#include "delay.h"
#include "dsp667x.h"
#include "ddr_dsp667x.h"

#define PARAMTER_FLAG_MASK			(0x12345AA5)
/* defines */ 
#define DDR_FREQ  1000K

/* typedefs */  

/* globals */ 

/* locals */

/* local function declarations */
void platform_delaycycles(UINT32 cycles);
LOCAL void pll_delay(UINT32 ix);

/*local function define*/
 void platform_delaycycles(uint32_t cycles)
{
	UINT32 start_val  = CSL_chipReadTSCL();

	while ((CSL_chipReadTSCL() - start_val) < cycles);

    return;
}

LOCAL void pll_delay(uint32_t ix)
{
    while (ix--)
	{
        asm("   NOP 5 ");
		asm("   NOP 5 ");
	 	asm("   NOP 5 ");
    }
}
/*--------------------------------------------------------------*/
/* xmc_setup()                                                  */
/* XMC MPAX register setting to access DDR3 config space        */
/*--------------------------------------------------------------*/
static void xmc_setup(void)
{
    /* mapping for ddr emif registers XMPAX*2 */
    CSL_XMC_XMPAXL    mpaxl;
    CSL_XMC_XMPAXH    mpaxh;

    /* base addr + seg size (64KB)*/    //"1B"-->"B" by xj */
    mpaxh.bAddr     = (0x2100000B >> 12);
    mpaxh.segSize   = (0x2100000B & 0x0000001F);

    /* replacement addr + perm*/
    mpaxl.rAddr     = 0x100000;
    mpaxl.sr        = 1;
    mpaxl.sw        = 1;
    mpaxl.sx        = 1;
    mpaxl.ur        = 1;
    mpaxl.uw        = 1;
    mpaxl.ux        = 1;

    /* set the xmpax for index2 */
    CSL_XMC_setXMPAXH(2, &mpaxh);
    CSL_XMC_setXMPAXL(2, &mpaxl);
}

/*global function define*/ 
INT32 ddrInit(DDR_PARAMETER* pDdrCfg)
{
	uint32_t ddr3config, ddrPhyCtrl;
	uint8_t ddrPHYReadLatency;
	EMIF4F_OUTPUT_IMP_CONFIG zqcfg;
	EMIF4F_PWR_MGMT_CONFIG pwrmgmtcfg;

	xmc_setup();

	CSL_BootCfgUnlockKicker();

	/* Wait for PLL to lock = min 500 ref clock cycles.
	   With 0 = 100MHz, = 5000 ns = 5us */
	pll_delay(50000);

	/**************** 3.3 Leveling Register Configuration ********************/
	CSL_BootCfgGetDDRConfig(0, &ddr3config);
	ddr3config &= ~(0x007FE000);  // clear ctrl_slave_ratio field
	CSL_BootCfgSetDDRConfig(0, ddr3config);

	CSL_BootCfgGetDDRConfig(0, &ddr3config);
	ddr3config |= 0x00200000;     // set ctrl_slave_ratio to 0x100
	CSL_BootCfgSetDDRConfig(0, ddr3config);

	CSL_BootCfgGetDDRConfig(12, &ddr3config);
	ddr3config |= 0x08000000;    // Set invert_clkout = 1
	CSL_BootCfgSetDDRConfig(12, ddr3config);

	CSL_BootCfgGetDDRConfig(0, &ddr3config);
	ddr3config |= 0xF;            // set dll_lock_diff to 15
	CSL_BootCfgSetDDRConfig(0, ddr3config);

	CSL_BootCfgGetDDRConfig(23, &ddr3config);
	ddr3config |= 0x00000200;    // See section 4.2.1, set for partial automatic levelling
	CSL_BootCfgSetDDRConfig(23, ddr3config);

//	/**************** 3.3 Partial Automatic Leveling ********************/
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(2,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(3,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(4,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(5,  ddr3config);
	ddr3config = 0x0000004A;  CSL_BootCfgSetDDRConfig(6,  ddr3config);
	ddr3config = 0x00000049;  CSL_BootCfgSetDDRConfig(7,  ddr3config);
	ddr3config = 0x0000005A;  CSL_BootCfgSetDDRConfig(8,  ddr3config);
	ddr3config = 0x00000057;  CSL_BootCfgSetDDRConfig(9,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(10, ddr3config);

	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(14,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(15,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(16,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(17,  ddr3config);
	ddr3config = 0x0000007F;  CSL_BootCfgSetDDRConfig(18,  ddr3config);
	ddr3config = 0x00000080;  CSL_BootCfgSetDDRConfig(19,  ddr3config);
	ddr3config = 0x0000008A;  CSL_BootCfgSetDDRConfig(20,  ddr3config);
	ddr3config = 0x0000008D;  CSL_BootCfgSetDDRConfig(21,  ddr3config);
	ddr3config = 0x00000000;  CSL_BootCfgSetDDRConfig(22,  ddr3config);


	/*Do a PHY reset. Toggle DDR_PHY_CTRL_1 bit 15 0->1->0 */
	CSL_EMIF4F_GetPhyControl(&ddrPhyCtrl, &ddrPHYReadLatency);
	ddrPhyCtrl &= ~(0x00008000);
	CSL_EMIF4F_SetPhyControl(ddrPhyCtrl,  ddrPHYReadLatency);

	CSL_EMIF4F_GetPhyControl(&ddrPhyCtrl, &ddrPHYReadLatency);
	ddrPhyCtrl |= (0x00008000);
	CSL_EMIF4F_SetPhyControl(ddrPhyCtrl,  ddrPHYReadLatency);

	CSL_EMIF4F_GetPhyControl(&ddrPhyCtrl, &ddrPHYReadLatency);
	ddrPhyCtrl &= ~(0x00008000);
	CSL_EMIF4F_SetPhyControl(ddrPhyCtrl,  ddrPHYReadLatency);

	/***************** 3.4 Basic Controller and DRAM configuration ************/
	/* enable configuration */
	CSL_EMIF4F_EnableInitRefresh();
	CSL_EMIF4F_SetRefreshRate(0x000061A7);



	//CSL_EMIF4F_SetTiming1Config(&sdram_tim1);
	hEmif->SDRAM_TIM_1 = 0x1557B9BD;

	//CSL_EMIF4F_SetTiming2Config (&sdram_tim2);
	hEmif->SDRAM_TIM_2 = 0x40D77FEC;

	//CSL_EMIF4F_SetTiming3Config (&sdram_tim3);
	hEmif->SDRAM_TIM_3 = 0x55BF8CFF;

	ddrPHYReadLatency   = 0x0F;
	ddrPhyCtrl          = (0x08008);
	CSL_EMIF4F_SetPhyControl(ddrPhyCtrl,  ddrPHYReadLatency);

	zqcfg.zqRefInterval     = 0x6418;//0x3214;
	zqcfg.zqZQCLMult        = 3;
	zqcfg.zqZQCLInterval    = 3;
	zqcfg.zqSFEXITEn        = 1;
	zqcfg.zqDualCSEn        = 1;
	zqcfg.zqCS0En           = 1;
	zqcfg.zqCS1En           = 0;
	CSL_EMIF4F_SetOutputImpedanceConfig(&zqcfg);

	pwrmgmtcfg.csTime           = 0;
	pwrmgmtcfg.srTime           = 0;
	pwrmgmtcfg.lpMode           = 0;
	pwrmgmtcfg.dpdEnable        = 0;
	pwrmgmtcfg.pdTime           = 0;
	CSL_EMIF4F_SetPowerMgmtConfig(&pwrmgmtcfg);

	/* New value with DYN_ODT disabled and SDRAM_DRIVE = RZQ/7 */
	//CSL_EMIF4F_SetSDRAMConfig (&sdramcfg);
	hEmif->SDRAM_CONFIG = 0x63067B32;


	pll_delay(840336); /*Wait 600us for HW init to complete*/

	/* Refresh rate = (7.8*625MHz] */
	CSL_EMIF4F_SetRefreshRate(0x00001869);


	/***************** 4.2.1 Partial automatic leveling ************/
	CSL_EMIF4F_SetLevelingRampControlInfo(1, 0, 0, 0, 0);

	/* Trigger full leveling - This ignores read DQS leveling result and uses ratio forced value */
	CSL_EMIF4F_SetLevelingControlInfo(1, 0, 0, 0, 0);

	/************************************************************
	  Wait for min 1048576 DDR clock cycles for leveling to complete
	  = 1048576 * 1.5ns = 1572864ns = 1.57ms.
	  Actual time = ~10-15 ms
	 **************************************************************/
	pll_delay(4201680); //Wait 3ms for leveling to complete

   return 0;
}

INT32 dsp667x_ddrInit(void* pCfg)
{
	DDR_PARAMETER* pDdrCfg = (DDR_PARAMETER*)pCfg;	
	DDR_PARAMETER defaultCfg;

	if(pDdrCfg == NULL)
	{
		pDdrCfg = &defaultCfg;
	}
	ddrInit(pDdrCfg);

	return 0x0;
}






