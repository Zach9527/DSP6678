/*

 文件名称：dsp667x.h
摘要：
*/
/* 修改历史:

2016.3.14,chengqb创建文件
*/

#ifndef __DSP667X_H__
#define __DSP667X_H__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/




#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>

#include <ti/csl/csl_version.h>
#include <ti/csl/csl_error.h>
#include <ti/csl/cslr.h>
#include <ti/csl/csl.h>


//#include "./qmss/qmss_qos.h"



#include <ti/csl/cslr_cp_ace.h>
#include <ti/csl/cslr_cp_timer16.h>
#include <ti/csl/cslr_cp_tracer.h>
#include <ti/csl/cslr_cpgmac_sl.h>
#include <ti/csl/cslr_cpintc.h>
#include <ti/csl/cslr_cppidma_global_config.h>
#include <ti/csl/cslr_cppidma_rx_channel_config.h>
#include <ti/csl/cslr_cppidma_rx_flow_config.h>
#include <ti/csl/cslr_cppidma_tx_channel_config.h>
#include <ti/csl/cslr_cppidma_tx_scheduler_config.h>
#include <ti/csl/cslr_cpsgmii.h>
#include <ti/csl/cslr_cpsw_3gf.h>
#include <ti/csl/cslr_cpsw_3gfss_s.h>
#include <ti/csl/cslr_cpts.h>
#include <ti/csl/cslr_device.h>
#include <ti/csl/cslr_emif4f.h>
#include <ti/csl/cslr_emif16.h>
#include <ti/csl/cslr_gpio.h>
#include <ti/csl/cslr_i2c.h>
#include <ti/csl/cslr_ipc.h>
#include <ti/csl/cslr_mcdma.h>
#include <ti/csl/cslr_mdio.h>
#include <ti/csl/cslr_mpu.h>
#include <ti/csl/cslr_msmc.h>
#include <ti/csl/cslr_pa_ss.h>
#include <ti/csl/cslr_pcie_cfg_space_endpoint.h>
#include <ti/csl/cslr_pcie_cfg_space_rootcomplex.h>
#include <ti/csl/cslr_pciess_app.h>
#include <ti/csl/cslr_pciess_cfgtype0.h>
#include <ti/csl/cslr_pciess_cfgtype1.h>
#include <ti/csl/cslr_pdsp.h>
#include <ti/csl/cslr_pllc.h>
#include <ti/csl/cslr_psc.h>
#include <ti/csl/cslr_qm_config.h>
#include <ti/csl/cslr_qm_descriptor_region_config.h>
#include <ti/csl/cslr_qm_intd.h>
#include <ti/csl/cslr_qm_qos_pdsp.h>
#include <ti/csl/cslr_qm_queue_management.h>
#include <ti/csl/cslr_qm_queue_status_config.h>
#include <ti/csl/cslr_sem.h>
#include <ti/csl/cslr_spi.h>
#include <ti/csl/cslr_srio.h>
#include <ti/csl/cslr_tmr.h>
#include <ti/csl/cslr_tpcc.h>
#include <ti/csl/cslr_tptc.h>
#include <ti/csl/cslr_tsip.h>
#include <ti/csl/cslr_uart.h>
#include <ti/csl/cslr_vusr.h>
#include <ti/csl/cslr_xmc.h>
#include <ti/csl/cslver.h>
#include <ti/csl/cslr_chip.h>
#include <ti/csl/cslr_bootcfg.h>
#include <ti/csl/cslr_cgem.h>
#include <ti/csl/cslr_gpio.h>
#include <ti/csl/cslr_i2c.h>
#include <ti/csl/cslr_pllc.h>
#include <ti/csl/cslr_srio.h>

#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_chipAux.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/csl_cache.h>
#include <ti/csl/csl_bootcfg.h>
#include <ti/csl/csl_bootcfgAux.h>
#include <ti/csl/csl_cgem.h>
#include <ti/csl/csl_cgemAux.h>
#include <ti/csl/csl_cpgmac_sl.h>
#include <ti/csl/csl_cpgmac_slAux.h>
#include <ti/csl/csl_cppi.h>
#include <ti/csl/csl_cpsgmii.h>
#include <ti/csl/csl_cpsgmiiAux.h>
#include <ti/csl/csl_cpsw.h>
#include <ti/csl/csl_cpsw_3gf.h>
#include <ti/csl/csl_cpsw_3gfAux.h>
#include <ti/csl/csl_cpsw_3gfss_s.h>
#include <ti/csl/csl_cpsw_3gfssAux.h>
#include <ti/csl/csl_cpts.h>
#include <ti/csl/csl_cptsAux.h>
#include <ti/csl/csl_cpIntc.h>
#include <ti/csl/csl_cpIntcAux.h>
#include <ti/csl/csl_idma.h>
#include <ti/csl/csl_idmaAux.h>
#include <ti/csl/csl_ipc.h>
#include <ti/csl/csl_ipcAux.h>
#include <ti/csl/csl_mdio.h>
#include <ti/csl/csl_mdioAux.h>
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>
#include <ti/csl/csl_qm_queue.h>
#include <ti/csl/csl_sem.h>
#include <ti/csl/csl_semAux.h>
#include <ti/csl/csl_idma.h>
#include <ti/csl/csl_memprot.h>
#include <ti/csl/csl_memprotAux.h>
#include <ti/csl/csl_msmc.h>
#include <ti/csl/csl_msmcAux.h>
#include <ti/csl/csl_mpu.h>
#include <ti/csl/csl_mpuAux.h>
#include <ti/csl/csl_edma3.h>
#include <ti/csl/csl_edma3Aux.h>
#include <ti/csl/csl_emif4f.h>
#include <ti/csl/csl_emif4fAux.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/csl_gpioAux.h>
#include <ti/csl/csl_memprot.h>
#include <ti/csl/csl_memprotAux.h>
#include <ti/csl/csl_pllc.h>
#include <ti/csl/csl_pllcAux.h>
#include <ti/csl/csl_srio.h>
#include <ti/csl/csl_srioAux.h>
#include <ti/csl/csl_srioAuxPhyLayer.h>
#include <ti/csl/csl_tmr.h>
#include <ti/csl/csl_tmrAux.h>
#include <ti/csl/csl_bwmngmt.h>
#include <ti/csl/csl_bwmngmtAux.h>
#include <ti/csl/cslr_mdio.h>
#include <ti/csl/csl_tsc.h>
#include <ti/csl/csl_tsip.h>
#include <ti/csl/csl_tsipAux.h>
#include <ti/csl/csl_xmc.h>
#include <ti/csl/csl_xmcAux.h>
#include <ti/csl/cslr_tmr.h>


#include "bootCfg_dsp667x.h"
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__DSP667X_H__*/

