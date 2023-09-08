/******************************************************************************
 * 文件名:  emif.c
 *
 * 文件描述:	初始化EMIF接口
 *
 */

#include "ti/csl/csl_types.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ti/csl/csl_chip.h"
#include "ti/csl/csl_chipAux.h"
#include "ti/csl/cslr_device.h"
#include "ti/csl/cslr_psc.h"
#include "ti/csl/csl_psc.h"
#include "ti/csl/csl_pscAux.h"
#include "ti/csl/cslr_emif16.h"

#define hEmif16Cfg     ((CSL_Emif16Regs*)CSL_EMIF16_REGS)

void platform_delaycycles(uint32_t cycles)
{
	uint32_t start_val  = CSL_chipReadTSCL();

	while ((CSL_chipReadTSCL() - start_val) < cycles);

    return;
}

unsigned int emif16_init (void)
{
    uint32_t     power_domain_num            = 0;
    uint32_t     mdctl_emif16_module_num     = 3;//3
    uint32_t     mdstat_emif16_module_num    = 3;//3

    unsigned int delay;

    CSL_PSC_MODSTATE mdstat;

    /* Wake up EMIF16 module:
       mdstat = CSL_PSC_getModuleState(mdstat_emif16_module_num); */
    {
       uint32_t  loop_cnt = 0;

       /* program pdctl and mdctl to enable the module. */
       CSL_PSC_enablePowerDomain(power_domain_num);
       CSL_PSC_setModuleNextState (mdctl_emif16_module_num, PSC_MODSTATE_ENABLE);

       // start the process and wait. but timeout in 1000 loops.
       CSL_PSC_startStateTransition(power_domain_num);
       while(((CSL_PSC_isStateTransitionDone (power_domain_num)) != 0) && (loop_cnt < 1000)) {
           loop_cnt++;
       }

       delay = 0x1000;
       while(delay--);

       mdstat = CSL_PSC_getModuleState(mdstat_emif16_module_num);

       delay = 0x1000;
       while(delay--);
       /* report result. */
       if (mdstat != PSC_MODSTATE_ENABLE) {
          return FAIL; /* Could not enable the PSC Module */
       }
    }


    hEmif16Cfg->A0CR = (0                                         \
                 | (1 << 31)     /* selectStrobe */ \
                 | (0 << 30)     /* extWait (never with NAND) */ \
                 | (0xf << 26)   /* writeSetup  10 ns */ \
                 | (0x3f << 20)  /* writeStrobe 40 ns */ \
                 | (7 << 17)     /* writeHold   10 ns */ \
                 | (0xf << 13)   /* readSetup   10 ns */ \
                 | (0x3f << 7)   /* readStrobe  60 ns */ \
                 | (7 << 4)      /* readHold    10 ns */ \
                 | (3 << 2)      /* turnAround  40 ns */ \
                 | (1 << 0));   /* asyncSize   16-bit bus */ \


  hEmif16Cfg->A1CR = (0                 \
            | (1 << 31)     /* selectStrobe */ \
            | (0 << 30)     /* extWait (never with NAND) */ \
            | (0x1 << 26)     /*0xf writeSetup  10 ns */ \
            | ( 0x1<< 20)       /*0x3f writeStrobe 40 ns */ \
            | (1 << 17)     /*7 writeHold   10 ns */ \
            | ( 0x1<< 13)   /*0xf readSetup   10 ns */ \
            | ( 0x1<< 7)   /*0x3f readStrobe  60 ns */ \
            | (1 << 4)      /* 7 readHold    10 ns */ \
            | (1 << 2)      /* turnAround  40 ns */ \
            | (1 << 0));   /* asyncSize   16-bit bus */ \

   hEmif16Cfg->A2CR = (0                                         \
                | (1 << 31)     /* selectStrobe */ \
                | (0 << 30)     /* extWait (never with NAND) */ \
                | (0xf << 26)   /* writeSetup  10 ns */ \
                | (0x3f << 20)  /* writeStrobe 40 ns */ \
                | (7 << 17)     /* writeHold   10 ns */ \
                | (0xf << 13)   /* readSetup   10 ns */ \
                | (0x3f << 7)   /* readStrobe  60 ns */ \
                | (7 << 4)      /* readHold    10 ns */ \
                | (3 << 2)      /* turnAround  40 ns */ \
                | (1 << 0));   /* asyncSize   16-bit bus */ \

   hEmif16Cfg->A3CR = (0                                         \
                    | (1 << 31)     /* selectStrobe */ \
                    | (0 << 30)     /* extWait (never with NAND) */ \
                    | (0xf << 26)   /* writeSetup  10 ns */ \
                    | (0x3f << 20)  /* writeStrobe 40 ns */ \
                    | (7 << 17)     /* writeHold   10 ns */ \
                    | (0xf << 13)   /* readSetup   10 ns */ \
                    | (0x3f << 7)   /* readStrobe  60 ns */ \
                    | (7 << 4)      /* readHold    10 ns */ \
                    | (3 << 2)      /* turnAround  40 ns */ \
                    | (1 << 0));   /* asyncSize   16-bit bus */ \

    /* Set the wait polarity */
    hEmif16Cfg->AWCCR = (0x10            /*0x80 max extended wait cycle */ \
        | (0 << 16)     /* CS2 uses WAIT0 */    \
        | (0 << 28));  /* WAIT0 polarity low */ \


    hEmif16Cfg->IRR = (1   /* clear async timeout */ \
        | (1 << 2));      /* clear wait rise */


    return SUCCESS;
}
