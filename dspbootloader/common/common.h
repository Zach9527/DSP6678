
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include <ti/csl/tistdtypes.h>
#include <ti/csl/cslr_device.h>
#include <ti/csl/cslr_bootcfg.h>
#include <ti/csl/cslr_cgem.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_xmc.h>
#include <ti/csl/csl_xmcAux.h>
#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/csl_cache.h>

/*----------------------Timer plus registers definition----------------*/
typedef struct {
    volatile Uint32 PID12;
    volatile Uint32 EMUMGT_CLKSPD;
    volatile Uint32 GPINT_EN;
    volatile Uint32 GPDIR_DAT;
    volatile Uint32 CNTLO;
    volatile Uint32 CNTHI;
    volatile Uint32 PRDLO;
    volatile Uint32 PRDHI;
    volatile Uint32 TCR;
    volatile Uint32 TGCR;
    volatile Uint32 WDTCR;
    volatile Uint32 TLGC;
    volatile Uint32 TLMR;
    volatile Uint32 RELLO;
    volatile Uint32 RELHI;
    volatile Uint32 CAPLO;
    volatile Uint32 CAPHI;
    volatile Uint32 INTCTL_STAT;
    volatile Uint8  RSVD0[24];
    volatile Uint32 TIMERLO_COMPARE_REG[8];
    volatile Uint8  RSVD1[32];
} CSL_TmrPlusRegs;
/*===============================Exception=============================*/
typedef	union	{
	volatile Uint32 MPFSR; /*copy of MPFSR register for L1P, L1D or LL2*/
	volatile Uint32 SMPFR; /*copy of SMPFR register for MSMC*/
	volatile Uint32 MPU_FAULT_STATUS; /*copy of FAULT_STATUS register for MPU*/
	volatile Uint32 L1PEDSTAT; /*copy of L1PEDSTAT register*/
	volatile Uint32 L2EDSTAT; /*copy of L2EDSTAT register*/
	volatile Uint32 SMESTAT; /*copy of SMESTAT register for SL2 EDC*/
	volatile Uint32 DDR_IRQSTATUS_SYS; /*copy of IRQSTATUS_SYS for DDR ECC*/
} Memory_Fault_Info;

typedef	struct{
	Uint32 fault_address;
	Memory_Fault_Info fault_status;
	volatile Uint32 BUS_ERROR; /*copy of MDMAERR or ECFGERR register*/
} Memory_Exception_Info;

typedef	struct{
	volatile Uint32 EMR; /*copy of TPTC_EMR register*/
	volatile Uint32 EMRH; /*copy of TPTC_EMRH register*/
	volatile Uint32 QEMR; /*copy of TPTC_QEMR register*/
	volatile Uint32 CCERR; /*copy of TPTC_CCERR register*/
} EDMA_CC_Exception_Info;

typedef	struct{
	volatile Uint32 ERRSTAT; /*copy of TPTC_ERRSTAT register*/
	volatile Uint32 ERRDET; /*copy of TPTC_ERRDET register*/
} EDMA_TC_Exception_Info;

typedef	union{
	EDMA_CC_Exception_Info CC_info;
	EDMA_TC_Exception_Info TC_info;
} EDMA_Exception_Info;


typedef	union	{
	volatile Uint32 INTXSTAT; /*copy of INTXSTAT register*/
	Memory_Exception_Info memory;
	EDMA_Exception_Info edma;
} Exception_Info;

typedef	struct{
	volatile Uint32 MEXPFLAG[4];  /*copy of the MEXPFLAG0..3 registers */
	volatile Uint32 CIC_STATUS[7];  /*copy of the CIC status registers */
	Exception_Info info;
} External_Exception_Status;

typedef	union	{
	volatile Uint32 IERR; /*copy of the IERR register */
	External_Exception_Status ext_sts;
} Exception_Status;

typedef struct {
	volatile Uint32 B3; /*copy of B3 register (return pointer of caller) */
	volatile Uint32 A4; /*copy of the A4 register (first input parameter of caller)*/
	volatile Uint32 B4; /*copy of the B4 register (second input parameter of caller)*/
	volatile Uint32 B14; /*copy of the B14 register (data pointer)*/
	volatile Uint32 B15; /*copy of the B15 register (stack pointer)*/
	volatile Uint32 TSCL; /*copy of the TSCL register (time stamp)*/
	volatile Uint32 TSCH; /*copy of the TSCH register (time stamp)*/
	volatile Uint32 NTSR; /*copy of the NTSR register */
	volatile Uint32 NRP; /*copy of the NRP register */
	volatile Uint32 EFR; /*copy of the EFR register */
	volatile Uint32 ITSR; /*copy of the ITSR register */
	volatile Uint32 IRP; /*copy of the IRP register */
	Exception_Status status;
} Exception_Record;

typedef enum
{
	DMA_NO_WAIT= 0,	/*do not wait DMA complete*/
	DMA_WAIT 			/*wait DMA complete*/
}DMA_Wait;

/* Register Overlay Structure MPAX*/
typedef struct
{
    volatile Uint32 MPAXL;
    volatile Uint32 MPAXH;
}MPAX_Regs;

/*memory protection and address extension configuration*/
typedef struct
{
    Uint32 BADDR; 	/*32-bit virtual base address*/
    /*36-bit physical replace address, right shift by 4 to get the value here)*/
    Uint32 RADDR;
    Uint32 SegementSize; 	/*Segment size in byte, must be power of 2*/
    Uint32 AccessPermisionMask; 	/*Access types allowed in this address range.*/
}MPAX_Config;
//data structure to save exception info
extern Exception_Record exception_record;

#define GLOBAL_ADDR(addr) ((Uint32)addr<0x1000000?\
						(Uint32)addr+(0x10000000+DNUM*0x1000000):\
						(Uint32)addr)

#define TMR_TCR_READRSTMODE_HI_SHIFT    (26)
#define TMR_TCR_CAPEVTMODE_LO_SHIFT     (12)
#define TMR_TCR_CAPMODE_LO_SHIFT        (11)
#define TMR_TCR_READRSTMODE_LO_SHIFT    (10)

#define TMR_TCR_READRSTMODE_HI_MASK    (1<<26)
#define TMR_TCR_CAPEVTMODE_LO_MASK     (3<<12)
#define TMR_TCR_CAPMODE_LO_MASK        (1<<11)
#define TMR_TCR_READRSTMODE_LO_MASK    (1<<10)

#define TMR_TGCR_PLUSEN_SHIFT 	       4
#define TMR_TGCR_PLUSEN_MASK 	       (1<<4)

#define TMR_INTCTLSTAT_EN_ALL_CLR_ALL   0x000F000F

#define CSL_TMR_WDTCR_WDKEY_CMD1         (0x0000A5C6u)
#define CSL_TMR_WDTCR_WDKEY_CMD2         (0x0000DA7Eu)

#define CSL_TMR_ENAMODE_CONT_RELOAD 	3

#define TSC_getDelay(startTSC) 	((unsigned int)((0xFFFFFFFFl+TSCL)- (unsigned long long)startTSC)+ 1)
#define TSC_count_cycle_from(startTSC) 	(TSC_getDelay(startTSC)- cycle_measure_overhead)


static inline unsigned int SWAP_ENDIAN(unsigned int byte_index)
{
#ifdef _BIG_ENDIAN
	return ((byte_index&0xFFFFFFFC)+(3-byte_index&3));
#else
	return byte_index;
#endif
}
#define CACHE_DISABLE_INT 	1
static inline void InvalidCache(void * blockPtr, Uint32 byteCnt)
{
#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	Uint32 uiOldGIE= _disable_interrupts();
#endif

	if(byteCnt>0xFFFF*4)
		byteCnt= 0xFFFF*4;
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_invL1d((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_invL2((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	_mfence();
	_mfence();

#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	asm(" nop 8");
	asm(" nop 8");
	_restore_interrupts(uiOldGIE); 	//restore interrupt
#endif
}

static inline void WritebackCache(void * blockPtr, Uint32 byteCnt)
{
	if(byteCnt>0xFFFF*4)
		byteCnt= 0xFFFF*4;
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_wbL1d((void *)blockPtr, byteCnt, CACHE_WAIT);
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_wbL2((void *)blockPtr, byteCnt, CACHE_WAIT);
	}
	_mfence();
	_mfence();
}

static inline void WritebackAllCache(void * blockPtr)
{
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_wbAllL1d(CACHE_WAIT);;
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_wbAllL2(CACHE_WAIT);
	}
	_mfence();
	_mfence();
}

static inline void WritebackInvalidCache(void * blockPtr, Uint32 byteCnt)
{
#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	Uint32 uiOldGIE= _disable_interrupts();
#endif

	if(byteCnt>0xFFFF*4)
		byteCnt= 0xFFFF*4;
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_wbInvL1d((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_wbInvL2((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	_mfence();
	_mfence();

#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	asm(" nop 8");
	asm(" nop 8");
	_restore_interrupts(uiOldGIE); 	//restore interrupt
#endif
}



/* Initialize Time stamp counter to measure cycles*/
extern void TSC_init();

/*delay in millisecond*/
extern void TSC_delay_ms(Uint32 ms);

/*delay in microsecond*/
extern void TSC_delay_us(Uint32 us);

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

extern CSL_CgemRegs * gpCGEM_regs ;
extern CSL_BootcfgRegs * gpBootCfgRegs;

#endif
