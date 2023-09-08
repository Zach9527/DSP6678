/*
 * DDR3.c
 *
 *  Created on: 2012-8-13
 *      Author: Administrator
 */
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <c6x.h>
#include "types.h"
#include "ti/csl/csl_types.h"
#include <ti/csl/csl_chip.h>
#include "ti/csl/csl_chipAux.h"
#include "ti/csl/cslr_device.h"
#include "ti/csl/csl_emif4f.h"
#include "ti/csl/csl_emif4fAux.h"
#include "ti/csl/csl_bootcfg.h"
#include "ti/csl/csl_bootcfgAux.h"
#include "ti/csl/csl_pllcAux.h"
#include "ti/csl/csl_xmcAux.h"
#define   DDR3PLLCTL0_REG       (*((volatile uint32_t *) 0x02620330))
#define   DDR3PLLCTL1_REG       (*((volatile uint32_t *) 0x02620334))
#define   OBSCLCTL_REG          (*((volatile uint32_t *) 0x026203AC))
/* DDR3 PLL settings for 1333 MHz */
//供给DDR3的时钟为100MHz
#define PLLM_DDR3 9//39
#define PLLD_DDR3 0//2
static void pll_delay(uint32_t ix)
{
    while (ix--) {
        asm("   NOP");
    }
}
static void platform_delaycycles(uint32_t cycles)
{
	uint32_t start_val  = CSL_chipReadTSCL();

	while ((CSL_chipReadTSCL() - start_val) < cycles);

    return;
}
CSL_Status SetDDR3PllConfig(void)
{

    uint32_t ddr3pllctl0val = DDR3PLLCTL0_REG;
    uint32_t obsclkval = OBSCLCTL_REG;
    uint32_t ddr3_pllm = PLLM_DDR3;
    uint32_t ddr3_plld = PLLD_DDR3;
    uint32_t temp;

    /* Unlock the Boot Config */
    CSL_BootCfgUnlockKicker();

    if (DNUM == 0)
    {
        /* Usage Note 9: For optimal PLL operation, the ENSAT bit in the PLL control *
         * registers for the Main PLL, DDR3 PLL, and PA PLL should be set to 1.      *
         * The PLL initialization sequence in the boot ROM sets this bit to 0 and    *
         * could lead to non-optimal PLL operation. Software can set the bit to the  *
         * optimal value of 1 after boot                                             *
         * DDR3PLLCTL1_REG Bit map                                                     *
         * |31...7   |6     |5 4       |3...0      |                                 *
         * |Reserved |ENSAT |Reserved  |BWADJ[11:8]|                                 */

        DDR3PLLCTL0_REG |= 0x00000040;

        /* Wait for the PLL Reset time (min: 1000 ns)                                */
        /*pll_delay(1400);*/

        /* Put the PLL in Bypass Mode                                                *
         * DDR3PLLCTL0_REG Bit map                                                     *
         * |31...24    |23     |22...19       |18...6   |5...0 |                     *
         * |BWADJ[7:0] |BYPASS |Reserved      |PLLM     |PLLD  |                     */

        DDR3PLLCTL0_REG |= 0x00800000; /* Set the Bit 23 */

        /*Wait 4 cycles for the slowest of PLLOUT or reference clock source (CLKIN)*/
        /*pll_delay(4);*/

        /* In PLL Controller, reset the PLL (bit 13) in DDR3PLLCTL1_REG register       */
        DDR3PLLCTL1_REG |= 0x00002000;

        /* Wait for the PLL Reset time (min: 1000 ns)                                */
        /*pll_delay(1400);*/

        /* Program the necessary multipliers/dividers and BW adjustments             */
        /* Set the divider values */
        DDR3PLLCTL0_REG &= ~(0x0000003F);
        DDR3PLLCTL0_REG |= (ddr3_plld & 0x0000003F);

        /* Set the Multipler values */
        DDR3PLLCTL0_REG &= ~(0x0007FFC0);
        DDR3PLLCTL0_REG |= ((ddr3_pllm << 6) & 0x0007FFC0 );

        /* Set the BWADJ */
        temp = ((ddr3_pllm + 1) >> 1) - 1;
        DDR3PLLCTL0_REG &= ~(0xFF000000);
        DDR3PLLCTL0_REG |= ((temp << 24) & 0xFF000000);
        DDR3PLLCTL1_REG &= ~(0x0000000F);
        DDR3PLLCTL1_REG |= ((temp >> 8) & 0x0000000F);

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

        ddr3pllctl0val = DDR3PLLCTL0_REG;

        /* Tells the multiplier value for the DDR3 PLL */
        ddr3_pllm = (((ddr3pllctl0val & 0x0007FFC0) >> 6) + 1);
        printf("DDR3 PLL programmable multiplier = %d\n", ddr3_pllm);

        /* Tells the divider value for the DDR3 PLL */
        ddr3_plld = (((ddr3pllctl0val & 0x0000003F) >> 0) +1);
        printf("DDR3 PLL programmable divider = %d\n", ddr3_plld);

        printf("PLL2 Setup... Done.\n" );

        return CSL_SOK;

    }
    else
    {
        printf("DSP core %d cannot set DDR3 PLL \n",DNUM);
        return CSL_ESYS_FAIL;
    }
}


/*--------------------------------------------------------------*/
/* xmc_setup()                                                  */
/* XMC MPAX register setting to access DDR3 config space        */
/*--------------------------------------------------------------*/
void xmc_setup()
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

/* Set the desired DDR3 configuration -- assumes 66.67 MHz DDR3 clock input */
CSL_Status DDR3Init()
{

    CSL_Status status = CSL_SOK;
    volatile unsigned int loopCount;
    uint32_t ddr3config, ddrPhyCtrl;
    uint8_t ddrPHYReadLatency;
    EMIF4F_TIMING1_CONFIG sdram_tim1;
    EMIF4F_TIMING2_CONFIG sdram_tim2;
    EMIF4F_TIMING3_CONFIG sdram_tim3;
    EMIF4F_OUTPUT_IMP_CONFIG    zqcfg;
    EMIF4F_PWR_MGMT_CONFIG      pwrmgmtcfg;
    EMIF4F_SDRAM_CONFIG         sdramcfg;

    CSL_BootCfgUnlockKicker();

    /* Wait for PLL to lock = min 500 ref clock cycles.
       With refclk = 100MHz, = 5000 ns = 5us */
    platform_delaycycles(50000);

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

    /**************** 3.3 Partial Automatic Leveling ********************/
    ddr3config = 0x00000001;  CSL_BootCfgSetDDRConfig(2,  ddr3config);
    ddr3config = 0x00000001;  CSL_BootCfgSetDDRConfig(3,  ddr3config);
    ddr3config = 0x0000000b;  CSL_BootCfgSetDDRConfig(4,  ddr3config);
    ddr3config = 0x0000000b;  CSL_BootCfgSetDDRConfig(5,  ddr3config);
    ddr3config = 0x00000020;  CSL_BootCfgSetDDRConfig(6,  ddr3config);
    ddr3config = 0x00000020;  CSL_BootCfgSetDDRConfig(7,  ddr3config);
    ddr3config = 0x0000002a;  CSL_BootCfgSetDDRConfig(8,  ddr3config);
    ddr3config = 0x0000002a;  CSL_BootCfgSetDDRConfig(9,  ddr3config);
    ddr3config = 0x00000015;  CSL_BootCfgSetDDRConfig(10, ddr3config);

    ddr3config = 0x0000005e;  CSL_BootCfgSetDDRConfig(14,  ddr3config);
    ddr3config = 0x0000005e;  CSL_BootCfgSetDDRConfig(15,  ddr3config);
    ddr3config = 0x00000059;  CSL_BootCfgSetDDRConfig(16,  ddr3config);
    ddr3config = 0x00000068;  CSL_BootCfgSetDDRConfig(17,  ddr3config);
    ddr3config = 0x0000007d;  CSL_BootCfgSetDDRConfig(18,  ddr3config);
    ddr3config = 0x0000007d;  CSL_BootCfgSetDDRConfig(19,  ddr3config);
    ddr3config = 0x00000087;  CSL_BootCfgSetDDRConfig(20,  ddr3config);
    ddr3config = 0x00000087;  CSL_BootCfgSetDDRConfig(21,  ddr3config);
    ddr3config = 0x00000073;  CSL_BootCfgSetDDRConfig(22,  ddr3config);

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
    /*    hEmif->SDRAM_REF_CTRL    = 0x00005162; */
    CSL_EMIF4F_EnableInitRefresh();
    //CSL_EMIF4F_SetRefreshRate(0x00005162);
      CSL_EMIF4F_SetRefreshRate(0x000030d4);
    /*    hEmif->SDRAM_TIM_1   = 0x1113783C; */

    sdram_tim1.t_wtr    = 3;
    sdram_tim1.t_rrd    = 4;
    sdram_tim1.t_rc     = 0x14;
    sdram_tim1.t_ras    = 0xe;
    sdram_tim1.t_wr     = 5;
    sdram_tim1.t_rcd    = 5;
    sdram_tim1.t_rp     = 5;
    CSL_EMIF4F_SetTiming1Config(&sdram_tim1);

    /*    hEmif->SDRAM_TIM_2   = 0x30717FE3; */
    sdram_tim2.t_cke    = 2;
    sdram_tim2.t_rtp    = 3;
    sdram_tim2.t_xsrd   = 0x1FF;
    sdram_tim2.t_xsnr   = 0x43;
    sdram_tim2.t_xp     = 2;
    sdram_tim2.t_odt    = 0;
    CSL_EMIF4F_SetTiming2Config (&sdram_tim2);

    /*    hEmif->SDRAM_TIM_3   = 0x559F86AF; */
    sdram_tim3.t_rasMax     = 0xF;
    sdram_tim3.t_rfc        = 0x3f;
    sdram_tim3.t_tdqsckmax  = 0;
    sdram_tim3.zq_zqcs      = 0x3F;
    sdram_tim3.t_ckesr      = 3;
    sdram_tim3.t_csta       = 0x5;
    sdram_tim3.t_pdll_ul    = 0x5;
    CSL_EMIF4F_SetTiming3Config (&sdram_tim3);

    /*    hEmif->DDR_PHY_CTRL_1   = 0x0010010F; */
    ddrPHYReadLatency   = 0x0F;
    ddrPhyCtrl          = (0x08008);
    CSL_EMIF4F_SetPhyControl(ddrPhyCtrl,  ddrPHYReadLatency);

    /*    hEmif->ZQ_CONFIG        = 0x70073214; */
    zqcfg.zqRefInterval     = 0x3214;
    zqcfg.zqZQCLMult        = 3;
    zqcfg.zqZQCLInterval    = 1;
    zqcfg.zqSFEXITEn        = 1;
    zqcfg.zqDualCSEn        = 1;
    zqcfg.zqCS0En           = 1;
    zqcfg.zqCS1En           = 0;
    CSL_EMIF4F_SetOutputImpedanceConfig(&zqcfg);

    /*    hEmif->PWR_MGMT_CTRL    = 0x0; */
    pwrmgmtcfg.csTime           = 0;
    pwrmgmtcfg.srTime           = 0;
    pwrmgmtcfg.lpMode           = 0;
    pwrmgmtcfg.dpdEnable        = 0;
    pwrmgmtcfg.pdTime           = 0;
    CSL_EMIF4F_SetPowerMgmtConfig  (&pwrmgmtcfg);

    /* New value with DYN_ODT disabled and SDRAM_DRIVE = RZQ/7 */
    /*    hEmif->SDRAM_CONFIG     = 0x63062A32; */
    CSL_EMIF4F_GetSDRAMConfig (&sdramcfg);
    sdramcfg.pageSize           = 2;
    sdramcfg.eBank              = 0;
    sdramcfg.iBank              = 3;
    sdramcfg.rowSize            = 5;
    sdramcfg.CASLatency         = 10;
    sdramcfg.narrowMode         = 0;
    sdramcfg.CASWriteLat        = 2;
    sdramcfg.SDRAMDrive         = 1;
    sdramcfg.disableDLL         = 0;
    sdramcfg.dynODT             = 0;
    sdramcfg.ddrDDQS            = 0;
    sdramcfg.ddrTerm            = 3;
    sdramcfg.iBankPos           = 0;
    sdramcfg.type               = 3;
    CSL_EMIF4F_SetSDRAMConfig (&sdramcfg);

    pll_delay(840336); /*Wait 600us for HW init to complete*/

    /* Refresh rate = (7.8*666MHz] */
    /*    hEmif->SDRAM_REF_CTRL   = 0x00001450;     */
    CSL_EMIF4F_SetRefreshRate(0x00000c30);
   // CSL_EMIF4F_SetRefreshRate(0x00001450);
    /***************** 4.2.1 Partial automatic leveling ************/
    /*    hEmif->RDWR_LVL_RMP_CTRL      =  0x80000000; */
    CSL_EMIF4F_SetLevelingRampControlInfo(1, 0, 0, 0, 0);

    /* Trigger full leveling - This ignores read DQS leveling result and uses ratio forced value */
    /*    hEmif->RDWR_LVL_CTRL          =  0x80000000; */
    CSL_EMIF4F_SetLevelingControlInfo(1, 0, 0, 0, 0);

    /************************************************************
      Wait for min 1048576 DDR clock cycles for leveling to complete
      = 1048576 * 1.5ns = 1572864ns = 1.57ms.
      Actual time = ~10-15 ms
     **************************************************************/
    pll_delay(4201680); //Wait 3ms for leveling to complete

    return (status);

}


