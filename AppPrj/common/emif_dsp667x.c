/*

 文件名称：emif_dsp667x.c
摘要：主要实现dsp667x的emif初始化控制
*/
/* 修改历史:
2016.3.19,chengqb创建文件
*/

/* includes */ 
#include "KeyStone_common.h"
#include "datatype.h"
#include "delay.h"
#include "dsp667x.h"
#include "emif_dsp667x.h"
#include "psc_dsp667x.h"
#define PARAMTER_FLAG_MASK			(0x12345AA5)
/* defines */ 

#define DSPEMIF_REGS_BASE_ADDR              (0x20C00000)	/*基地址*/

/*==========emif 可以配置的总线类型===========*/
#define EMIFA_TYPE_SDRAM					(0)	/*EMIFA AS SDRAM 6678 not suport*/
#define EMIFA_TYPE_NAND						(1)
#define EMIFA_TYPE_ASYNCHRONOUS_CS2			(2)
#define EMIFA_TYPE_ASYNCHRONOUS_CS3			(3)
#define EMIFA_TYPE_ASYNCHRONOUS_CS4			(4)
#define EMIFA_TYPE_ASYNCHRONOUS_CS5			(5)

/*================寄存器设置值================*/
#define DSPEMIFA_AWCC_WP1(state)				((UINT32)((state)&0x1)<<29)
#define DSPEMIFA_AWCC_WP0(state)				((UINT32)((state)&0x1)<<28)
#define DSPEMIFA_AWCC_CCS5WAIT(whitchPin)		((UINT32)((whitchPin)&0x2)<<22)
#define DSPEMIFA_AWCC_CCS4WAIT(whitchPin)		((UINT32)((whitchPin)&0x2)<<20)
#define DSPEMIFA_AWCC_CCS3WAIT(whitchPin)		((UINT32)((whitchPin)&0x2)<<18)
#define DSPEMIFA_AWCC_CCS2WAIT(whitchPin)		((UINT32)((whitchPin)&0x2)<<16)
#define DSPEMIFA_AWCC_MAXEXTWAIT(waitNum)		((UINT32)((waitNum)&0xFF)<<0)

#define DSPEMIFA_CEXCFG_SS(enable)				((UINT32)((enable)&0x1)<<31)
#define DSPEMIFA_CEXCFG_EW(enable)				((UINT32)((enable)&0x1)<<30)
#define DSPEMIFA_CEXCFG_WSETUP(width)			((UINT32)((width)&0xF)<<26)
#define DSPEMIFA_CEXCFG_WSTROBE(width)			((UINT32)((width)&0x3F)<<20)
#define DSPEMIFA_CEXCFG_WHOLD(width)			((UINT32)((width)&0x7)<<17)
#define DSPEMIFA_CEXCFG_RSETUP(width)			((UINT32)((width)&0xF)<<13)
#define DSPEMIFA_CEXCFG_RSTROBE(width)			((UINT32)((width)&0x3F)<<7)
#define DSPEMIFA_CEXCFG_RHOLD(width)			((UINT32)((width)&0x7)<<4)
#define DSPEMIFA_CEXCFG_TA(width)				((UINT32)((width)&0x3)<<2)
#define DSPEMIFA_CEXCFG_ASIZE(width)			((UINT32)((width)&0x3)<<0)

/* typedefs */  
typedef struct  __emifRegs {
    VOLATILE UINT32 rcsr;				//00h
    VOLATILE UINT32 awccr;				//04h
    VOLATILE UINT8 rsvd0[8];			//
    VOLATILE UINT32 a0cr;				//10h
    VOLATILE UINT32 a1cr;				//14h
    VOLATILE UINT32 a2cr;				//18h
    VOLATILE UINT32 a3cr;				//1Ch 
    VOLATILE UINT8 rsvd1[32];           //
    VOLATILE UINT32 irr;				//40h	
    VOLATILE UINT32 imr;				//44h	
    VOLATILE UINT32 imsr;				//48h	
    VOLATILE UINT32 imcr;				//4Ch	
    VOLATILE UINT32 iocr;				//	
    VOLATILE UINT32 iosr;				//	
    VOLATILE UINT8 rsvd2[8];			//	
    VOLATILE UINT32 nandfcr;			//60h 	
    VOLATILE UINT32 nandfsr;			//64h	
    VOLATILE UINT32 pmcr;				//68h 	
    VOLATILE UINT8 rsvd3[4];			//	
    VOLATILE UINT32 nfeccce0;			//70h 	
    VOLATILE UINT32 nfeccce1;			//74h	
    VOLATILE UINT32 nfeccce2;			//78h	
    VOLATILE UINT32 nfeccce3;			//7Ch	
    VOLATILE UINT8 rsvd4[4];			//	
    VOLATILE UINT32 iodftexecnt;		//	
    VOLATILE UINT32 iodftgblctrl;		//	
    VOLATILE UINT8 rsvd5[4];			//	
    VOLATILE UINT32 iodfttlamisr;		//	
    VOLATILE UINT32 iodfttldmisr;		//	
    VOLATILE UINT32 iodfttldcmisr;		//	
    VOLATILE UINT8 rsvd6[20];			//	
    VOLATILE UINT32 modrelnum;			//	
    VOLATILE UINT8 rsvd7[8];			//	
    VOLATILE UINT32 nandf4becclr;		//BCh
    VOLATILE UINT32 nandf4becc1r;		//C0h 	
    VOLATILE UINT32 nandf4becc2r;		//C4h	
    VOLATILE UINT32 nandf4becc3r;		//C8h	
    VOLATILE UINT32 nandf4becc4r;		//CCh	
    VOLATILE UINT32 nandfea1r;			//D0h	
    VOLATILE UINT32 nandfea2r;			//D4h	
    VOLATILE UINT32 nandfev1r;			//D8h 	
    VOLATILE UINT32 nandfev2r;			//DCh	
} EMIFREGS;				
/* globals */ 

/* locals */

/* local function declarations */

/*global function define*/ 
INT32 emifInit(void)
{
	
	return 0;
}

/*cs2~cs5*/
INT32 emifaInit(UINT8 emifaType, EMIF_PARAMETER* pCfg)
{
	EMIF_PARAMETER* pEmifCfg = (EMIF_PARAMETER*)pCfg;
	VOLATILE EMIFREGS *pReg = (VOLATILE EMIFREGS*)DSPEMIF_REGS_BASE_ADDR;
	LOCAL BOOL first = TRUE;

	if(pEmifCfg->emifParamtertFlag != PARAMTER_FLAG_MASK) //使用默认参数
	{
		pEmifCfg->emifTim.emifTim6678.ta = 0x1;
		pEmifCfg->emifTim.emifTim6678.asize = 0x1;
		pEmifCfg->emifTim.emifTim6678.wsetup = 0xA;
		pEmifCfg->emifTim.emifTim6678.wstrobe = 0x16;
		pEmifCfg->emifTim.emifTim6678.whold = 0x5;
		pEmifCfg->emifTim.emifTim6678.rsetup = 0xA;
		pEmifCfg->emifTim.emifTim6678.rstrobe = 0x16;
		pEmifCfg->emifTim.emifTim6678.rhold = 0x5;
	}
	else
	{
//		pEmifCfg->emifTim.emifTim6678.ta = 0x3;
//		pEmifCfg->emifTim.emifTim6678.asize = 0x1;
//		if(pEmifCfg->emifBusSize == 8)
//		{
//			pEmifCfg->emifTim.emifTim6678.asize = 0x0;
//		}
	}

	if(first && (emifaType>=EMIFA_TYPE_ASYNCHRONOUS_CS2) && (emifaType<=EMIFA_TYPE_ASYNCHRONOUS_CS5))
	{
		first = FALSE;
		pscPowerDomainUp(PSC_PD_ALWAYSON);
		pscClockDomainUp(PSC_CD_EMIF25_SPI);

		pReg->awccr = DSPEMIFA_AWCC_WP1(0)
						| DSPEMIFA_AWCC_WP0(0)
						| DSPEMIFA_AWCC_CCS5WAIT(0)
						| DSPEMIFA_AWCC_CCS4WAIT(0)
						| DSPEMIFA_AWCC_CCS3WAIT(0)
						| DSPEMIFA_AWCC_CCS2WAIT(0)
						| DSPEMIFA_AWCC_MAXEXTWAIT(0x0);
	}	

	switch(emifaType)
	{
		case EMIFA_TYPE_SDRAM:	/*配置SDRAM*/
			break;
		case EMIFA_TYPE_NAND:	/*配置NAND*/
			break;
		case EMIFA_TYPE_ASYNCHRONOUS_CS2: /*配置异步总线片选1*/ 	/*flash*/	
			pReg->a0cr = DSPEMIFA_CEXCFG_SS(0) 			/*0:Normal Mode enabled. 1:Select Strobe Mode enabled.*/
					  | DSPEMIFA_CEXCFG_EW(0) 			/*Extended wait cycles disabled. 1:Extended wait cycles enabled.*/
					  | DSPEMIFA_CEXCFG_WSETUP(pEmifCfg->emifTim.emifTim6678.wsetup)		//0x0f
					  | DSPEMIFA_CEXCFG_WSTROBE(pEmifCfg->emifTim.emifTim6678.wstrobe)		//0x3f
					  | DSPEMIFA_CEXCFG_WHOLD(pEmifCfg->emifTim.emifTim6678.whold)			//0x07
					  | DSPEMIFA_CEXCFG_RSETUP(pEmifCfg->emifTim.emifTim6678.rsetup)		//0x0f
					  | DSPEMIFA_CEXCFG_RSTROBE(pEmifCfg->emifTim.emifTim6678.rstrobe)		//0x3f
					  | DSPEMIFA_CEXCFG_RHOLD(pEmifCfg->emifTim.emifTim6678.rhold)			//0x07
					  | DSPEMIFA_CEXCFG_TA(pEmifCfg->emifTim.emifTim6678.ta)				//0x3
					  | DSPEMIFA_CEXCFG_ASIZE(pEmifCfg->emifTim.emifTim6678.asize); 		/*0:8-bit data bus ,1:16-bit data bus*/
			break;
		case EMIFA_TYPE_ASYNCHRONOUS_CS3: /*配置异步总线片选2*/ 	 
			pReg->a1cr = DSPEMIFA_CEXCFG_SS(0) 			
					  | DSPEMIFA_CEXCFG_EW(0) 			
					  | DSPEMIFA_CEXCFG_WSETUP(pEmifCfg->emifTim.emifTim6678.wsetup)
					  | DSPEMIFA_CEXCFG_WSTROBE(pEmifCfg->emifTim.emifTim6678.wstrobe)
					  | DSPEMIFA_CEXCFG_WHOLD(pEmifCfg->emifTim.emifTim6678.whold)
					  | DSPEMIFA_CEXCFG_RSETUP(pEmifCfg->emifTim.emifTim6678.rsetup)
					  | DSPEMIFA_CEXCFG_RSTROBE(pEmifCfg->emifTim.emifTim6678.rstrobe)
					  | DSPEMIFA_CEXCFG_RHOLD(pEmifCfg->emifTim.emifTim6678.rhold)
					  | DSPEMIFA_CEXCFG_TA(pEmifCfg->emifTim.emifTim6678.ta)
					  | DSPEMIFA_CEXCFG_ASIZE(pEmifCfg->emifTim.emifTim6678.asize); 		
			break;
		case EMIFA_TYPE_ASYNCHRONOUS_CS4: /*配置异步总线片选3*/       
			pReg->a2cr = DSPEMIFA_CEXCFG_SS(0) 			
					  | DSPEMIFA_CEXCFG_EW(0) 			
					  | DSPEMIFA_CEXCFG_WSETUP(pEmifCfg->emifTim.emifTim6678.wsetup)
					  | DSPEMIFA_CEXCFG_WSTROBE(pEmifCfg->emifTim.emifTim6678.wstrobe)
					  | DSPEMIFA_CEXCFG_WHOLD(pEmifCfg->emifTim.emifTim6678.whold)
					  | DSPEMIFA_CEXCFG_RSETUP(pEmifCfg->emifTim.emifTim6678.rsetup)
					  | DSPEMIFA_CEXCFG_RSTROBE(pEmifCfg->emifTim.emifTim6678.rstrobe)
					  | DSPEMIFA_CEXCFG_RHOLD(pEmifCfg->emifTim.emifTim6678.rhold)
					  | DSPEMIFA_CEXCFG_TA(pEmifCfg->emifTim.emifTim6678.ta)
					  | DSPEMIFA_CEXCFG_ASIZE(pEmifCfg->emifTim.emifTim6678.asize); 	
			break;
		case EMIFA_TYPE_ASYNCHRONOUS_CS5: /*配置异步总线片选4*/ 		
			pReg->a3cr =  DSPEMIFA_CEXCFG_SS(0) 	
					  | DSPEMIFA_CEXCFG_EW(0) 		
					  | DSPEMIFA_CEXCFG_WSETUP(pEmifCfg->emifTim.emifTim6678.wsetup)
					  | DSPEMIFA_CEXCFG_WSTROBE(pEmifCfg->emifTim.emifTim6678.wstrobe)
					  | DSPEMIFA_CEXCFG_WHOLD(pEmifCfg->emifTim.emifTim6678.whold)
					  | DSPEMIFA_CEXCFG_RSETUP(pEmifCfg->emifTim.emifTim6678.rsetup)
					  | DSPEMIFA_CEXCFG_RSTROBE(pEmifCfg->emifTim.emifTim6678.rstrobe)
					  | DSPEMIFA_CEXCFG_RHOLD(pEmifCfg->emifTim.emifTim6678.rhold)
					  | DSPEMIFA_CEXCFG_TA(pEmifCfg->emifTim.emifTim6678.ta)
					  | DSPEMIFA_CEXCFG_ASIZE(pEmifCfg->emifTim.emifTim6678.asize); 
			break;

		default:
			break;
	}
	return 0;
}

INT32 dsp667x_emifInit(void* pCfg)
{
	EMIF_PARAMETER* pPllCfg = (EMIF_PARAMETER*)pCfg;	
	EMIF_PARAMETER defaultCfg[4];

	if(pPllCfg == NULL)
	{
		pPllCfg = &defaultCfg[0];
		
	}
	pscPowerDomainUp(PSC_PD_ALWAYSON);
	pscClockDomainUp(PSC_CD_EMIF25_SPI);


	pPllCfg[2].emifTim.emifTim6678.ta = 0x1;
	pPllCfg[2].emifTim.emifTim6678.asize = 0x1;
	pPllCfg[2].emifTim.emifTim6678.wsetup = 0x3;
	pPllCfg[2].emifTim.emifTim6678.wstrobe = 0x10;
	pPllCfg[2].emifTim.emifTim6678.whold = 0x1;
	pPllCfg[2].emifTim.emifTim6678.rsetup = 0x3;
	pPllCfg[2].emifTim.emifTim6678.rstrobe = 0x10;
	pPllCfg[2].emifTim.emifTim6678.rhold = 0x1;
	pPllCfg[2].emifParamtertFlag=PARAMTER_FLAG_MASK;

	emifaInit(EMIFA_TYPE_ASYNCHRONOUS_CS2, &pPllCfg[0]);
	emifaInit(EMIFA_TYPE_ASYNCHRONOUS_CS3, &pPllCfg[1]);
	emifaInit(EMIFA_TYPE_ASYNCHRONOUS_CS4, &pPllCfg[2]);
	emifaInit(EMIFA_TYPE_ASYNCHRONOUS_CS5, &pPllCfg[3]);

	return 0x0;
}


/*local function define*/
