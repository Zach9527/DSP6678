/*

 文件名称：psc_dsp6678.c
摘要：主要实现dsp66786的psc初始化控制
*/
/* 修改历史:
2016.3.13 chengqb创建文件
*/


/* includes */ 
#include "datatype.h"
#include "delay.h"
#include "dsp667x.h"

/* defines */ 
#define DSP_PDCCMD_REG		(*(VOLATILE UINT32*)0x01810000)

/* typedefs */  

/* globals */ 

/* locals */

/* local function declarations */
 
/*global function define*/ 
void corePacPowerPown(void)
{
	DSP_PDCCMD_REG |= (UINT32)1<<16;
}

void corePacPowerUp(void)
{
	DSP_PDCCMD_REG &= ~((UINT32)1<<16);
}

/*控制模块电源开关是否使能*/
INT32 pscPowerDomainUp( UINT32 pscPdIndex)
{
	CSL_PSC_PDSTATE pdstat;

	CSL_PSC_enablePowerDomain (pscPdIndex);/*set PDCTL[X].NEXT for an ON (0x1) transition.*/
	CSL_PSC_startStateTransition (pscPdIndex);/*Set PTCMD.GO[X] to 0x1 to initiate the state transition(s)*/
	while (!CSL_PSC_isStateTransitionDone (pscPdIndex));/*Wait for PTSTAT.GOSTAT[X] to clear to 0x0 */
	//判断状态
	pdstat = CSL_PSC_getPowerDomainState(pscPdIndex);
	if(pdstat != PSC_PDSTATE_ON)
	{
		return 1;
	}

	return 0;
}

/*控制模块时钟开关是否使能*/
INT32 pscClockDomainUp( UINT32 pscCdIndex)
{
	 CSL_PSC_MODSTATE mdstat;

	CSL_PSC_setModuleNextState (pscCdIndex, PSC_MODSTATE_ENABLE);
	CSL_PSC_startStateTransition (pscCdIndex);/*Set PTCMD.GO[X] to 0x1 to initiate the state transition(s)*/
	while (!CSL_PSC_isStateTransitionDone (pscCdIndex));/*Wait for PTSTAT.GOSTAT[X] to clear to 0x0 */
	//判断状态
	 mdstat = CSL_PSC_getModuleState(pscCdIndex);
	if(mdstat != PSC_MODSTATE_ENABLE)
	{
		return 1;
	}
	return 0;
}

void pscLocalReset(void)
{
	
}
/***************************************************************************************
 * FUNCTION PURPOSE: Power up all the power domains
 ***************************************************************************************
 * DESCRIPTION: this function powers up the PA subsystem domains
 ***************************************************************************************/
void PowerUpDomains (void)
{
    /* PASS power domain is turned OFF by default. It needs to be turned on before doing any
     * PASS device register access. This not required for the simulator. */

    /* Set PASS Power domain to ON */
    CSL_PSC_enablePowerDomain (CSL_PSC_PD_ALWAYSON);

    /* Enable the clocks for PASS modules */
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_EMIF4F, PSC_MODSTATE_ENABLE);
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_EMIF25_SPI,  PSC_MODSTATE_ENABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (CSL_PSC_PD_ALWAYSON);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (CSL_PSC_PD_ALWAYSON));


    /* PASS power domain is turned OFF by default. It needs to be turned on before doing any
     * PASS device register access. This not required for the simulator. */

    /* Set PASS Power domain to ON */
    CSL_PSC_enablePowerDomain (CSL_PSC_PD_PASS);

    /* Enable the clocks for PASS modules */
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_PKTPROC, PSC_MODSTATE_ENABLE);
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_CPGMAC,  PSC_MODSTATE_ENABLE);
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_Crypto,  PSC_MODSTATE_ENABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (CSL_PSC_PD_PASS);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (CSL_PSC_PD_PASS));
}

/*local function define*/



