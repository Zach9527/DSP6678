/*

 文件名称：reg_dsp6746.h
摘要：主要实现dsp6746片上外设寄存器的地址定义以及相关宏值
*/
/* 修改历史:

2016.3.16,chengqb创建文件
*/

#ifndef __REG_DSP6746_H__
#define __REG_DSP6746_H__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/

/*typedef*/

/*global declarations*/

/*defines*/
#define HWREG(x) (*((VOLATILE UINT32*)(x)))

/********************************************************************************************
 *                     PLL control local Declarations                                          *
 *******************************************************************************************/

/**
 *  Handle to access BOOTCFG registers.
 */
#define hPscCfg     ((CSL_PscRegs*)CSL_PSC_REGS)

/**
  @}
  */
/* Boot Cfg Registers */
#define   DEVSTAT_REG           (*((VOLATILE UINT32 *) 0x02620020))
#define   MAINPLLCTL0_REG       (*((VOLATILE UINT32 *) 0x02620328))
#define   MAINPLLCTL1_REG       (*((VOLATILE UINT32 *) 0x0262032C))
#define   DDR3PLLCTL0_REG       (*((VOLATILE UINT32 *) 0x02620330))
#define   DDR3PLLCTL1_REG       (*((VOLATILE UINT32 *) 0x02620334))

/* PA PLL Registers */
#define   PAPLLCTL0_REG         (*((VOLATILE UINT32 *) 0x02620338))
#define   PAPLLCTL1_REG         (*((VOLATILE UINT32 *) 0x0262033C))

#define   OBSCLCTL_REG          (*((VOLATILE UINT32 *) 0x026203AC))

/*PLL controller registers*/
#define   PLLCTL_REG            (*((VOLATILE UINT32 *) 0x02310100))
#define   SECCTL_REG            (*((VOLATILE UINT32 *) 0x02310108))
#define   PLLM_REG              (*((VOLATILE UINT32 *) 0x02310110))
#define   PLLCMD_REG            (*((VOLATILE UINT32 *) 0x02310138))
#define   PLLSTAT_REG           (*((VOLATILE UINT32 *) 0x0231013C))
#define   PLLALNCTL_REG         (*((VOLATILE UINT32 *) 0x02310140))
#define   PLLDIV2_REG           (*((VOLATILE UINT32 *) 0x0231011C))
#define   PLLDIV5_REG           (*((VOLATILE UINT32 *) 0x02310164))
#define   PLLDIV8_REG           (*((VOLATILE UINT32 *) 0x02310170))
#define   PREDIV_REG            (*((VOLATILE UINT32 *) 0x02310114))

#define PA_PLL_OBS_CLK_SEL_MASK (1 << 4) /* OBSCLKCTL Register Bit 4 - set to 0 to see PA PLL reference (input) clock, set to 1 to see PA PLL output*/
#define PA_PLL_OBS_CLK_EN_MASK  (1 << 5) /* OBSCLKCTL Register Bit 5 - set to 1 to enable power to PA PLL observation clock*/

/* PA PLL Registers */
#define BYPASS_BIT_SHIFT 23
#define CLKF_BIT_SHIFT   6
#define PASSCLKSEL_MASK    (1 << 17)    /* Tells the configuration of the PASSCLKSEL pin */
#define PA_PLL_BYPASS_MASK (1 << BYPASS_BIT_SHIFT)    /* Tells whether the PA PLL is in BYPASS mode or not */
#define PA_PLL_CLKOD_MASK  (0x00780000) /* Tells the output divider value for the PA PLL */
#define PA_PLL_CLKF_MASK   (0x0007FFC0) /* Tells the multiplier value for the PA PLL */
#define PA_PLL_CLKR_MASK   (0x0000003F) /* Tells the divider value for the PA PLL */
#define PLL1_BASE           0x02310000
#define PLL1_PLLCTL              (*(unsigned int*)(PLL1_BASE + 0x100))   // PLL1 Control
#define PLL1_SECCTL              (*(unsigned int*)(PLL1_BASE + 0x108))   // PLL1 Sec Control
#define PLL1_PLLM                (*(unsigned int*)(PLL1_BASE + 0x110))   // PLL1 Multiplier
#define PLL1_DIV1                (*(unsigned int*)(PLL1_BASE + 0x118))   // DIV1 divider
#define PLL1_DIV2                (*(unsigned int*)(PLL1_BASE + 0x11C))   // DIV2 divider
#define PLL1_DIV3                (*(unsigned int*)(PLL1_BASE + 0x120))   // DIV3 divider
#define PLL1_CMD                 (*(unsigned int*)(PLL1_BASE + 0x138))   // CMD control
#define PLL1_STAT                (*(unsigned int*)(PLL1_BASE + 0x13C))   // STAT control
#define PLL1_ALNCTL              (*(unsigned int*)(PLL1_BASE + 0x140))   // ALNCTL control
#define PLL1_DCHANGE             (*(unsigned int*)(PLL1_BASE + 0x144))   // DCHANGE status
#define PLL1_CKEN                (*(unsigned int*)(PLL1_BASE + 0x148))   // CKEN control
#define PLL1_CKSTAT              (*(unsigned int*)(PLL1_BASE + 0x14C))   // CKSTAT status
#define PLL1_SYSTAT              (*(unsigned int*)(PLL1_BASE + 0x150))   // SYSTAT status
#define PLL1_DIV4                (*(unsigned int*)(PLL1_BASE + 0x160))   // DIV4 divider
#define PLL1_DIV5                (*(unsigned int*)(PLL1_BASE + 0x164))   // DIV5 divider
#define PLL1_DIV6                (*(unsigned int*)(PLL1_BASE + 0x168))   // DIV6 divider
#define PLL1_DIV7                (*(unsigned int*)(PLL1_BASE + 0x16C))   // DIV7 divider
#define PLL1_DIV8                (*(unsigned int*)(PLL1_BASE + 0x170))   // DIV8 divider
#define PLL1_DIV9                (*(unsigned int*)(PLL1_BASE + 0x174))   // DIV9 divider
#define PLL1_DIV10               (*(unsigned int*)(PLL1_BASE + 0x178))   // DIV10 divider
#define PLL1_DIV11               (*(unsigned int*)(PLL1_BASE + 0x17C))   // DIV11 divider
#define PLL1_DIV12               (*(unsigned int*)(PLL1_BASE + 0x180))   // DIV12 divider
#define PLL1_DIV13               (*(unsigned int*)(PLL1_BASE + 0x184))   // DIV13 divider
#define PLL1_DIV14               (*(unsigned int*)(PLL1_BASE + 0x188))   // DIV14 divider
#define PLL1_DIV15               (*(unsigned int*)(PLL1_BASE + 0x18C))   // DIV15 divider
#define PLL1_DIV16               (*(unsigned int*)(PLL1_BASE + 0x190))   // DIV16 divider

#define BWADJ_BIT_SHIFT     24
#define BYPASS_BIT_SHIFT    23
#define CLKF_BIT_SHIFT      6
#define PA_PLL_BYPASS_MASK (1 << BYPASS_BIT_SHIFT)    /* Tells whether the PA PLL is in BYPASS mode or not */
#define PA_PLL_BWADJ_MASK (1 << BWADJ_BIT_SHIFT) /* Tells the bandwidth adjust value for the PA PLL */
#define PA_PLL_CLKOD_MASK  (0x00780000) /* Tells the output divider value for the PA PLL */
#define PA_PLL_CLKF_MASK   (0x0007FFC0) /* Tells the multiplier value for the PA PLL */
#define PA_PLL_CLKR_MASK   (0x0000003F) /* Tells the divider value for the PA PLL */

#define ENSAT_BIT_SHIFT 6
#define RESET_BIT_SHIFT 14
#define PA_PLL_ENSAT_MASK (1 << ENSAT_BIT_SHIFT) /* Tells the configuration of the ENSAT bit */
#define PA_PLL_RESET_MASK (1 << RESET_BIT_SHIFT) /* Tells the configuration of the RESET bit */





/*****************************************************************************/
/*设备状态、控制寄存器												  		 */
/*****************************************************************************/
#define DSPPDSCREGS_BASE_ADDR                   		(0x02620000)	/*基地址*/

//主要用于核给核自身产生NMI中断
#define DSPDSCREGS_NMIGRx(index)						(0x200+(4*(index)))

//主要用于核间中断通信，比如core0向core5中断，core0就向IPCGR5写数据
#define DSPDSCREGS_IPCGRx(index)						(0x240+4*(index))
//产生中断时根据该寄存器判断中断源，然后清除中断状态
#define DSPDSCREGS_IPCARx(index)						(0x280+4*(index))
//主要用于本DSP向其他DSP产生中断，用于芯片与芯片之间的中断通信
#define DSPDSCREGS_IPCGRH								(0x27C)
#define DSPDSCREGS_IPCARH								(0x2BC)

#define DSPPDSCREGS_DEVSPEED							(0x3F8)			/*寄存器偏移量*/















/* function declaration */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__REG_DSP6746_H__*/


