/******************************************************************************

  Copyright (C), 2001-2012, Texas Instrument.

 ******************************************************************************
  File Name     : KeyStone_common.c
  Version       : Initial Draft
  Author        : Brighton Feng
  Created       : 2010-12-12
  Last Modified : 
  Description   : KeyStone common miscellaneous functions and definitions
  History       :
  1.Date        : 2010-12-12
    Author      : Brighton Feng
    Modification: Created file

  2.Date         : 2012-10-6
    Author       : Brighton Feng
    Modification : Add memory protection and EDC configuration

  3.Date         : 2014-12-8
    Author       : Brighton Feng
    Modification : Add common device, CPU, interrupt initialization functions.
                   Print device information including device type, speed grade, 
                   boot mode, required voltage, ID…
                   Add EDMA enable/disable functions.
                   To support square wave generation by timer.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_bootcfgAux.h>
#include <ti/csl/csl_pscAux.h>
#include <ti/csl/cslr_chip.h>
#include <ti/csl/csl_edma3.h>
#include <ti/csl/CSL_msmc.h>
#include <ti/csl/CSL_msmcAux.h>


#include "common.h"
#include "dsp667x.h"
/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/
CSL_XmcRegs * gpXMC_regs = (CSL_XmcRegs *) CSL_XMC_CONFIG_REGS;
CSL_CgemRegs * gpCGEM_regs = (CSL_CgemRegs *)CSL_CGEM0_5_REG_BASE_ADDRESS_REGS;
CSL_BootcfgRegs * gpBootCfgRegs = (CSL_BootcfgRegs *)CSL_BOOT_CFG_REGS;
CSL_PllcRegs * gpPLLC_regs = (CSL_PllcRegs * )CSL_PLL_CONTROLLER_REGS;
CSL_PscRegs *  gpPSC_regs =   (CSL_PscRegs *)CSL_PSC_REGS;
CSL_MsmcRegs * gpMSMC_regs = (CSL_MsmcRegs *)CSL_MSMC_CONFIG_REGS;
CSL_GpioRegs * gpGPIO_regs= (CSL_GpioRegs * )CSL_GPIO_REGS;

CSL_CPINTCRegs* gpCIC0_regs = (CSL_CPINTCRegs*)CSL_CP_INTC_0_REGS;
CSL_CPINTCRegs* gpCIC1_regs = (CSL_CPINTCRegs*)CSL_CP_INTC_1_REGS;
/*The register pointer for the CIC routing events DSP core.
By default, it is CIC0; but for core 4~7 of C6678, it is CIC1*/
CSL_CPINTCRegs* gpCIC_regs= (CSL_CPINTCRegs*)CSL_CP_INTC_0_REGS;

CSL_TpccRegs*  gpEDMA_CC0_regs  = (CSL_TpccRegs*)CSL_EDMA0CC_REGS;
CSL_TpccRegs*  gpEDMA_CC1_regs  = (CSL_TpccRegs*)CSL_EDMA1CC_REGS;
CSL_TpccRegs*  gpEDMA_CC2_regs  = (CSL_TpccRegs*)CSL_EDMA2CC_REGS;
CSL_TpccRegs*  gpEDMA_CC_regs[3]  = {
	(CSL_TpccRegs*)CSL_EDMA0CC_REGS,
	(CSL_TpccRegs*)CSL_EDMA1CC_REGS,
	(CSL_TpccRegs*)CSL_EDMA2CC_REGS
};

CSL_TptcRegs * gpEDMA_TC_0_0_regs=(CSL_TptcRegs *) CSL_EDMA0TC0_REGS;
CSL_TptcRegs * gpEDMA_TC_0_1_regs=(CSL_TptcRegs *) CSL_EDMA0TC1_REGS;
CSL_TptcRegs * gpEDMA_TC_1_0_regs=(CSL_TptcRegs *) CSL_EDMA1TC0_REGS;
CSL_TptcRegs * gpEDMA_TC_1_1_regs=(CSL_TptcRegs *) CSL_EDMA1TC1_REGS;
CSL_TptcRegs * gpEDMA_TC_1_2_regs=(CSL_TptcRegs *) CSL_EDMA1TC2_REGS;
CSL_TptcRegs * gpEDMA_TC_1_3_regs=(CSL_TptcRegs *) CSL_EDMA1TC3_REGS;
CSL_TptcRegs * gpEDMA_TC_2_0_regs=(CSL_TptcRegs *) CSL_EDMA2TC0_REGS;
CSL_TptcRegs * gpEDMA_TC_2_1_regs=(CSL_TptcRegs *) CSL_EDMA2TC1_REGS;
CSL_TptcRegs * gpEDMA_TC_2_2_regs=(CSL_TptcRegs *) CSL_EDMA2TC2_REGS;
CSL_TptcRegs * gpEDMA_TC_2_3_regs=(CSL_TptcRegs *) CSL_EDMA2TC3_REGS;

CSL_TptcRegs * gpEDMA_TC_regs[10]= {
	(CSL_TptcRegs *) CSL_EDMA0TC0_REGS,
	(CSL_TptcRegs *) CSL_EDMA0TC1_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC0_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC1_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC2_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC3_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC0_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC1_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC2_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC3_REGS
};

CSL_TmrPlusRegs * gpTimer0Regs = (CSL_TmrPlusRegs *)CSL_TIMER_0_REGS;
CSL_TmrPlusRegs * gpTimer1Regs = (CSL_TmrPlusRegs *)CSL_TIMER_1_REGS;
CSL_TmrPlusRegs * gpTimer2Regs = (CSL_TmrPlusRegs *)CSL_TIMER_2_REGS;
CSL_TmrPlusRegs * gpTimer3Regs = (CSL_TmrPlusRegs *)CSL_TIMER_3_REGS;
CSL_TmrPlusRegs * gpTimer4Regs = (CSL_TmrPlusRegs *)CSL_TIMER_4_REGS;
CSL_TmrPlusRegs * gpTimer5Regs = (CSL_TmrPlusRegs *)CSL_TIMER_5_REGS;
CSL_TmrPlusRegs * gpTimer6Regs = (CSL_TmrPlusRegs *)CSL_TIMER_6_REGS;
CSL_TmrPlusRegs * gpTimer7Regs = (CSL_TmrPlusRegs *)CSL_TIMER_7_REGS;
CSL_TmrPlusRegs * gpTimer8Regs = (CSL_TmrPlusRegs *)(CSL_TIMER_7_REGS+(CSL_TIMER_7_REGS-CSL_TIMER_6_REGS));
CSL_TmrPlusRegs * gpTimerRegs[9] = {
	(CSL_TmrPlusRegs *)CSL_TIMER_0_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_1_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_2_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_3_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_4_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_5_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_6_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_7_REGS,
	(CSL_TmrPlusRegs *)(CSL_TIMER_7_REGS+(CSL_TIMER_7_REGS-CSL_TIMER_6_REGS))
};

/*MPU for peripherals registers and data space*/
CSL_MpuRegs * gpMPU0_regs= (CSL_MpuRegs *)CSL_MPU_0_REGS;
CSL_MpuRegs * gpMPU1_regs= (CSL_MpuRegs *)CSL_MPU_1_REGS;
CSL_MpuRegs * gpMPU2_regs= (CSL_MpuRegs *)CSL_MPU_2_REGS;
CSL_MpuRegs * gpMPU3_regs= (CSL_MpuRegs *)CSL_MPU_3_REGS;

CSL_Emif4fRegs * gpDDR_regs= (CSL_Emif4fRegs *)CSL_DDR3_EMIF_CONFIG_REGS;
extern unsigned int gDSP_Core_Speed_Hz; 	//DSP core clock speed in Hz

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

/*===============================TSC===================================*/
unsigned int cycle_measure_overhead=50;
/*****************************************************************************
 Prototype    : calc_cycle_measure_overhead
 Description  : calclucate the cycles measurement overhead
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void calc_cycle_measure_overhead()
{
	unsigned int cycle_cold, cycle_warm;
	cycle_cold= TSCL;
	cycle_cold = TSC_getDelay(cycle_cold);
	cycle_warm= TSCL;
	cycle_warm = TSC_getDelay(cycle_warm);
	cycle_measure_overhead = (cycle_cold + cycle_warm)/2;
}

/*****************************************************************************
 Prototype    : TSC_init
 Description  : Initialize Time stamp counter to measure cycles
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void TSC_init()
{
	TSCL = 0; 	/* Enable the TSC */
	calc_cycle_measure_overhead();
}

/*****************************************************************************
 Prototype    : TSC_delay_ms
 Description  : Implement the delay function in millisecond
 Input        : Uint32 ms  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void TSC_delay_ms(Uint32 ms)
{
	volatile unsigned long long startTSC, currentTSC;
	unsigned long long delay_cycles;
	Uint32 tscl, tsch;

	tscl= TSCL;
	tsch= TSCH;
	startTSC= _itoll(tsch,tscl); 
	
	delay_cycles= ((unsigned long long)ms*gDSP_Core_Speed_Hz/1000);

	do
	{
		tscl= TSCL;
		tsch= TSCH;
		currentTSC= _itoll(tsch,tscl); 
	}
	while((currentTSC-startTSC)<delay_cycles);
}

/*****************************************************************************
 Prototype    : TSC_delay_us
 Description  : Implement the delay function in microsecond
 Input        : Uint32 us  
 Output       : None
 Return Value : 
*****************************************************************************/
void TSC_delay_us(Uint32 us)
{
	volatile unsigned long long startTSC, currentTSC;
	unsigned long long delay_cycles;
	Uint32 tscl, tsch;

	tscl= TSCL;
	tsch= TSCH;
	startTSC= _itoll(tsch,tscl); 
	
	delay_cycles= ((unsigned long long)us*gDSP_Core_Speed_Hz/1000000);

	do
	{
		tscl= TSCL;
		tsch= TSCH;
		currentTSC= _itoll(tsch,tscl); 
	}
	while((currentTSC-startTSC)<delay_cycles);
}

/*===============================Timer=================================*/
/*****************************************************************************
 Prototype    : Reset_Timer
 Description  : Reset the general timer value
 Input        : int timer_num  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void Reset_Timer(int timer_num)
{
	if(gpTimerRegs[timer_num]->TGCR)
	{
		gpTimerRegs[timer_num]->TGCR= 0;
		gpTimerRegs[timer_num]->TCR= 0;
	}
}


/*****************************************************************************
 Prototype    : Service_Watchdog
 Description  : Implement the watch dog service
 Input        : int timer_num  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void Service_Watchdog(int timer_num)
{
    /*write sequence of a A5C6h followed by a DA7Eh 
    to services the watchdog timer.*/
    
	gpTimerRegs[timer_num]->WDTCR =
		(CSL_TMR_WDTCR_WDKEY_CMD1<<CSL_TMR_WDTCR_WDKEY_SHIFT);
	gpTimerRegs[timer_num]->WDTCR =
		(CSL_TMR_WDTCR_WDKEY_CMD2<<CSL_TMR_WDTCR_WDKEY_SHIFT);
}

/*===============================PSC===================================*/
/*****************************************************************************
 Prototype    : KeyStone_enable_PSC_module
 Description  : Enable the PSC module in KeyStone device
 Input        : Uint32 pwrDmnNum  
                Uint32 moduleNum  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
Int32 KeyStone_enable_PSC_module (Uint32 pwrDmnNum, Uint32 moduleNum)
{
	Uint32 uiStartTSC= TSCL;

    if (CSL_PSC_getPowerDomainState(pwrDmnNum) != PSC_PDSTATE_ON)
    {
	    /* Set Power domain to ON */
	    CSL_PSC_enablePowerDomain (pwrDmnNum);

	    /* Start the state transition */
	    CSL_PSC_startStateTransition (pwrDmnNum);

	    /* Wait until the state transition process is completed. */
	    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
		{
			if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
			{
				printf("Enable power domain %d timeout!\n", pwrDmnNum);
				return -2;
			}
		}
	}

    /* Enable the clocks too*/
    CSL_PSC_setModuleNextState (moduleNum, PSC_MODSTATE_ENABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (pwrDmnNum);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
	{
		if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
		{
			printf("Enable clock domain %d timeout!\n", moduleNum);
			return -2;
		}
	}

    /* Return PSC status */
    if ((CSL_PSC_getPowerDomainState(pwrDmnNum) == PSC_PDSTATE_ON) &&
        (CSL_PSC_getModuleState (moduleNum) == PSC_MODSTATE_ENABLE))
    {
        /*Ready for use */
        return 0;
    }
    else
    {
        /*Return error */
        return -1;
    }
}
/*****************************************************************************
 Prototype    : KeyStone_disable_PSC_module
 Description  : Disable the PSC module in KeyStone device
 Input        : Uint32 pwrDmnNum  
                Uint32 moduleNum  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/2/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
Int32 KeyStone_disable_PSC_module (Uint32 pwrDmnNum, Uint32 moduleNum)
{
	Uint32 uiStartTSC= TSCL;
	
    /* disable the clocks*/
    CSL_PSC_setModuleNextState (moduleNum, PSC_MODSTATE_SWRSTDISABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (pwrDmnNum);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
	{
		if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
		{
			printf("Disable clock domain %d timeout!\n", moduleNum);
			return -2;
		}
	}

    /* Return PSC status */
    if (CSL_PSC_getModuleState (moduleNum) == PSC_MODSTATE_SWRSTDISABLE)
    {
        /*Ready for use */
        return 0;
    }
    else
    {
        /*Return error */
        return -1;
    }

}
/*****************************************************************************
 Prototype    : KeyStone_disable_PSC_Power_Domain
 Description  : Disable the PSC power domain
 Input        : Uint32 pwrDmnNum  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
Int32 KeyStone_disable_PSC_Power_Domain (Uint32 pwrDmnNum)
{
	Uint32 uiStartTSC= TSCL;

    /* Set Power domain to OFF */
    CSL_PSC_disablePowerDomain (pwrDmnNum);

    /* Start the state transition */
    CSL_PSC_startStateTransition (pwrDmnNum);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
	{
		if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
		{
			printf("Disable power domain %d timeout!\n", pwrDmnNum);
			return -2;
		}
	}

    /* Return PSC status */
    if (CSL_PSC_getPowerDomainState(pwrDmnNum) == PSC_PDSTATE_OFF)
    {
        /*Ready for use */
        return 0;
    }
    else
    {
        /*Return error */
        return -1;
    }

}

/*======================memory protection==============================*/
/*code and data related to CorePac MPAX configuration should be allocated in LL2*/
#pragma DATA_SECTION(mem_prot_key,".far:Core_MPAX")
unsigned int mem_prot_key[4] = {0xBFBFBFBF, 0xFE29, 3, 4};
/*****************************************************************************
 Prototype    : lock_mem_prot_regs
 Description  : lock memory protection registers
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma CODE_SECTION (lock_mem_prot_regs, ".text:Core_MPAX")
void lock_mem_prot_regs()
{
	int i;

	/*1. Write a 1 to the KEYR field of the MPLKCMD register. This resets some internal
	status for the MPLK0 through MPLK3 registers.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_KEYR_SHIFT);

	/*2. Write the key to MPLK0 through MPLK3. All four registers must be written
	exactly once. They may be written in any order.*/
	for(i=0; i<4; i++)
	{
		gpCGEM_regs->MPLK[i] = mem_prot_key[i];
	}

	/*3. Write a 1 to the LOCK field of the MPLKCMD register. This engages the lock.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_LOCK_SHIFT);

	/*wait to make sure it is locked*/
	while(0==(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK));
}

/*****************************************************************************
 Prototype    : unlock_mem_prot_regs
 Description  : unlock memory protection registers
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma CODE_SECTION (unlock_mem_prot_regs, ".text:Core_MPAX")
void unlock_mem_prot_regs()
{
	int i;

	/*1. Write a 1 to the KEYR field in the MPLKCMD register. This resets some internal
	status for the MPLK0 through the MPLK3 registers.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_KEYR_SHIFT);

	/*2. Write the unlock key to MPLK0 through the MPLK3 registers. The hardware
	compares the written value with the stored key value. Software must write to all
	four registers exactly once. The writes can arrive in any order.*/
	for(i=0; i<4; i++)
	{
		gpCGEM_regs->MPLK[i] = mem_prot_key[i];
	}

	/*3. Write a 1 to the UNLOCK field in the MPLKCMD register. If the key written in
	step 2 matches the stored key, the hardware disengages the lock. If the key written
	in step 2 does not match, the hardware signals an exception. The hardware
	reports the fault address as the address of the MPLKCMD register.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_UNLOCK_SHIFT);

	/*wait to make sure it is unlocked*/
	while(1==(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK));
}

/*****************************************************************************
 Prototype    : L1_MPPA_setup
 Description  : setup the memory protection for local L1 memory
 Input        : volatile Uint32 MPPA_regs[], Uint32 MPPA[]
 Output       : None
 Return Value :

usage example:
 Uint32 MPPA[16]=
 {
	MP_LOCAL|MP_SR|MP_UR, 			//page 0 for read only
	MP_LOCAL|MP_SR|MP_SW|MP_UR|MP_UW, 	//page 1 for read/write
	......
 }
 ......
	L1_MPPA_setup(gpCGEM_regs->L1PMPPA, MPPA);

  History        :
  1.Date         : 2012/12/6
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void L1_MPPA_setup(volatile Uint32 MPPA_regs[], Uint32 MPPA[])
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*clear any memory protection fault*/
	gpCGEM_regs->L1PMPFCR = 1;
	gpCGEM_regs->L1DMPFCR = 1;

	/*setup the memory protection attributes for 32 pages*/
	for(i=0; i<16; i++)
	{
		MPPA_regs[i] = MPPA[i];
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : L1P_memory_protection_cfg
 Description  : config "AccessPermisionMask" for L1P
 Input        : Uint32 AccessPermisionMask
 Output       : None
 Return Value :
*****************************************************************************/
void L1P_memory_protection_cfg(Uint32 AccessPermisionMask)
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*clear any memory protection fault*/
	gpCGEM_regs->L1PMPFCR = 1;

	/*set L1P only for cacheable local execution, disable all external access*/
	for(i=0; i<16; i++)
	{
		gpCGEM_regs->L1PMPPA[i] = AccessPermisionMask;
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : L1D_memory_protection_cfg
 Description  : config "AccessPermisionMask" for L1P
 Input        : Uint32 AccessPermisionMask
 Output       : None
 Return Value :
*****************************************************************************/
void L1D_memory_protection_cfg(Uint32 AccessPermisionMask)
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*clear any memory protection fault*/
	gpCGEM_regs->L1DMPFCR = 1;

	/*set L1P only for cacheable local execution, disable all external access*/
	for(i=0; i<16; i++)
	{
		gpCGEM_regs->L1DMPPA[i] = AccessPermisionMask;
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : L1_cache_protection
 Description  : protect L1 as cache
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void L1_cache_protection()
{
	/*set L1P only for cacheable local execution, disable all external access*/
	L1P_memory_protection_cfg(0);

	/*set L1D only for cacheable local read/write, disable all external access*/
	L1D_memory_protection_cfg(0);
}


/*****************************************************************************
 Prototype    : LL2_MPPA_setup
 Description  : setup the memory protection for local L2 memory
 Input        : Uint32 MPPA[]
 Output       : None
 Return Value :
usage example:
 Uint32 MPPA[32]=
 {
	MP_LOCAL|MP_SX|MP_UX, 			//page 0 for local code only
	MP_LOCAL|MP_SR|MP_SW|MP_UR|MP_UW, 	//page 1 for local data only
	......
 }
 ......
	LL2_MPPA_setup(MPPA);

  History        :
  1.Date         : 2012/10/5
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_MPPA_setup(Uint32 MPPA[])
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*clear any memory protection fault*/
	gpCGEM_regs->L2MPFCR = 1;

	/*setup the memory protection attributes for 32 pages*/
	for(i=0; i<32; i++)
	{
		gpCGEM_regs->L2MPPA[i] = MPPA[i];
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : LL2_Memory_Protection_cfg
 Description  : config "AccessPermisionMask" for local L2 memory section from
				"startAddress" with "byteCount" size
 Input        : Uint32 startAddress
                Uint32 byteCount
                Uint32 AccessPermisionMask
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/5
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_Memory_Protection_cfg(Uint32 startAddress,
	Uint32 byteCount, Uint32 AccessPermisionMask)
{
	int i;
	Uint32 uiEndAddress;
	Uint32 uiPageIndex, uiNumPages, uiPageSize, uiPageAddressMask, uiPageShift;
	//TDSP_Board_Type DSP_Board_Type;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	//DSP_Board_Type = KeyStone_Get_dsp_board_type();

	/*L2 memory protection size is 32KB for TCI6614, C6670,
	it is 16KB for C6678*/
	uiPageSize= 32*1024;
	uiPageAddressMask= 32*1024-1;
	uiPageShift= 15;
	//if(C6678_EVM == DSP_Board_Type)
	{
		uiPageSize= 16*1024;
		uiPageAddressMask= 16*1024-1;
		uiPageShift= 14;
	}

	if(startAddress>=0x10800000)
	{
		printf("LL2 memory protection start Address 0x%x is not a local address\n",
			startAddress);
		startAddress &= 0xFFFFFF;	 /*convert to local address*/
	}
	uiEndAddress= startAddress+ byteCount;

	if(startAddress&uiPageAddressMask)
	{
		printf("LL2 memory protection start Address 0x%x does not align to page boundary\n",
			startAddress);
		startAddress &= (~uiPageAddressMask);
	}
	uiPageIndex= (startAddress-0x800000)>>uiPageShift;

	byteCount= uiEndAddress- startAddress;
	if(byteCount&uiPageAddressMask)
	{
		printf("LL2 memory protection section size 0x%x is not multiple of page size\n",
			byteCount);
		byteCount = (byteCount+uiPageSize)&(~uiPageAddressMask);
	}
	uiNumPages= byteCount>>uiPageShift;

	for(i= 0; i<uiNumPages; i++)
		gpCGEM_regs->L2MPPA[uiPageIndex+i] = AccessPermisionMask;

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : KeyStone_CorePac_AID_map
 Description  : map CorePac AID to PrivID:
        map_table[0] assign the PrivID for AID0,
        map_table[1] assign the PrivID for AID1
        ......
        map_table[5] assign the PrivID for AID5
 Input        : Uint8 map_table[]
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/5
    Author       : Zhan
    Modification : Created function

*****************************************************************************/
void KeyStone_CorePac_AID_map(Uint8 map_table[])
{
	int i;
	Uint32 *PAMAP= (Uint32 *)&(gpCGEM_regs->PAMAP0);

	/*map all PrivID to AIDx by default*/
	for(i=0; i<16; i++)
		PAMAP[i]= CSL_CGEM_PAMAP0_AID_MASK;

	/*map AID0~AID5*/
	for(i=0; i<6; i++)
	{
		if(map_table[i]<16) /*PrivID must be less than 16*/
			PAMAP[map_table[i]]= i;
	}
}


/*****************************************************************************
 Prototype    : KeyStone_MPAX_seg_setup
 Description  : configure one MPAX segment
 Input        : MPAX_Regs * MPAX_regs
                Uint32 BADDR
                Uint32 RADDR
                Uint32 SegementSize
                Uint32 AccessPermisionMask
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/

/*****************************************************************************
 Prototype    : KeyStone_XMC_MPAX_setup
 Description  : configure multiple MPAX segments in XMC with a configuration
                table.
	Please note, the code of this function or the data used by this function
	(stack, parameters...) can not be put in the segment that will be modified
	by this function. Normally, to put this function and its related data in
	LL2 is a good idea.
 Input        : MPAX_Config MPAX_cfg[]
                Uint32 firstSeg
                Uint32 numSegs
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma CODE_SECTION (KeyStone_XMC_MPAX_setup, ".text:Core_MPAX")
void KeyStone_XMC_MPAX_setup(MPAX_Config MPAX_cfg[],
	Uint32 firstSeg, Uint32 numSegs)
{
	int i;

    if(firstSeg >= 16)
    {
        printf("The XMC MPAX segment number %d >= 16, not supported.\n ", firstSeg);
        return;
    }

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*CAUTION:
	A MPAX segment can only be modified when there is no access to the space
	of this segment. Any data in cache or prefetch buffer from the space of this
	segment must be writeback and invalidated before the segment modification.
	It is recommended to configure the MPAX at the very beginning of application
	software before any shared memory is used. Code and data for CorePac MPAX
	configuration should be allocated in LL2.
	If a MPAX segment must be modified on-the-fly, the safer way is, to write
	the new configuration to a unused higher segment, and then clear the old
	segment. This is based on the fact that higher numbered segments take
	precedence over lower numbered segments.	*/
	CACHE_wbInvAllL2(CACHE_WAIT);
	CSL_XMC_invalidatePrefetchBuffer();
	_mfence();
	_mfence(); 	//ensure all writeback invalidate have completed.
#if 0
	for(i=numSegs-1; i>=0 ; i--)
    {
		KeyStone_MPAX_seg_setup((MPAX_Regs *)&gpXMC_regs->XMPAX[firstSeg+i],
			MPAX_cfg[i].BADDR, MPAX_cfg[i].RADDR,
			MPAX_cfg[i].SegementSize, MPAX_cfg[i].AccessPermisionMask);
    }
#endif
	lock_mem_prot_regs();
}



/*======================memory EDC=====================================*/
/*****************************************************************************
 Prototype    : KeyStone_SL2_EDC_enable
 Description  : Enable MSMC EDC
 Input        : scrubCnt, number of MSMC clock cycles between scrubbing
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SL2_EDC_enable(Uint32 scrubCnt)
{
	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
		CSL_MSMC_unlockNonMPAX();

	/*Software must wait for the PRR (Parity RAM Ready) bit before making
	the first read access to MSMC RAM after reset.*/
	while(0==(gpMSMC_regs->SMEDCC&CSL_MSMC_SMEDCC_PRR_MASK));

	/* set scrubbing period value */
	if(scrubCnt>255)
		scrubCnt= 255;
	CSL_MSMC_setCounterBankRefreshRead(scrubCnt); //the scrubbing engine works every scrubCnt*1024 cycle*/

	/* clear EDC errors and enable EDC event*/
	gpMSMC_regs->SMIRC = 0xf;
	gpMSMC_regs->SMIESTAT |= (CSL_MSMC_SMIESTAT_NCSIE_MASK
			           | CSL_MSMC_SMIESTAT_CSIE_MASK
			           | CSL_MSMC_SMIESTAT_NCEIE_MASK
			           | CSL_MSMC_SMIESTAT_CEIE_MASK);

	//enable SL2 EDC
	CSL_MSMC_setECM(1);

	CSL_MSMC_lockNonMPAX();
}

/*****************************************************************************
 Prototype    : KeyStone_SL2_EDC_interrupt_en
 Description  : Enable MSMC EDC error interrupt
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SL2_EDC_interrupt_en()
{
	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
		CSL_MSMC_unlockNonMPAX();

	/* clear EDC errors*/
	gpMSMC_regs->SMIRC = 0xf;

	/* Enable EDC error interrupt */
	gpMSMC_regs->SMIESTAT |= (CSL_MSMC_SMIESTAT_NCSIE_MASK
			           | CSL_MSMC_SMIESTAT_CSIE_MASK
			           | CSL_MSMC_SMIESTAT_NCEIE_MASK
			           | CSL_MSMC_SMIESTAT_CEIE_MASK);

	CSL_MSMC_lockNonMPAX();
}

/*****************************************************************************
 Prototype    : LL2_EDC_setup
 Description  : Eenable LL2 EDC and scrub whole LL2
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/10
    Author       : Jane
    Modification : Created function

  2.Date         : 2012/10/20
    Author       : Brighton Feng

*****************************************************************************/
void LL2_EDC_setup()
{
	int i;
	unsigned int uiByteCnt= 512*1024;

	/* 1. Disable the EDC */
	CSL_CGEM_disableL2EDC();

	/* 2. Clear any EDC errors */
	CSL_CGEM_clearL2EDCErrorStatus(1, 1, 1, 1);

	/* 3. Memory Scrubbing with IDMA, generate the parity bits*/

	/*Each IDMA can transfer up to 65532 bytes,
	here we transfer 32KB each time*/
	for(i=0; i< (uiByteCnt>>15); i++)
	{
#if 0
		IDMA_copy((0x00800000 + i*(1<<15)), (0x00800000 + i*(1<<15)),
			(1<<15), DMA_WAIT);
#endif
	}

	/* 4. Enable the EDC*/
	CSL_CGEM_enableL2EDC();
	gpCGEM_regs->L2EDCEN= (1<<CSL_CGEM_L2EDCEN_DL2CEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_DL2SEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_PL2CEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_PL2SEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_SDMAEN_SHIFT);

}

Uint32 uiLL2_scrub_addr=0x800000;
/*****************************************************************************
 Prototype    : LL2_EDC_scrub
 Description  : scrub a block in LL2 for EDC.

    Number of bytes must be multiple of 128 bits and less than 64KB.
This function should be called periodically, for example,
if every 1 minute, call it with:	LL2_EDC_scrub(1024);
For 1MB LL2, the whole space will be scrubbed in 1024 minutes(17 hours)

 Input        : Uint32 uiByteCnt
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/20
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_EDC_scrub(Uint32 uiByteCnt)
{
	Uint32	uiLL2EndAddress= 0x00880000;

	uiByteCnt &= 0xFFF0;	//size must be multiple of 128 bits and less than 64KB

#if 1
	int i;
	volatile Uint32 * uipAddress= (volatile Uint32 *)uiLL2_scrub_addr;
	for(i=0; i< uiByteCnt/64; i++)
	{
		/*read one word to fetch a cache line, write to make it dirty*/
		*uipAddress= *uipAddress;
		uipAddress+= 16; 	//skip to the next cach line
	}
	CACHE_wbInvL1d((void *)uiLL2_scrub_addr, uiByteCnt, CACHE_NOWAIT);
#else 	//use IDMA ONLY for read ONLY space
	/*if IDMA scrub memory which is modifying by other masters at the same time,
	there may be race condtion that the new value is overwritter by the IDMA
	with old value.*/
	IDMA_copy(uiLL2_scrub_addr, uiLL2_scrub_addr, uiByteCnt, DMA_NO_WAIT);
#endif

	uiLL2_scrub_addr+= uiByteCnt;

	//wrap back
	if(uiLL2_scrub_addr >= uiLL2EndAddress)
		uiLL2_scrub_addr=0x800000;

}

/*****************************************************************************
 Prototype    : L1P_EDC_setup
 Description  : enable L1P ED and scrub whole L1P
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/10
    Author       : Jane
    Modification : Created function

  2.Date         : 2012/10/30
    Author       : Brighton Feng
*****************************************************************************/
void L1P_EDC_setup()
{
	Uint32 preL1PMPPA[16];

	/* 1. Disable the EDC */
	CSL_CGEM_disablePMCErrorDetection();

	/* 2. Clear any EDC errors */
	CSL_CGEM_clearPMCErrorDetectionStatus(1, 1);

	/* 3. Memory Scrubbing with IDMA, generate the parity bits*/
	memcpy(preL1PMPPA, (void *)gpCGEM_regs->L1PMPPA, 64);//save protection attributes
	L1P_memory_protection_cfg(0xFFFF); //enable IDMA access to L1P
//	IDMA_copy(0x00E00000, 0x00E00000, 32*1024, DMA_WAIT);
	L1_MPPA_setup(gpCGEM_regs->L1PMPPA, preL1PMPPA);//restore protection for L1

	/* 4. Enable the EDC*/
	CSL_CGEM_enablePMCErrorDetection();
}

char * LL2_EDC_victim_err_str="LL2 victims";
char * LL2_EDC_DMA_err_str=	"DMA access";
char * LL2_EDC_L1D_err_str=	"L1D access";
char * LL2_EDC_L1P_err_str=	"L1P access";

/*****************************************************************************
 Prototype    : LL2_EDC_handler
 Description  : LL2 EDC exception/interrupt handler
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_EDC_handler(Bool bCorrected)
{

}
/*****************************************************************************
 Prototype    : L1P_ED_handler
 Description  : L1P EDC processing
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void L1P_ED_handler()
{
	Uint32 errAddr;
	Uint8 errRAM;

	/* EDC error during DMA access */
    Uint8  dmaerr;
    /* EDC error during program fetch access */
    Uint8  perr;

	/* Read PMC EDC status*/
	CSL_CGEM_getPMCErrorDetectionStatus(&dmaerr, &perr);

	if(perr|dmaerr)
	{
		CSL_CGEM_getPMCErrorInfo(&errAddr, &errRAM);

		exception_record.status.ext_sts.info.memory.fault_address= errAddr*32;
		exception_record.status.ext_sts.info.memory.fault_status.L1PEDSTAT=
			gpCGEM_regs->L1PEDSTAT;

		if(errRAM)
			printf("  L1P RAM ");
		else
			printf("  L1P Cache ");

		printf("parity check error caused by ");

		if(perr == 1)
		{
			printf("program fetch ");

			/*flush wrong code in L1P. Code will be refetched from L2*/
			CACHE_invL1p((void *)NRP, 64, CACHE_WAIT);
		}
		else if(dmaerr == 1)
		{
			printf("DMA ");
		}
		printf("at address 0x%x\n", errAddr*32);

		CSL_CGEM_clearPMCErrorDetectionStatus(dmaerr,perr);
	}
}


/*****************************************************************************
 Prototype    : KeyStone_SL2_EDC_handler
 Description  : SL2 EDC Processing
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SL2_EDC_handler()
{
	/* EDC correctable error during scrubbing cycle */
    Uint8  cses;
	/* EDC non-correctable error during scrubbing cycle */
    Uint8  ncses;
    /* EDC correctable error during SRAM access*/
    Uint8  cees;
    /* EDC non-correctable error during SRAM access*/
    Uint8  ncees;
    /* protection fault status*/
    Uint16  pfeStat;

    /*  error address  */
    Uint32 errAddr, bitPos, PrivID;

	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
		CSL_MSMC_unlockNonMPAX();

    CSL_MSMC_getPendingInterrupts(&pfeStat, &cees, &ncees, &cses, &ncses);

	exception_record.status.ext_sts.info.memory.fault_status.SMESTAT=
		gpMSMC_regs->SMESTAT;

	if((cses == 1)||(ncses == 1))
	{
		if(cses == 1)
		{
			/*scrubbing engine report address offset from 0*/
			errAddr = (gpMSMC_regs->SMCEA&0xFFFFFF)+0xc000000;
			exception_record.status.ext_sts.info.memory.fault_address= errAddr;

			bitPos = (gpMSMC_regs->SMCEA&CSL_MSMC_SMCEA_ESYN_MASK)
				>>CSL_MSMC_SMCEA_ESYN_SHIFT;
			printf("SL2 Correctable error occurred at bit %d of address 0x%x by scrubbing\n",
				bitPos, errAddr);
		}
		 if(ncses == 1)
		{
			/*scrubbing engine report address offset from 0*/
			errAddr = gpMSMC_regs->SMNCEA+0xc000000;
			exception_record.status.ext_sts.info.memory.fault_address= errAddr;

			printf("SL2 Non-correctable error occurred at address 0x%x by scrubbing\n", errAddr);
		}
		printf("%d correctable errors, %d non-correctable errors occurred during scrubbing.\n",
			(gpMSMC_regs->SMSECC&CSL_MSMC_SMSECC_SCEC_MASK)
				>>CSL_MSMC_SMSECC_SCEC_SHIFT,
			(gpMSMC_regs->SMSECC&CSL_MSMC_SMSECC_SNCEC_MASK)
				>>CSL_MSMC_SMSECC_SNCEC_SHIFT);
	}
	if(cees == 1)
	{
		volatile Uint32 scrubValue;

		errAddr =  gpMSMC_regs->SMCERRAR;
		exception_record.status.ext_sts.info.memory.fault_address= errAddr;

		//scrub the address to correct the error
		scrubValue= *(volatile Uint32 *)errAddr; //touch to cach
		*(volatile Uint32 *)errAddr= scrubValue; //make cache dirty
		CACHE_wbInvL2((void *)errAddr, 32, CACHE_WAIT);

		bitPos = (gpMSMC_regs->SMCERRXR&CSL_MSMC_SMCERRXR_ESYN_MASK)
			>>CSL_MSMC_SMCERRXR_ESYN_SHIFT;
		PrivID = (gpMSMC_regs->SMCERRXR&CSL_MSMC_SMCERRXR_SEPID_MASK)
			>>CSL_MSMC_SMCERRXR_SEPID_SHIFT;
		printf("SL2 Correctable error occurred at bit %d of address 0x%x by PrivID %d ",
			bitPos, errAddr, PrivID);
		if(gpMSMC_regs->SMCERRXR&CSL_MSMC_SMCERRXR_SER_MASK)
			printf("(not from C66x CorePacs)\n");
		else
			printf("(from C66x CorePacs)\n");
	}
	if(ncees ==1)
	{
		errAddr =  gpMSMC_regs->SMNCERRAR;
		exception_record.status.ext_sts.info.memory.fault_address= errAddr;

		PrivID = (gpMSMC_regs->SMNCERRXR&CSL_MSMC_SMNCERRXR_SEPID_MASK)
			>>CSL_MSMC_SMNCERRXR_SEPID_SHIFT;
		printf("SL2 Non-correctable error occurred at address 0x%x by PrivID %d ",
			errAddr, PrivID);
		if(gpMSMC_regs->SMNCERRXR&CSL_MSMC_SMNCERRXR_SER_MASK)
			printf("(not from C66x CorePacs)\n");
		else
			printf("(from C66x CorePacs)\n");
	}

	/* clear EDC error status  */
	CSL_MSMC_clearRawInterruptStatus(0, cees,ncees, cses, ncses);

	CSL_MSMC_lockNonMPAX();
}

/*===============================Exception=============================*/
//data structure to save exception info
Exception_Record exception_record;

/*some exception events routed from CIC to INTC and then to exception moduel,
all these events are routed to one input of INTC*/
Uint32 guwIntcCICExcEvtIdx= 95; /*INTC event number mapping to CIC exception events*/
Uint32 gCIC_EXC_out_num = 15; 	//CIC output event number
Uint32 gCIC_EXC_EN_MASK[8]= {0,0,0,0,0,0,0,0};
/*****************************************************************************
 Prototype    : KeyStone_CIC_exception_events_mapping
 Description  : CIC exception event mapping to the NMI external exception
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/5
    Author       : Brighton Feng
    Modification : Created function

  2.Date         : 2012/10/20
    Author       : Zhan
    Modification : Add event for TCI6614

  3.Date         : 2012/10/28
    Author       : Brighton Feng
*****************************************************************************/
void KeyStone_CIC_exception_events_mapping(void)
{


}
/*****************************************************************************
 Prototype    : KeyStone_Exception_cfg
 Description  : Config the system  err and external exception to generate the NMI.
                Call this function as last step after all 
                configuration/initialization complete
 Input        : Bool bGlobalExceptionMaster. If TRUE, the global exception events 
                from CIC will be routed to exception model of this CPU core.
 Output       : None
 Return Value : 
*****************************************************************************/
void KeyStone_Exception_cfg(Bool bGlobalExceptionMaster)
{

	puts("Enable Exception handling...");

	TSCL = 0; 	/* Enable the TSC */

	memset(&exception_record, 0, sizeof(exception_record));
#if 0
	 /*Clear all CPU events*/
	gpCGEM_regs->EVTCLR[0]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[1]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[2]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[3]= 	0xFFFFFFFF;
#endif
	/*clear memory fault*/
	gpCGEM_regs->L1PMPFCR = 1;
	gpCGEM_regs->L1DMPFCR = 1;
	gpCGEM_regs->L2MPFCR = 1;
	gpXMC_regs->XMPFCR = 1;

	/*clear configuration bus error*/
	gpCGEM_regs->ICFGMPFCR= 1;
	gpCGEM_regs->ECFGERRCLR= 1;

	/* clear the MDMAERR */
	gpCGEM_regs->MDMAERRCLR = 1;

	/*clear interrupt drop staus*/
	gpCGEM_regs->INTXCLR = 1;

	gpCGEM_regs->INTDMASK= ~IER; /*only monitor drop of enabled interrupts*/

	/*enable events:
	10 MSMC_mpf_error_n MSMC Memory protection fault  caused by local CorePac
	96 INTERR Dropped CPU interrupt event
	97 EMC_IDMAERR Invalid IDMA parameters
	110 MDMAERREVT XMC VBUSM error event
	113 PMC_ED Single bit error detected during DMA accesses L1P
	117 UMC_ED2 Uncorrected bit error detected LL2
	119 SYS_CMPA CPU Memory Protection Fault for local configuration of INTC and power control
	120 PMC_CMPA CPU memory protection fault for L1P
	121 PMC_DMPA DMA memory protection fault for L1P
	122 DMC_CMPA CPU memory protection fault for L1D (and other memory read finally goes through the L1D controller)
	123 DMC_DMPA DMA memory protection fault for L1D
	124 UMC_CMPA CPU memory protection fault for LL2
	125 UMC_DMPA DMA memory protection fault for LL2
	126 EMC_CMPA CPU memory protection fault for other local configuration space between 0x01000000 - 0x01BFFFFF 
	127 EMC_BUSERR Bus Error Interrupt for global configuration space between 0x01C00000 - 0x07FFFFFF 
	*/
	gpCGEM_regs->EXPMASK[0]= ~(1<<CSL_GEM_MSMC_MPF_ERRORN);
	gpCGEM_regs->EXPMASK[1]= 0xFFFFFFFF;
	gpCGEM_regs->EXPMASK[2]= 0xFFFFFFFF;
	gpCGEM_regs->EXPMASK[3]= ~((1<<(CSL_GEM_INTERR - 96))|
		(1<<(CSL_GEM_EMC_IDMAERR-96))|
		(1<<(CSL_GEM_MDMAERREVT-96))|
		(1<<(CSL_GEM_PMC_ED-96))|
		(1<<(CSL_GEM_UMC_ED2-96))|
		(1<<(CSL_GEM_SYS_CMPA-96))|
		(1<<(CSL_GEM_PMC_CMPA-96))|
		(1<<(CSL_GEM_PMC_DMPA-96))|
		(1<<(CSL_GEM_DMC_CMPA-96))|
		(1<<(CSL_GEM_DMC_DMPA-96))|
		(1<<(CSL_GEM_UMC_CMPA-96))|
		(1<<(CSL_GEM_UMC_DMPA-96))|
		(1<<(CSL_GEM_EMC_CMPA-96))|
		(1<<(CSL_GEM_EMC_BUSERR-96)));


	if(bGlobalExceptionMaster)
	{
		/*enable exception events routed from CIC,
		please note, this should be only configured for one CPU*/
		KeyStone_CIC_exception_events_mapping();
		gpCGEM_regs->EXPMASK[guwIntcCICExcEvtIdx>>5] &= (~(1<<(guwIntcCICExcEvtIdx&0x1F)));        
	}

	/*clear exception flag*/
	ECR = EFR;
	IERR = 0; 
    
	/*Eanble external exception, global exception enable*/
	TSR = TSR|
		(1<<CSL_CHIP_TSR_XEN_SHIFT)|
		(1<<CSL_CHIP_TSR_GEE_SHIFT)|
		(1<<CSL_CHIP_TSR_GIE_SHIFT);

	/*enable NMI exception*/
	IER = IER|(1<<CSL_CHIP_IER_NMI_SHIFT);
	
}

char * bus_err_stat_str[]=
{
	"unrecognized RID/WID (should cause error to be latched)",
	"Addressing error",
	"Privilege error",
	"Timeout error",
	"Data error",
	"Reserved error",
	"Reserved error",
	"Exclusive - operation failure"
};
/*****************************************************************************
 Prototype    : Bus_error_handler
 Description  : System bus error processing
 Input        : unsigned int ERR_REG  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/25
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void Bus_error_handler(unsigned int ERR_REG)
{
	unsigned int err, stat;

	if(0 == ERR_REG)
		return;

	exception_record.status.ext_sts.info.memory.BUS_ERROR= ERR_REG;

	err= (ERR_REG & CSL_CGEM_MDMAERR_ERR_MASK)>>CSL_CGEM_MDMAERR_ERR_SHIFT;
	if (1==err) {
		puts("  MDMA read status error detected");
	}
	else if (2==err) {
		puts("  MDMA write status error detected");
	}
	else if (3==err) {
		puts("  CFG read status error detected");
	}
	else if (4==err) {
		puts("  CFG write status error detected");
	}

	printf("  XID (Transaction ID)= %d\n", 
		(ERR_REG & CSL_CGEM_MDMAERR_XID_MASK)>>CSL_CGEM_MDMAERR_XID_SHIFT);	

	stat= (ERR_REG & CSL_CGEM_MDMAERR_STAT_MASK)>>CSL_CGEM_MDMAERR_STAT_SHIFT;
	printf("  %s\n", bus_err_stat_str[stat]);
}

/*****************************************************************************
 Prototype    : KeyStone_CIC_EXC_handler
 Description  : This function handle the exception events from CIC
 Input        : void
 Output       : None
 Return Value : void
 
  History        :
  1.Date         : 2012/10/18
    Author       : Zhan
    Modification : Created function

  2.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Add EDMA error processing

*****************************************************************************/
void KeyStone_CIC_EXC_handler()
{

}

/*****************************************************************************
 Prototype    : KeyStone_EXC_external
 Description  : external exception processing
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_EXC_external(void)
{

}

char * internal_exception_str[]=
{
	"Instruction fetch exception",
	"Fetch packet exception",
	"Execute packet exception",
	"Opcode exception",
	"Resource conflict exception",
	"Resource access exception",
	"Privilege exception",
	"SPLOOP buffer exception",
	"Missed stall exception"
};

/*****************************************************************************
 Prototype    : EXC_internal
 Description  : internal exception handler
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
/*internal exception handler*/
void EXC_internal(void)
{
	int i;
	unsigned int ierr;

	/*record IERR */    
	ierr = IERR;
	exception_record.status.IERR= ierr;

	if(ierr)
	{
		/*Clear internal excpeiton flag*/
		IERR= 0;

		printf("internal excpetion happened. IERR=0x%x.\n", ierr);
		for(i=0; i<9; i++)
		{
			if((ierr>>i)&1)
				printf("  %s\n", internal_exception_str[i]);
		}
		if (ierr & CSL_CHIP_IERR_IFX_MASK) {
			/* L1P EDC Processing*/
			L1P_ED_handler();
		}
	}
	else
		puts("Enter Internal Exception service routine, but internal excpetion flage is 0!");
	
}
/*****************************************************************************
 Prototype    : EXC_nmi
 Description  : NMI processing
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EXC_NMI(void)
{
	puts("NMI exception happened, normally you should reset the DSP to recover from the problem!");
}

/*****************************************************************************
 Prototype    : EXC_swgen
 Description  : software generated exception handler
 Input        : void  
 Output       : None
 Return Value : 
*****************************************************************************/
void EXC_swgen(void)
{	
	puts("Software generated exception happened.");
}

/*****************************************************************************
 Prototype    : Exception_service_routine
 Description  : Exception service routine
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma NMI_INTERRUPT( Exception_service_routine );
void Exception_service_routine(void)
{
	unsigned int efr, nrp, ntsr, tscl, tsch, irp, itsr;

	/*record timestamp*/
	tscl = TSCL;
	exception_record.TSCL= tscl;
	tsch = TSCH;
	exception_record.TSCH= tsch;
	
	nrp = NRP;   /*record NRP */
	exception_record.NRP= nrp;
	ntsr = NTSR; /*record NTSR */
	exception_record.NTSR= ntsr;
	efr = EFR;   /*record EFR */
	exception_record.EFR= efr;

	irp = IRP;   /*record IRP */
	itsr = ITSR; /*record ITSR */
	exception_record.IRP= irp;
	exception_record.ITSR= itsr;

	if(efr)
	{
		/*Clear excpeiton flag*/
		ECR = efr;

		/*check all possible exceptions*/
		if (efr & CSL_CHIP_EFR_OXF_MASK) {
			/* S/W generated exception */
			EXC_swgen();		
		}
		if (efr & CSL_CHIP_EFR_IXF_MASK) {
			/* internal exception */
			EXC_internal();		
		}
		if (efr & CSL_CHIP_EFR_EXF_MASK) {
			/* external exception */
			KeyStone_EXC_external();		
		}
		if (efr & CSL_CHIP_EFR_NXF_MASK) {
			/* legacy NMI exception */
			EXC_NMI();		
		}
	}
	else
		puts("Enter Exception service routine, but excpetion flage is 0!");
		
	printf("NRP=0x%x, NTSR=0x%x, IRP=0x%x, ITSR=0x%x, TSCH= 0x%x, TSCL= 0x%x\n", 
		nrp, ntsr, irp, itsr, tsch, tscl);

	printf(" B3=0x%x, A4=0x%x, B4= 0x%x, B14= 0x%x, B15= 0x%x\n", 
		exception_record.B3, exception_record.A4,
		exception_record.B4, exception_record.B14,
		exception_record.B15);

	/*
	It is not always possible to safely exit the exception handling routine. Conditions that
	can prevent a safe return from exceptions include:
	1. SPLOOPs that are terminated by an exception cannot be resumed correctly. The
	SPLX bit in NTSR should be verified to be 0 before returning.
	2. Exceptions that occur when interrupts are blocked cannot be resumed correctly.
	The IB bit in NTSR should be verified to be 0 before returning.
	3. Exceptions that occur at any point in the code that cannot be interrupted safely
	(for example, a tight loop containing multiple assignments) cannot be safely
	returned to. The compiler will normally disable interrupts at these points in the
	program; check the GIE bit in NTSR to be 1 to verify that this condition is met.
	4. NRP is not in valid address space*/
	if((ntsr&CSL_CHIP_TSR_SPLX_MASK)
		||(ntsr&CSL_CHIP_TSR_IB_MASK)
		||(0==(ntsr&CSL_CHIP_TSR_GIE_MASK))
		||(0x800000>NRP))
	{
		puts("Exception happened at a place can not safely return!");
		//while(1);		//trap
		exit(0);
	}

}

/*****************************************************************************
 Prototype    : Nested_Exception_service_routine
 Description  : Nested Exception service routine
  	When a non-maskable exception happens in the first exception service routine,
  	then the reset vector is used when redirecting program execution to service the second
	exception. In this case, NTSR and NRP are left unchanged. TSR is copied to ITSR and
	the current PC is copied to IRP. TSR is set to the default exception processing value and
	the NMIE bit in IER is cleared in this case preventing any further external exceptions.
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/29
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
interrupt void Nested_Exception_service_routine(void)
{
	unsigned int tscl, tsch;

	/*record timestamp*/
	tscl = TSCL;
	tsch = TSCH;

	if(0==exception_record.TSCL)
		exception_record.TSCL= tscl;
	if(0==exception_record.TSCH)
		exception_record.TSCH= tsch;
	if(0==exception_record.NRP)
		exception_record.NRP= NRP;
	if(0==exception_record.NTSR)
		exception_record.NTSR= NTSR;
	if(0==exception_record.EFR)
		exception_record.EFR= EFR;
	if(0==exception_record.status.IERR)
		exception_record.status.IERR= IERR;

	exception_record.IRP= IRP;
	exception_record.ITSR= ITSR;

	printf("Nested exception happened! IRP=0x%x, ITSR=0x%x\n",
		IRP, ITSR);
		
	printf("NRP=0x%x, NTSR=0x%x, EFR=0x%x, IERR=0x%x, TSCH= 0x%x, TSCL= 0x%x\n", 
		NRP, NTSR, EFR, IERR, tsch, tscl);

	while(1);		//trap
}

/*=========================other utility functions==========================*/
/*clear all interrupt flag/status, setup ISTP to begining of LL2*/
void CPU_interrupt_init()
{
	//clear interrupt and excpetion events
	ICR = IFR;
	ECR = EFR;
	IER= 3; 	//disable all interrupts
    
	/* disable event combine */
	gpCGEM_regs->EVTMASK[0] = 0xffffffff;
	gpCGEM_regs->EVTMASK[1] = 0xffffffff;
	gpCGEM_regs->EVTMASK[2] = 0xffffffff;
	gpCGEM_regs->EVTMASK[3] = 0xffffffff;

	 /*Clear all CPU events*/
	gpCGEM_regs->EVTCLR[0]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[1]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[2]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[3]= 	0xFFFFFFFF;

	/*Interrupt Service Table Pointer to begining of LL2 memory*/
	ISTP= 0x800000;
}

/*enable interrupt to CPU: IER |= uiIER_en_mask; GIE=1*/
void CPU_interrupt_enable(Uint32 uiIER_en_mask)
{
	ICR= uiIER_en_mask;
	IER |= uiIER_en_mask;

	//enable GIE
	TSR = TSR|1;
}

/*****************************************************************************
 Prototype    : KeyStone_get_device_info
 Description  : Get device information
 Input        : None
 Output       : None
 Return Value :

  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function
  2.Date         : 2014/12/2
    Author       : Brighton Feng
    Modification : Update to parser device type, boot mode, endian information,
                   speed grade, required CVDD

*****************************************************************************/

char * device_type_str[]=
{
	"TCI6616",
	"C6670/TCI6618",
	"C6678/TCI6608",
	"TCI6614",
	"unknown"
};
char * endian_str[]=
{
	"big",
	"little"
};
char * boot_mode_str[]=
{
	"No boot or EMIF16(NOR FLASH) or UART",
	"Serial Rapid I/O",
	"Ethernet (SGMII)",
	"Ethernet (SGMII) or NAND FLASH",
	"PCIE",
	"I2C",
	"SPI",
	"HyperLink"
 };
char * input_clk_str[]=
{
	"50MHz",
	"66.67MHz",
	"80MHz",
	"100MHz",
	"156.25MHz",
	"250MHz",
	"312.5MHz",
	"122.88MHz",
	"bypassed"
};

/*****************************************************************************
 Prototype    : KeyStone_common_device_init
 Description  : common initialization for internal modules in K2 device
 enable memory protection interrupts, EDC for MSMC RAM
  History        :
  1.Date         : July 11, 2014
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_common_device_init()
{
	int i;

	/* enable common MPU interrupts */
	for(i=0; i<4; i++)
	{
//		KeyStone_MPU_interrupt_enable(i);
	}

	/*Enable MSMC EDC and setup scrubbing cycle counter= 255*1024*/
	KeyStone_SL2_EDC_enable(255);
}

/*****************************************************************************
 Prototype    : KeyStone_common_CPU_init
 Description  : common initialization for internal modules in K2 device
 enable TSC, EDC for local RAM; clear cache; protect L1 as cache
  History        :
  1.Date         : September 1, 2014
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_common_CPU_init()
{
    TSC_init();	//initialize TSC to measure cycle

	/*clear all interrupt flag/status, setup ISTP to begining of LL2*/
	CPU_interrupt_init();

	/*clean cache from previous run, not required from power on or cold reset*/
	CACHE_wbInvAllL2(CACHE_WAIT);
	CSL_XMC_invalidatePrefetchBuffer();
	_mfence();
	_mfence();

	/* protect L1 as cache */
   	L1_cache_protection();

	//Enable MSMC Memory protection error interrupt for local core, refer to MSMC user guide section3.8
//	KeyStone_MSMC_MP_interrupt_en(1<<DNUM);

	/*enable L1P ED and scrub whole L1P*/
	L1P_EDC_setup();

   	/*enable LL2 EDC and scrub whole LL2*/
	LL2_EDC_setup();

}

/* chengqb   2016.3.25 增加上层调用接口*/

 void CInvalidCache(void * blockPtr, Uint32 byteCnt)
 {
	InvalidCache( blockPtr,  byteCnt);
 }

 void CWritebackCache(void * blockPtr, Uint32 byteCnt)
{
	WritebackCache( blockPtr, byteCnt);
  }

