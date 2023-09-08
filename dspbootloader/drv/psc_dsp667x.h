/*

 文件名称：psc_dsp667x.h
摘要：
*/
/* 修改历史:

2016.3.13,chengqb 创建文件
*/

#ifndef __PSC_DSP6678__
#define __PSC_DSP6678__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/

/*defines*/
#define PSC_PD_ALWAYSON  	(0)			/*Most peripheral logic*/
#define PSC_PD_DEBUG_TRC 	(1)			/*Per-core TETB and System TETB*/
#define PSC_PD_PASS 		(2)			/*Packet Coprocessor*/
#define PSC_PD_PCIEX 		(3)			/*PCIe*/
#define PSC_PD_SRIO 		(4)			/*SRIO*/
#define PSC_PD_HYPERBRIDGE 	(5)			/*HyperLink*/
#define PSC_PD_L2SRAM 		(6)			/*Reserved*/
#define PSC_PD_MSMCSRAM		(7)			/*MSMC RAM*/
#define PSC_PD_GEM0 		(8 )       	/*C66x CorePac0, L1/L2 RAMs*/
#define PSC_PD_GEM1 		(9 )       	/*C66x CorePac1, L1/L2 RAMs*/
#define PSC_PD_GEM2 		(10)       	/*C66x CorePac2, L1/L2 RAMs*/
#define PSC_PD_GEM3 		(11)       	/*C66x CorePac3, L1/L2 RAMs*/
#define PSC_PD_GEM4 		(12)       	/*C66x CorePac4, L1/L2 RAMs*/
#define PSC_PD_GEM5 		(13)       	/*C66x CorePac5, L1/L2 RAMs*/
#define PSC_PD_GEM6 		(14)       	/*C66x CorePac6, L1/L2 RAMs*/
#define PSC_PD_GEM7 		(15)       	/*C66x CorePac7, L1/L2 RAMs*/

#define PSC_CD_MODRST0 			(0 )    /*Shared LPSC for all peripherals other than those listed in this table*/         
#define PSC_CD_MODSRC3_PWR 		(1 )    /*SmartReflex*/                                                                   
#define PSC_CD_EMIF4F 			(2 )    /*DDR3 EMIF*/                                                                     
#define PSC_CD_EMIF25_SPI 		(3 )    /*EMIF16 and SPI*/                                                                
#define PSC_CD_TSIP 			(4 )    /*TSIP*/                                                                          
#define PSC_CD_DEBUGSS_TRC 		(5 )    /*Debug Subsystem and Tracers*/                                                   
#define PSC_CD_TETB_TRC 		(6 )    /*Per-core TETB and System TETB*/                                                 
#define PSC_CD_PKTPROC 			(7 )    /*Packet Accelerator*/                                                            
#define PSC_CD_CPGMAC 			(8 )    /*Ethernet SGMIIs*/                                                               
#define PSC_CD_Crypto  			(9 )    /*Security Accelerator*/                                                          
#define PSC_CD_PCIEX 			(10)    /*PCIe*/                                                                          
#define PSC_CD_SRIO 			(11)    /*SRIO*/                                                                          
#define PSC_CD_HYPERBRIDGE 		(12)    /*HyperLink*/                                                                     
#define PSC_CD_L2SRAM 			(13)    /*Reserved*/                                                                      
#define PSC_CD_MSMCSRAM 		(14)    /*MSMC RAM*/                                                                      
#define PSC_CD_GEM0  			(15)    /*C66x CorePac0 and Timer 0*/                                                     
#define PSC_CD_GEM1 			(16)    /*C66x CorePac1 and Timer 1*/                                                                                  
#define PSC_CD_GEM2 			(17)	/*C66x CorePac2 and Timer 2*/
#define PSC_CD_GEM3 			(18)	/*C66x CorePac3 and Timer 3*/
#define PSC_CD_GEM4  			(19)	/*C66x CorePac4 and Timer 4*/
#define PSC_CD_GEM5 			(20)	/*C66x CorePac5 and Timer 5*/
#define PSC_CD_GEM6 			(21)	/*C66x CorePac6 and Timer 6*/
#define PSC_CD_GEM7 			(22)	/*C66x CorePac7 and Timer 7*/

/*typedef*/

/*global declarations*/


/* function declaration */
extern void corePacPowerPown(void);
extern void corePacPowerUp(void);
extern INT32  pscPowerDomainUp( UINT32 pscPdIndex);
extern INT32  pscClockDomainUp( UINT32 pscCdIndex);
extern void pscLocalReset(void);
extern void PowerUpDomains (void);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__PSC_DSP6678__*/
