/******************************************************************************
 * Copyright (c) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *****************************************************************************/

/******************************************************************************
 *
 * File	Name:       evmc6678.c
 *
 * Description: This contains   TMS320C6678 specific functions.
 * 
 ******************************************************************************/
 
/************************
 * Include Files
 ************************/
#include "platform_internal.h"

 /**
  *  Handle to access BOOTCFG registers.
  */
#define hPscCfg     ((CSL_PscRegs*)CSL_PSC_REGS)
 
 /**
 @}
 */
/* Boot Cfg Registers */
#define   MAINPLLCTL0_REG       (*((volatile uint32_t *) 0x02620328))
#define   MAINPLLCTL1_REG       (*((volatile uint32_t *) 0x0262032C))
#define   DDR3PLLCTL0_REG       (*((volatile uint32_t *) 0x02620330))
#define   DDR3PLLCTL1_REG       (*((volatile uint32_t *) 0x02620334))

/* PA PLL Registers */
#define   PAPLLCTL0_REG         (*((volatile uint32_t *) 0x02620338))
#define   PAPLLCTL1_REG         (*((volatile uint32_t *) 0x0262033C))

/*PLL controller registers*/
#define   PLLCTL_REG            (*((volatile uint32_t *) 0x02310100))
#define   SECCTL_REG            (*((volatile uint32_t *) 0x02310108))
#define   PLLM_REG              (*((volatile uint32_t *) 0x02310110))
#define   PLLCMD_REG            (*((volatile uint32_t *) 0x02310138))
#define   PLLSTAT_REG           (*((volatile uint32_t *) 0x0231013C))
#define   PLLDIV2_REG           (*((volatile uint32_t *) 0x0231011C))
#define   PLLDIV5_REG           (*((volatile uint32_t *) 0x02310164))
#define   PLLDIV8_REG           (*((volatile uint32_t *) 0x02310170))
#define   PREDIV_REG            (*((volatile uint32_t *) 0x02310114))


CSL_Status CorePllcHwSetup (
    PllcHwSetup          *hwSetup
)
{
    CSL_Status       status = CSL_SOK;
    volatile uint32_t i, loopCount;
    uint32_t ctl,secctl, pllstatus;

    /* Unlock the Boot Config */
    CSL_BootCfgUnlockKicker();

    /*In PLLCTL, write PLLENSRC = 0 (enable PLLEN bit)*/    
    /* Program pllen=0 (pll bypass), pllrst=1 (reset pll), pllsrc = 0 */

    ctl         = PLLCTL_REG;
    ctl        &= ~(0x00000031);
    PLLCTL_REG = ctl;

    /* Enable secondary controller pll bypass */
    secctl     = SECCTL_REG;
    secctl     |= 1 << 23;
    SECCTL_REG = secctl;


/* PLL WORK AROUND FOR THE SI BUG */
    /* Reset the PLL, wait at least 5 us, release reset */
    ctl = ctl | 2;
    PLLCTL_REG = ctl;

    loopCount = 50000;
    while (loopCount--) {
        asm("   NOP");
    }

    ctl = ctl & ~2;
    PLLCTL_REG = ctl;

    loopCount = 50000;
    while (loopCount--) {
        asm("   NOP");
    }

    
    /* Reset the PLL */
      ctl = ctl | (1 << 3);
      PLLCTL_REG = ctl;
/* WORK AROUND ENDS */

    /* Enable the pll divider */
    secctl = SECCTL_REG;
    secctl |= (1 << 16);
    secctl |= (1 << 19);
    SECCTL_REG = secctl;

    MAINPLLCTL0_REG  = hwSetup->preDiv & 0x3f; /* PLLD[5:0] */
    MAINPLLCTL0_REG |= (((hwSetup->pllM) >> 6) & 0x7f) << 12; /* PLLM[12:6] */
    PLLM_REG   = hwSetup->pllM & 0x3f; /* PLLM[5:0] */

    MAINPLLCTL0_REG      |= (((hwSetup->pllM+1)>>1)-1) << 24;  /* BWADJ bits */

    /* PLL Advisory 9 fix */
    MAINPLLCTL1_REG      |= 1 << 6;

    /*If necessary program PLLDIV1n.  Note that you must aplly the GO operation
     to change these dividers to new ratios*/
     if (hwSetup->divEnable & PLLC_DIVEN_PLLDIV2) {
        PLLDIV2_REG = (hwSetup->pllDiv2) | 0x00008000;        
     }
     if (hwSetup->divEnable & PLLC_DIVEN_PLLDIV5) {
        PLLDIV5_REG = (hwSetup->pllDiv5) | 0x00008000;
     }
     if (hwSetup->divEnable & PLLC_DIVEN_PLLDIV8) {
        PLLDIV8_REG = (hwSetup->pllDiv8) | 0x00008000;
     }

    /*Set GOSET bit in PLLCMD to initiate the GO operation to change the divide
    values and align the SYSCLKs as programmed */
    PLLCMD_REG |= 0x00000001;

    loopCount = 2000;
    while (loopCount--) {
        asm("   NOP");
    }

    /* set pllrst to 0 to deassert pll reset */
    ctl = ctl & ~(1<<3);
    PLLCTL_REG = ctl;


    /* wait for the pll to lock, but don't trap if lock is never read */
    for (i = 0; i < 100; i++)  {
        loopCount = 2000;
        while (loopCount--) {
            asm("   NOP");
        }
      pllstatus = PLLSTAT_REG;
      if ( (pllstatus & 0x1) != 0 )
        break;
    }

    /* Clear the secondary controller bypass bit */
    secctl = secctl & ~(1<<23);
    SECCTL_REG = secctl;
    

    /* Set pllen to 1 to enable pll mode */
    ctl = ctl | 0x1;
    PLLCTL_REG = ctl;

    loopCount = 8000;
    while (loopCount--) {
        asm("   NOP");
    }
    
    return status;
}
