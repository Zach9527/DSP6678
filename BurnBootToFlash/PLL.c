/******************************************************************************
 * 文件名:  PLL.c
 *
 * 文件描述:	配置DSP的主频时钟
 */
#include <stdio.h>
#include <ti/csl/csl_pllc.h>
#include <ti/csl/csl_pllcAux.h>
#define REF_CLOCK_KHZ 100000
#define TARGET_FREQ   1000
#define PLL1_MULTIPLIER (TARGET_FREQ/(REF_CLOCK_KHZ/1000))
#define PLATFORM_BASE_CLK_RATE_MHZ   100
// Global Register and constant definitions
// Global timeout value
#define GTIMEOUT 1000

#define CHIP_LEVEL_REG  0x02620000
#define KICK0			*(unsigned int*)(CHIP_LEVEL_REG + 0x0038)
#define KICK1			*(unsigned int*)(CHIP_LEVEL_REG + 0x003C)
#define KICK0_UNLOCK (0x83E70B13)
#define KICK1_UNLOCK (0x95A4F1E0)
#define KICK_LOCK    0
#define MAINPLLCTL0		*(unsigned int*)(CHIP_LEVEL_REG + 0x0328)
#define MAINPLLCTL1		*(unsigned int*)(CHIP_LEVEL_REG + 0x032C)
// PLL 1 definitions (DSP clk and subsystems)
#define PLL1_BASE           0x02310000
#define PLL1_RSCTL          (PLL1_BASE + 0x0e8)   // PLL1 Reset Control
#define PLL1_RSCFG          (PLL1_BASE + 0x0ec)   // PLL1 Reset Config

#define PLL1_PLLCTL         (PLL1_BASE + 0x100)   // PLL1 Control
#define PLL1_SECCTL         (PLL1_BASE + 0x108)
#define PLL1_PLLM           (PLL1_BASE + 0x110)   // PLL1 Multiplier
#define PLL1_DIV1           (PLL1_BASE + 0x118)   // DIV1 divider
#define PLL1_DIV2           (PLL1_BASE + 0x11C)   // DIV2 divider
#define PLL1_DIV3           (PLL1_BASE + 0x120)   // DIV3 divider
#define PLL1_CMD            (PLL1_BASE + 0x138)   // CMD control
#define PLL1_STAT           (PLL1_BASE + 0x13C)   // STAT control
#define PLL1_ALNCTL         (PLL1_BASE + 0x140)   // ALNCTL control
#define PLL1_DCHANGE        (PLL1_BASE + 0x144)   // DCHANGE status
#define PLL1_CKEN           (PLL1_BASE + 0x148)   // CKEN control
#define PLL1_CKSTAT         (PLL1_BASE + 0x14C)   // CKSTAT status
#define PLL1_SYSTAT         (PLL1_BASE + 0x150)   // SYSTAT status
#define PLL1_DIV4           (PLL1_BASE + 0x160)   // DIV4 divider
#define PLL1_DIV5           (PLL1_BASE + 0x164)   // DIV5 divider
#define PLL1_DIV6           (PLL1_BASE + 0x168)   // DIV6 divider
#define PLL1_DIV7           (PLL1_BASE + 0x16C)   // DIV7 divider
#define PLL1_DIV8           (PLL1_BASE + 0x170)   // DIV8 divider
#define PLL1_DIV9           (PLL1_BASE + 0x174)   // DIV9 divider
#define PLL1_DIV10          (PLL1_BASE + 0x178)   // DIV10 divider
#define PLL1_DIV11          (PLL1_BASE + 0x17C)   // DIV11 divider
#define PLL1_DIV12          (PLL1_BASE + 0x180)   // DIV12 divider
#define PLL1_DIV13          (PLL1_BASE + 0x184)   // DIV13 divider
#define PLL1_DIV14          (PLL1_BASE + 0x188)   // DIV14 divider
#define PLL1_DIV15          (PLL1_BASE + 0x18C)   // DIV15 divider
#define PLL1_DIV16          (PLL1_BASE + 0x190)   // DIV16 divider
#define PLL_REG_RSCTL_VALUE_KEY                  (0x5A69)
#define PLL_REG_RSCFG_FIELD_POWER_ON_RESET       (1<<13)


static Wait_Soft( int nloop )
{
    int i;
    for( i = 0 ; i < nloop ; i++ )
    {
    }
}

static int Set_Pll1( int pll_multiplier)
{
    unsigned int* pll_rsctl     = ( unsigned int* )PLL1_RSCTL;
    unsigned int* pll_rscfg     = ( unsigned int* )PLL1_RSCFG;
    unsigned int* pll_ctl       = ( unsigned int* )PLL1_PLLCTL;
    unsigned int* pll_mult      = ( unsigned int* )PLL1_PLLM;
    unsigned int* pll_alnctl    = ( unsigned int* )PLL1_ALNCTL;
    unsigned int* pll_dchange   = ( unsigned int* )PLL1_DCHANGE;
    unsigned int cfg;
    unsigned int rbmult;
    int iResult=0;

    // Default dividers
    unsigned int div2=3, div5=5, div8=64;

    unsigned int* pll_div2      = ( unsigned int* )PLL1_DIV2;
    unsigned int* pll_div5      = ( unsigned int* )PLL1_DIV5;
    unsigned int* pll_div8      = ( unsigned int* )PLL1_DIV8;
    unsigned int* pll_cmd       = ( unsigned int* )PLL1_CMD;
    unsigned int* pll_stat      = ( unsigned int* )PLL1_STAT;
    unsigned int* pll_secctl    = ( unsigned int* )PLL1_SECCTL;

    int dsp_freq;
    int dsp_freM,dsp_freD;

    rbmult = pll_multiplier;

        if (pll_multiplier>0 && pll_multiplier<=64)
        {


        	// Unlock Boot Config
        	KICK0 = KICK0_UNLOCK;
        	KICK1 = KICK1_UNLOCK;

             // Set bit 6 to a value of 1 in MAINPLLCTL1 register for PLL ENSAT Bit
             MAINPLLCTL1 |= (1 << 6);

            // config reset control (isolation)
            *pll_rsctl = PLL_REG_RSCTL_VALUE_KEY;
            cfg = *pll_rscfg | PLL_REG_RSCFG_FIELD_POWER_ON_RESET;
            *pll_rscfg = cfg;


            *pll_secctl = 0x00890000;

            //  Step 1: Set PLL to BYPASS mode
            *pll_ctl &= 0xFFFFFFDF;             // Set PLL to Bypass mode
            *pll_ctl &= 0xFFFFFFFE;

            // Wait Bypass mode switch
            // Bypass sw time is 4 clkin cycles
            // The following delay is much more than necessary...
            Wait_Soft(150);

            *pll_ctl |= 0x2;
            Wait_Soft(150);
            *pll_ctl &= ~0x2;
            Wait_Soft(150);

            //  Step 2: Configure and stabilize PLL
            *pll_ctl |= 0x8;                    // Reset PLL

            // Verify if pll is in power down
            if ((*pll_ctl & 0x00000002) !=0 )
            {
                *pll_ctl &= 0xFFFFFFFD;         // Power up PLL

                // Wait PLL Stabilization time
                // that is 150 usec
                // The following delay is much more than necessary and provide stable PLL...
                Wait_Soft(5000);
            }
            // Step 3: Set PLL multiplier (minus 1 desired value) (multiplier is splitted in 2 parts)
            // Set PLL multipler LSB
        	*pll_mult = pll_multiplier*2 - 1;

            // Set PLL multipler MSB
        	MAINPLLCTL0 |= (pll_multiplier << 23) & 0xFF000000;
        	MAINPLLCTL0 &= (pll_multiplier << 23) | 0x00FFFFFF;

            // Wait for GOSTAT to be cleared so no go operation is in progress
            while((*pll_stat & 0x01) !=0 ) Wait_Soft(150);

            // Step 4. Set PLL dividers if needed
            *pll_div2 = (0x8000) | (div2 - 1);
            *pll_div5 = (0x8000) | (div5 - 1);
            *pll_div8 = (0x8000) | (div8 - 1);

            // Adjust modified related sysclk align
            *pll_alnctl = *pll_dchange;

            // Gives the GO cmd
            *pll_cmd |= 0x00000001;

            // Wait for phase alignment
            while((*pll_stat & 0x01) !=0 )  Wait_Soft(150);

            // Step 5: Wait for PLL to lock

            // Wait for PLL to Reset
            // !!! M.T.
            // Reset time =128C
            Wait_Soft(1000);

            *pll_ctl &= 0xFFFFFFF7;             // Release PLL from Reset

            // Wait for PLL to LOCK
            // !!! M.T.
            // Lock time =2000C
            Wait_Soft(4000);

            *pll_secctl = 0x00090000;
            *pll_ctl = 0x00000041;             // Set PLL to PLL mode

            // Read back pll dividers and multipliers for validation
            div2 = (*pll_div2 & 0x7f) +1;
            div5 = (*pll_div5 & 0x7f) +1;
            div8 = (*pll_div8 & 0x7f) +1;
            rbmult = ((MAINPLLCTL0 >> 23) & 0x000000FF);

        	// Lock Boot Config
        	KICK0 = KICK_LOCK;
        	KICK1 = KICK_LOCK;

            // Compute the real dsp freq (*100)
            dsp_freq = ((REF_CLOCK_KHZ/10 * rbmult));

            // Displayed frequency setup
            // dsp freq in MHz
            dsp_freM = dsp_freq / 100;

            // dsp freq first decimal if freq expressed in MHz
            dsp_freD = ((dsp_freq - dsp_freM * 100) + 5) / 10;

            // Add roundup unit to MHz displayed and reajust decimal value if necessary...
            if (dsp_freD > 9)
            {
               dsp_freD = dsp_freD - 10;
               dsp_freM = dsp_freM + 1;
            }

        }
        else
        {
             iResult=1;
        }

    return(iResult);
}

unsigned int getcore_clk ()
{
	unsigned int pllM,preDiv,dsp_freq;
	unsigned int* pll_mult      = ( unsigned int* )PLL1_PLLM;
	unsigned int* pll_stat      = ( unsigned int* )PLL1_STAT;
    /* Unlock the Boot Config */
	KICK0 = KICK0_UNLOCK;
	KICK1 = KICK1_UNLOCK;


    pllM   = *pll_mult  & 0x3F;
    preDiv = MAINPLLCTL0& 0x3F;

    /* Make sure no GO operation is pending*/
    while((*pll_stat) & 0x00000001);

	KICK0 = KICK_LOCK;
	KICK1 = KICK_LOCK;
	dsp_freq =(pllM+1)>>1;
	dsp_freq = (dsp_freq * PLATFORM_BASE_CLK_RATE_MHZ)/(preDiv + 1);
	return (dsp_freq);
 }

