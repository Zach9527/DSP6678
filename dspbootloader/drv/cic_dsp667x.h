/*
 文件名称：cic_dsp6678.h
摘要：
*/
/* 修改历史:

2016.3.12,chengqb创建文件
*/

#ifndef __CIC_DSP6678__
#define __CIC_DSP6678__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/
#include"common.h"

/*defines*/
#define CIC_EVENT_TOTAL_NUM		256		 /*CIC事件总数*/

#define CIC0_EDMA3CC1_CC_ERRINT 									(0 	)																				
#define CIC0_EDMA3CC1_CC_MPINT 										(1 	)																				
#define CIC0_EDMA3CC1_TC_ERRINT0 									(2 	)																				
#define CIC0_EDMA3CC1_TC_ERRINT1 									(3 	)																				
#define CIC0_EDMA3CC1_TC_ERRINT2 									(4 	)																				
#define CIC0_EDMA3CC1_TC_ERRINT3 									(5 	)																				
#define CIC0_EDMA3CC1_CC_GINT										(6 	)																				
#define CIC0_RSV0 													(7 	)																				
#define CIC0_EDMA3CC1_CCINT0 										(8 	)																				
#define CIC0_EDMA3CC1_CCINT1 										(9 	)																				
#define CIC0_EDMA3CC1_CCINT2 										(10 )																				
#define CIC0_EDMA3CC1_CCINT3 										(11 )																				
#define CIC0_EDMA3CC1_CCINT4 										(12 )																				
#define CIC0_EDMA3CC1_CCINT5 										(13 )																				
#define CIC0_EDMA3CC1_CCINT6 										(14 )																				
#define CIC0_EDMA3CC1_CCINT7 										(15 )																				
#define CIC0_EDMA3CC2_ERRINT 										(16 )																				
#define CIC0_EDMA3CC2_MPINT 										(17 )																				
#define CIC0_EDMA3CC2_ERRINT0 										(18 )																				
#define CIC0_EDMA3CC2_ERRINT1 										(19 )																				
#define CIC0_EDMA3CC2_ERRINT2 										(20 )																				
#define CIC0_EDMA3CC2_ERRINT3										(21 )																				
#define CIC0_EDMA3CC2_GINT 										(22 )																				
#define CIC0_RSV1										(23 )																				
#define CIC0_EDMA3CC2_CCINT0 										(24 )																				
#define CIC0_EDMA3CC2_CCINT1 										(25 )																				
#define CIC0_EDMA3CC2_CCINT2 										(26 )																				
#define CIC0_EDMA3CC2_CCINT3 										(27 )																				
#define CIC0_EDMA3CC2_CCINT4 										(28 )																				
#define CIC0_EDMA3CC2_CCINT5 										(29 )																				
#define CIC0_EDMA3CC2_CCINT6 										(30 )																				
#define CIC0_EDMA3CC2_CCINT7 										(31 )																				
#define CIC0_EDMA3CC0_ERRINT 										(32 )																				
#define CIC0_EDMA3CC0_MPINT 										(33 )																				
#define CIC0_EDMA3CC0_ERRINT0 										(34 )																				
#define CIC0_EDMA3CC0_ERRINT1 										(35 )																				
#define CIC0_EDMA3CC0_GINT 										(36 )																				
#define CIC0_RSV2 										(37 )																				
#define CIC0_EDMA3CC0_CCINT0 										(38 )																				
#define CIC0_EDMA3CC0_CCINT1 										(39 )																				
#define CIC0_EDMA3CC0_CCINT2 										(40 )																				
#define CIC0_EDMA3CC0_CCINT3 										(41 )																				
#define CIC0_EDMA3CC0_CCINT4 										(42 )																				
#define CIC0_EDMA3CC0_CCINT5 										(43 )																				
#define CIC0_EDMA3CC0_CCINT6 										(44 )																				
#define CIC0_EDMA3CC0_CCINT7 										(45 )																				
#define CIC0_RSV3                     (46 )																				                               
#define CIC0_QM_INT_PASS_TXQ_PEND_12 			(47 )																				      
#define CIC0_PCIEXPRESS_ERR_INT 					(48 )																				      
#define CIC0_PCIEXPRESS_PM_INT 						(49 )																				    
#define CIC0_PCIEXPRESS_LEGACY_INTA 			(50 )																				         
#define CIC0_PCIEXPRESS_LEGACY_INTB 			(51 )																				         
#define CIC0_PCIEXPRESS_LEGACY_INTC 			(52 )																				         
#define CIC0_PCIEXPRESS_LEGACY_INTD 			(53 )																				         
#define CIC0_SPIINT0 											(54 )																				              
#define CIC0_SPIINT1 											(55 )																				              
#define CIC0_SPIXEVT 											(56 )																				            
#define CIC0_SPIREVT 											(57 )																				            
#define CIC0_I2CINT 											(58 )																				          
#define CIC0_I2CREVT 											(59 )																				            
#define CIC0_I2CXEVT 											(60 )																				            
#define CIC0_RSV4                     (61 )																				                               
#define CIC0_RSV5                     (62 )																				                               
#define CIC0_TETBHFULLINT 								(63 )																				        
#define CIC0_TETBFULLINT 									(64 )																				        
#define CIC0_TETBACQINT 									(65 )																				
#define CIC0_TETBOVFLINT 									(66 )																				
#define CIC0_TETBUNFLINT 									(67 )																				   
#define CIC0_MDIO_LINK_INTR0 							(68 )																				
#define CIC0_MDIO_LINK_INTR1 							(69 )																				
#define CIC0_MDIO_USER_INTR0 							(70 )																				
#define CIC0_MDIO_USER_INTR1 							(71 )																				
#define CIC0_MISC_INTR										(72 )																				
#define CIC0_TRACER_CORE_0_INTD 					(73 )																				
#define CIC0_TRACER_CORE_1_INTD 					(74 )																				
#define CIC0_TRACER_CORE_2_INTD 					(75 )																				
#define CIC0_TRACER_CORE_3_INTD 					(76 )																				
#define CIC0_TRACER_DDR_INTD 							(77 )																				
#define CIC0_TRACER_MSMC_0_INTD 					(78 )																				
#define CIC0_TRACER_MSMC_1_INTD 					(79 )																				
#define CIC0_TRACER_MSMC_2_INTD 					(80 )																				
#define CIC0_TRACER_MSMC_3_INTD 					(81 )																				
#define CIC0_TRACER_CFG_INTD 							(81 )																				
#define CIC0_TRACER_QM_SS_CFG_INTD 				(82 )																				
#define CIC0_TRACER_QM_SS_DMA_INTD 				(84 )																				
#define CIC0_TRACER_SEM_INTD 							(85 )																				
#define CIC0_PSC_ALLINT 									(86 )																				
#define CIC0_MSMC_SCRUB_									(87 )																				
#define CIC0_BOOTCFG_INTD 								(88 )																				
#define CIC0_PO_VCON_SMPSERR_INTR 				(89 )																				
#define CIC0_MPU0_INTD 										(90 )																				
#define CIC0_QM_INT_PASS_TXQ_PEND_13 			(91 )																				            
#define CIC0_MPU1_INTD 										(92 )																				             
#define CIC0_QM_INT_PASS_TXQ_PEND_14 			(93 )																				           
#define CIC0_MPU2_INTD 										(94 )																				               
#define CIC0_QM_INT_PASS_TXQ_PEND_15 			(95 )																				        
#define CIC0_MPU3_INTD 										(96 )																				           
#define CIC0_QM_INT_PASS_TXQ_PEND_16 			(97 )																				          
#define CIC0_MSMC_DEDC_CERROR 						(98 )																				
#define CIC0_MSMC_DEDC_NC_ERROR 					(99 )																				
#define CIC0_MSMC_SCRUB_NC_ERROR 					(100)																				
#define CIC0_RSV6                     (101)																				                                      
#define CIC0_MSMC_MPF_ERROR8 							(102)																				
#define CIC0_MSMC_MPF_ERROR9 							(103)																				
#define CIC0_MSMC_MPF_ERROR10 						(104)																				
#define CIC0_MSMC_MPF_ERROR11 						(105)																				
#define CIC0_MSMC_MPF_ERROR12 						(105)																				
#define CIC0_MSMC_MPF_ERROR13 						(107)																				
#define CIC0_MSMC_MPF_ERROR14 						(108)																				
#define CIC0_MSMC_MPF_ERROR15 						(109)																				
#define CIC0_DDR3_ERR 										(110)																				             
#define CIC0_VUSR_INT_O 									(111)																				             
#define CIC0_INTDST0 											(112)																				                  
#define CIC0_INTDST1 											(113)																				                  
#define CIC0_INTDST2 											(114)																				                  
#define CIC0_INTDST3 											(115)																				                  
#define CIC0_INTDST4 											(116)																				                  
#define CIC0_INTDST5 											(117)																				                  
#define CIC0_INTDST6 											(118)																				                  
#define CIC0_INTDST7 											(119)																				                  
#define CIC0_INTDST8 											(120)																				                  
#define CIC0_INTDST9 											(121)																				
#define CIC0_INTDST10 										(122)																				                        
#define CIC0_INTDST11 										(123)																				                        
#define CIC0_INTDST12 										(124)																				                        
#define CIC0_INTDST13 										(125)																				                        
#define CIC0_INTDST14 										(126)																				                        
#define CIC0_INTDST15 										(127)																				                        
#define CIC0_EASYNCERR 										(128)																				                    
#define CIC0_TRACER_CORE_4_INTD 					(129)																				
#define CIC0_TRACER_CORE_5_INTD 					(130)																				
#define CIC0_TRACER_CORE_6_INTD 					(131)																				
#define CIC0_TRACER_CORE_7_INTD 					(132)																				
#define CIC0_QM_INT_PKTDMA_0 							(133)																				
#define CIC0_QM_INT_PKTDMA_1 							(134)																				
#define CIC0_RAPIDIO_INT_PKTDMA_0 				(135)																				
#define CIC0_PASS_INT_PKTDMA_0 						(136)																				
#define CIC0_SMARTREFLEX_INTRREQ0 				(137)																				           
#define CIC0_SMARTREFLEX_INTRREQ1 				(138)																				           
#define CIC0_SMARTREFLEX_INTRREQ2 				(139)																				           
#define CIC0_SMARTREFLEX_INTRREQ3 				(140)																				
#define CIC0_VPNOSMPSACK 									(141)																				
#define CIC0_VPEQVALUE 										(142)																				
#define CIC0_VPMAXVDD 										(143)																				
#define CIC0_VPMINVDD 										(144)																				
#define CIC0_VPINIDLE 										(145)																				
#define CIC0_VPOPPCHANGEDONE 							(146)																				
#define CIC0_RSV7                     (147)																				                                            
#define CIC0_UARTINT 											(148)																				                  
#define CIC0_URXEVT 											(149)																				                  
#define CIC0_UTXEVT 											(150)																				                    
#define CIC0_QM_INT_PASS_TXQ_PEND_17 			(151)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_18 			(152)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_19 			(153)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_20 			(154)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_21 			(155)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_22 			(156)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_23 			(157)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_24 			(158)																				                  
#define CIC0_QM_INT_PASS_TXQ_PEND_25 			(159)			



#define CIC1_EDMA3CC1_CC_ERRINT 										(0 	)																				
#define CIC1_EDMA3CC1_CC_MPINT 										(1 	)																				
#define CIC1_EDMA3CC1_TC_ERRINT0 										(2 	)																				
#define CIC1_EDMA3CC1_TC_ERRINT1 										(3 	)																				
#define CIC1_EDMA3CC1_TC_ERRINT2 										(4 	)																				
#define CIC1_EDMA3CC1_TC_ERRINT3 										(5 	)																				
#define CIC1_EDMA3CC1_CC_GINT										(6 	)																				
#define CIC1_RSV0 										(7 	)																				
#define CIC1_EDMA3CC1_CCINT0 										(8 	)																				
#define CIC1_EDMA3CC1_CCINT1 										(9 	)																				
#define CIC1_EDMA3CC1_CCINT2 										(10 )																				
#define CIC1_EDMA3CC1_CCINT3 										(11 )																				
#define CIC1_EDMA3CC1_CCINT4 										(12 )																				
#define CIC1_EDMA3CC1_CCINT5 										(13 )																				
#define CIC1_EDMA3CC1_CCINT6 										(14 )																				
#define CIC1_EDMA3CC1_CCINT7 										(15 )																				
#define CIC1_EDMA3CC2_ERRINT 										(16 )																				
#define CIC1_EDMA3CC2_MPINT 										(17 )																				
#define CIC1_EDMA3CC2_ERRINT0 										(18 )																				
#define CIC1_EDMA3CC2_ERRINT1 										(19 )																				
#define CIC1_EDMA3CC2_ERRINT2 										(20 )																				
#define CIC1_EDMA3CC2_ERRINT3										(21 )																				
#define CIC1_EDMA3CC2_GINT 										(22 )																				
#define CIC1_RSV1										(23 )																				
#define CIC1_EDMA3CC2_CCINT0 										(24 )																				
#define CIC1_EDMA3CC2_CCINT1 										(25 )																				
#define CIC1_EDMA3CC2_CCINT2 										(26 )																				
#define CIC1_EDMA3CC2_CCINT3 										(27 )																				
#define CIC1_EDMA3CC2_CCINT4 										(28 )																				
#define CIC1_EDMA3CC2_CCINT5 										(29 )																				
#define CIC1_EDMA3CC2_CCINT6 										(30 )																				
#define CIC1_EDMA3CC2_CCINT7 										(31 )																				
#define CIC1_EDMA3CC0_ERRINT 										(32 )																				
#define CIC1_EDMA3CC0_MPINT 										(33 )																				
#define CIC1_EDMA3CC0_ERRINT0 										(34 )																				
#define CIC1_EDMA3CC0_ERRINT1 										(35 )																				
#define CIC1_EDMA3CC0_GINT 										(36 )																				
#define CIC1_RSV2 										(37 )																				
#define CIC1_EDMA3CC0_CCINT0 										(38 )																				
#define CIC1_EDMA3CC0_CCINT1 										(39 )																				
#define CIC1_EDMA3CC0_CCINT2 										(40 )																				
#define CIC1_EDMA3CC0_CCINT3 										(41 )																				
#define CIC1_EDMA3CC0_CCINT4 										(42 )																				
#define CIC1_EDMA3CC0_CCINT5 										(43 )																				
#define CIC1_EDMA3CC0_CCINT6 										(44 )																				
#define CIC1_EDMA3CC0_CCINT7 										(45 )	          
#define CIC1_RSV3                        (46 )            
#define CIC1_QM_INT_PASS_TXQ_PEND_18         (47 )            
#define CIC1_PCIEXPRESS_ERR_INT              (48 )            
#define CIC1_PCIEXPRESS_PM_INT               (49 )            
#define CIC1_PCIEXPRESS_LEGACY_INTA          (50 )            
#define CIC1_PCIEXPRESS_LEGACY_INTB          (51 )            
#define CIC1_PCIEXPRESS_LEGACY_INTC          (52 )            
#define CIC1_PCIEXPRESS_LEGACY_INTD          (53 )            
#define CIC1_SPIINT0                         (54 )            
#define CIC1_SPIINT1                         (55 )            
#define CIC1_SPIXEVT                         (56 )            
#define CIC1_SPIREVT                         (57 )            
#define CIC1_I2CINT                          (58 )            
#define CIC1_I2CREVT                         (59 )            
#define CIC1_I2CXEVT                         (60 )            
#define CIC1_RSV4                        (61 )            
#define CIC1_RSV5                        (62 )            
#define CIC1_TETBHFULLINT                    (63 )            
#define CIC1_TETBFULLINT                     (64 )            
#define CIC1_TETBACQINT                      (65 )            
#define CIC1_TETBOVFLINT                     (66 )            
#define CIC1_TETBUNFLINT                     (67 )            
#define CIC1_MDIO_LINK_INTR0                 (68 )            
#define CIC1_MDIO_LINK_INTR1                 (69 )            
#define CIC1_MDIO_USER_INTR0                 (70 )            
#define CIC1_MDIO_USER_INTR1                 (71 )            
#define CIC1_MISC_INTR                       (72 )            
#define CIC1_TRACER_CORE_0_INTD              (73 )            
#define CIC1_TRACER_CORE_1_INTD              (74 )            
#define CIC1_TRACER_CORE_2_INTD              (75 )            
#define CIC1_TRACER_CORE_3_INTD              (76 )            
#define CIC1_TRACER_DDR_INTD                 (77 )            
#define CIC1_TRACER_MSMC_0_INTD              (78 )            
#define CIC1_TRACER_MSMC_1_INTD              (79 )            
#define CIC1_TRACER_MSMC_2_INTD              (80 )            
#define CIC1_TRACER_MSMC_3_INTD              (81 )            
#define CIC1_TRACER_CFG_INTD                 (81 )            
#define CIC1_TRACER_QM_SS_CFG_INTD 			    (82 )             
#define CIC1_TRACER_QM_SS_DMA_INTD 			    (84 )             
#define CIC1_TRACER_SEM_INTD 						    (85 )             
#define CIC1_PSC_ALLINT 								      (86 )           
#define CIC1_MSMC_SCRUB_CERROR 					    (87 )             
#define CIC1_BOOTCFG_INTD BOOTCFG 			      (88 )           
#define CIC1_PO_VCON_SMPSERR_INTR 			      (89 )           
#define CIC1_MPU0_INTD 									    (90 )             
#define CIC1_QM_INT_PASS_TXQ_PEND_19         (91 )            
#define CIC1_MPU1_INTD                       (92 )            
#define CIC1_QM_INT_PASS_TXQ_PEND_20         (93 )            
#define CIC1_MPU2_INTD                       (94 )            
#define CIC1_QM_INT_PASS_TXQ_PEND_21         (95 )            
#define CIC1_MPU3_INTD                       (96 )            
#define CIC1_QM_INT_PASS_TXQ_PEND_22         (97 )            
#define CIC1_MSMC_DEDC_CERROR                (98 )            
#define CIC1_MSMC_DEDC_NC_ERROR              (99 )            
#define CIC1_MSMC_SCRUB_NC_ERRORE            (100)            
#define CIC1_RSV6                        (101)            
#define CIC1_MSMC_MPF_ERROR8 	              (102)             
#define CIC1_MSMC_MPF_ERROR9 	              (103)             
#define CIC1_MSMC_MPF_ERROR10 	              (104)           
#define CIC1_MSMC_MPF_ERROR11 	              (105)           
#define CIC1_MSMC_MPF_ERROR12 	              (105)           
#define CIC1_MSMC_MPF_ERROR13 	              (107)           
#define CIC1_MSMC_MPF_ERROR14 	              (108)           
#define CIC1_MSMC_MPF_ERROR15 	              (109)           
#define CIC1_DDR3_ERR                   (110)            
#define CIC1_VUSR_INT_O                      (111)            
#define CIC1_INTDST0                         (112)            
#define CIC1_INTDST1                         (113)            
#define CIC1_INTDST2                         (114)            
#define CIC1_INTDST3                         (115)            
#define CIC1_INTDST4                         (116)            
#define CIC1_INTDST5                         (117)            
#define CIC1_INTDST6                         (118)            
#define CIC1_INTDST7                         (119)            
#define CIC1_INTDST8                         (120)            
#define CIC1_INTDST9                         (121)            
#define CIC1_INTDST10                        (122)            
#define CIC1_INTDST11                        (123)            
#define CIC1_INTDST12                        (124)            
#define CIC1_INTDST13                        (125)            
#define CIC1_INTDST14                        (126)            
#define CIC1_INTDST15                        (127)            
#define CIC1_EASYNCERR                       (128)            
#define CIC1_TRACER_CORE_4_INTD              (129)            
#define CIC1_TRACER_CORE_5_INTD              (130)            
#define CIC1_TRACER_CORE_6_INTD              (131)            
#define CIC1_TRACER_CORE_7_INTD              (132)            
#define CIC1_QM_INT_PKTDMA_0                 (133)            
#define CIC1_QM_INT_PKTDMA_1                 (134)            
#define CIC1_RAPIDIO_INT_PKTDMA_0            (135)            
#define CIC1_PASS_INT_PKTDMA_0               (136)            
#define CIC1_SMARTREFLEX_INTRREQ0            (137)            
#define CIC1_SMARTREFLEX_INTRREQ1            (138)            
#define CIC1_SMARTREFLEX_INTRREQ2            (139)            
#define CIC1_SMARTREFLEX                     (140)            
#define CIC1_VPNOSMPSACK                     (141)            
#define CIC1_VPEQVALUE                       (142)            
#define CIC1_VPMAXVDD                        (143)            
#define CIC1_VPMINVDD                        (144)            
#define CIC1_VPINIDLE                        (145)            
#define CIC1_VPOPPCHANGEDONE                 (146)            
#define CIC1_RSV7                        (147)            
#define CIC1_UARTINT                         (148)            
#define CIC1_URXEVT                          (149)            
#define CIC1_UTXEVT                          (150)            
#define CIC1_QM_INT_PASS_TXQ_PEND_23         (151)            
#define CIC1_QM_INT_PASS_TXQ_PEND_24         (152)            
#define CIC1_QM_INT_PASS_TXQ_PEND_25         (153)            
#define CIC1_QM_INT_PASS_TXQ_PEND_26         (154)            
#define CIC1_QM_INT_PASS_TXQ_PEND_27         (155)            
#define CIC1_QM_INT_PASS_TXQ_PEND_28         (156)            
#define CIC1_QM_INT_PASS_TXQ_PEND_29         (157)            
#define CIC1_QM_INT_PASS_TXQ_PEND_30         (158)            
#define CIC1_QM_INT_PASS_TXQ_PEND_31         (159)            

#define CIC_MAX_NUM				(1)			//4
#define CORE_MAX_NUM			(8)
#define CHANNEL_MAX_NUM			(1)		//256
#define CHANNEL_MAX_SYSTENID	(1)		//256


/*typedef*/
typedef struct  cic_reg{
    VOLATILE UINT32 revision_reg;				/*Revision Register*/
    VOLATILE UINT32 control_reg;				/*Control Register*/
    VOLATILE UINT8  rsvd0[4];
    VOLATILE UINT32 host_control_reg;
    VOLATILE UINT32 global_enable_hint_reg;	/*Global Enable Register*/
    VOLATILE UINT8  rsvd1[8];
    VOLATILE UINT32 glb_nest_level_reg;		
    VOLATILE UINT32 status_set_index_reg;		/*System Interrupt Status Indexed Set Register*/
    VOLATILE UINT32 status_clr_index_reg;		/*System Interrupt Status Indexed Clear Register*/
    VOLATILE UINT32 enable_set_index_reg;		/*System Interrupt Enable Indexed Set Register*/
    VOLATILE UINT32 enable_clr_index_reg;		/*System Interrupt Enable Indexed Clear Register*/
    VOLATILE UINT8  rsvd2[4];
    VOLATILE UINT32 hint_enable_set_index_reg;	/*Host Interrupt Enable Indexed Set Register*/
    VOLATILE UINT32 hint_enable_clr_index_reg; /*Host Interrupt Enable Indexed Clear Register*/
    VOLATILE UINT8  rsvd3[28];
    VOLATILE UINT32 vector_null_reg;			
    VOLATILE UINT8  rsvd4[36];
    VOLATILE UINT32 glb_pri_intr_reg;			/*Global Prioritized index Register*/
    VOLATILE UINT32 glb_vector_addr_reg;
    VOLATILE UINT8  rsvd5[8];
    VOLATILE UINT32 global_secure_enable_reg;
    VOLATILE UINT32 secure_pri_intr_reg;
    VOLATILE UINT8  rsvd6[360];
#ifdef CSL_MODIFICATION
    VOLATILE UINT32 raw_status_reg0;
    VOLATILE UINT32 raw_status_reg1;
    VOLATILE UINT32 raw_status_reg2;
    VOLATILE UINT32 raw_status_reg3;
    VOLATILE UINT32 raw_status_reg4;
    VOLATILE UINT32 raw_status_reg5;
    VOLATILE UINT32 raw_status_reg6;
    VOLATILE UINT32 raw_status_reg7;
    VOLATILE UINT32 raw_status_reg8;
    VOLATILE UINT32 raw_status_reg9;
    VOLATILE UINT32 raw_status_reg10;
    VOLATILE UINT32 raw_status_reg11;
    VOLATILE UINT32 raw_status_reg12;
    VOLATILE UINT32 raw_status_reg13;
    VOLATILE UINT32 raw_status_reg14;
    VOLATILE UINT32 raw_status_reg15;
    VOLATILE UINT32 raw_status_reg16;
    VOLATILE UINT32 raw_status_reg17;
    VOLATILE UINT32 raw_status_reg18;
    VOLATILE UINT32 raw_status_reg19;
    VOLATILE UINT32 raw_status_reg20;
    VOLATILE UINT32 raw_status_reg21;
    VOLATILE UINT32 raw_status_reg22;
    VOLATILE UINT32 raw_status_reg23;
    VOLATILE UINT32 raw_status_reg24;
    VOLATILE UINT32 raw_status_reg25;
    VOLATILE UINT32 raw_status_reg26;
    VOLATILE UINT32 raw_status_reg27;
    VOLATILE UINT32 raw_status_reg28;
    VOLATILE UINT32 raw_status_reg29;
    VOLATILE UINT32 raw_status_reg30;
    VOLATILE UINT32 raw_status_reg31;
#else
    VOLATILE UINT32 raw_status_reg[32];	/*System Interrupt Status Raw/Set Registers*/
#endif
#ifdef CSL_MODIFICATION    
    VOLATILE UINT32 ena_status_reg0;
    VOLATILE UINT32 ena_status_reg1;
    VOLATILE UINT32 ena_status_reg2;
    VOLATILE UINT32 ena_status_reg3;
    VOLATILE UINT32 ena_status_reg4;
    VOLATILE UINT32 ena_status_reg5;
    VOLATILE UINT32 ena_status_reg6;
    VOLATILE UINT32 ena_status_reg7;
    VOLATILE UINT32 ena_status_reg8;
    VOLATILE UINT32 ena_status_reg9;
    VOLATILE UINT32 ena_status_reg10;
    VOLATILE UINT32 ena_status_reg11;
    VOLATILE UINT32 ena_status_reg12;
    VOLATILE UINT32 ena_status_reg13;
    VOLATILE UINT32 ena_status_reg14;
    VOLATILE UINT32 ena_status_reg15;
    VOLATILE UINT32 ena_status_reg16;
    VOLATILE UINT32 ena_status_reg17;
    VOLATILE UINT32 ena_status_reg18;
    VOLATILE UINT32 ena_status_reg19;
    VOLATILE UINT32 ena_status_reg20;
    VOLATILE UINT32 ena_status_reg21;
    VOLATILE UINT32 ena_status_reg22;
    VOLATILE UINT32 ena_status_reg23;
    VOLATILE UINT32 ena_status_reg24;
    VOLATILE UINT32 ena_status_reg25;
    VOLATILE UINT32 ena_status_reg26;
    VOLATILE UINT32 ena_status_reg27;
    VOLATILE UINT32 ena_status_reg28;
    VOLATILE UINT32 ena_status_reg29;
    VOLATILE UINT32 ena_status_reg30;
    VOLATILE UINT32 ena_status_reg31;
#else
    VOLATILE UINT32 ena_status_reg[32];	/*System Interrupt Status Enabled/Clear Registers*/
#endif
#ifdef CSL_MODIFICATION    
    VOLATILE UINT32 enable_reg0;
    VOLATILE UINT32 enable_reg1;
    VOLATILE UINT32 enable_reg2;
    VOLATILE UINT32 enable_reg3;
    VOLATILE UINT32 enable_reg4;
    VOLATILE UINT32 enable_reg5;
    VOLATILE UINT32 enable_reg6;
    VOLATILE UINT32 enable_reg7;
    VOLATILE UINT32 enable_reg8;
    VOLATILE UINT32 enable_reg9;
    VOLATILE UINT32 enable_reg10;
    VOLATILE UINT32 enable_reg11;
    VOLATILE UINT32 enable_reg12;
    VOLATILE UINT32 enable_reg13;
    VOLATILE UINT32 enable_reg14;
    VOLATILE UINT32 enable_reg15;
    VOLATILE UINT32 enable_reg16;
    VOLATILE UINT32 enable_reg17;
    VOLATILE UINT32 enable_reg18;
    VOLATILE UINT32 enable_reg19;
    VOLATILE UINT32 enable_reg20;
    VOLATILE UINT32 enable_reg21;
    VOLATILE UINT32 enable_reg22;
    VOLATILE UINT32 enable_reg23;
    VOLATILE UINT32 enable_reg24;
    VOLATILE UINT32 enable_reg25;
    VOLATILE UINT32 enable_reg26;
    VOLATILE UINT32 enable_reg27;
    VOLATILE UINT32 enable_reg28;
    VOLATILE UINT32 enable_reg29;
    VOLATILE UINT32 enable_reg30;
    VOLATILE UINT32 enable_reg31;
#else
    VOLATILE UINT32 enable_reg[32];	/*System Interrupt Status Enable Set Registers*/
#endif
#ifdef CSL_MODIFICATION 
    VOLATILE UINT32 enable_clr_reg0;
    VOLATILE UINT32 enable_clr_reg1;
    VOLATILE UINT32 enable_clr_reg2;
    VOLATILE UINT32 enable_clr_reg3;
    VOLATILE UINT32 enable_clr_reg4;
    VOLATILE UINT32 enable_clr_reg5;
    VOLATILE UINT32 enable_clr_reg6;
    VOLATILE UINT32 enable_clr_reg7;
    VOLATILE UINT32 enable_clr_reg8;
    VOLATILE UINT32 enable_clr_reg9;
    VOLATILE UINT32 enable_clr_reg10;
    VOLATILE UINT32 enable_clr_reg11;
    VOLATILE UINT32 enable_clr_reg12;
    VOLATILE UINT32 enable_clr_reg13;
    VOLATILE UINT32 enable_clr_reg14;
    VOLATILE UINT32 enable_clr_reg15;
    VOLATILE UINT32 enable_clr_reg16;
    VOLATILE UINT32 enable_clr_reg17;
    VOLATILE UINT32 enable_clr_reg18;
    VOLATILE UINT32 enable_clr_reg19;
    VOLATILE UINT32 enable_clr_reg20;
    VOLATILE UINT32 enable_clr_reg21;
    VOLATILE UINT32 enable_clr_reg22;
    VOLATILE UINT32 enable_clr_reg23;
    VOLATILE UINT32 enable_clr_reg24;
    VOLATILE UINT32 enable_clr_reg25;
    VOLATILE UINT32 enable_clr_reg26;
    VOLATILE UINT32 enable_clr_reg27;
    VOLATILE UINT32 enable_clr_reg28;
    VOLATILE UINT32 enable_clr_reg29;
    VOLATILE UINT32 enable_clr_reg30;
    VOLATILE UINT32 enable_clr_reg31;
#else
    VOLATILE UINT32 enable_clr_reg[32];		/*System Interrupt Status Enable Clear Registers*/
#endif    
#ifdef CSL_MODIFICATION
    VOLATILE UINT32 ch_map_reg0;
    VOLATILE UINT32 ch_map_reg1;
    VOLATILE UINT32 ch_map_reg2;
    VOLATILE UINT32 ch_map_reg3;
    VOLATILE UINT32 ch_map_reg4;
    VOLATILE UINT32 ch_map_reg5;
    VOLATILE UINT32 ch_map_reg6;
    VOLATILE UINT32 ch_map_reg7;
    VOLATILE UINT32 ch_map_reg8;
    VOLATILE UINT32 ch_map_reg9;
    VOLATILE UINT32 ch_map_reg10;
    VOLATILE UINT32 ch_map_reg11;
    VOLATILE UINT32 ch_map_reg12;
    VOLATILE UINT32 ch_map_reg13;
    VOLATILE UINT32 ch_map_reg14;
    VOLATILE UINT32 ch_map_reg15;
    VOLATILE UINT32 ch_map_reg16;
    VOLATILE UINT32 ch_map_reg17;
    VOLATILE UINT32 ch_map_reg18;
    VOLATILE UINT32 ch_map_reg19;
    VOLATILE UINT32 ch_map_reg20;
    VOLATILE UINT32 ch_map_reg21;
    VOLATILE UINT32 ch_map_reg22;
    VOLATILE UINT32 ch_map_reg23;
    VOLATILE UINT32 ch_map_reg24;
    VOLATILE UINT32 ch_map_reg25;
    VOLATILE UINT32 ch_map_reg26;
    VOLATILE UINT32 ch_map_reg27;
    VOLATILE UINT32 ch_map_reg28;
    VOLATILE UINT32 ch_map_reg29;
    VOLATILE UINT32 ch_map_reg30;
    VOLATILE UINT32 ch_map_reg31;
    VOLATILE UINT32 ch_map_reg32;
    VOLATILE UINT32 ch_map_reg33;
    VOLATILE UINT32 ch_map_reg34;
    VOLATILE UINT32 ch_map_reg35;
    VOLATILE UINT32 ch_map_reg36;
    VOLATILE UINT32 ch_map_reg37;
    VOLATILE UINT32 ch_map_reg38;
    VOLATILE UINT32 ch_map_reg39;
    VOLATILE UINT32 ch_map_reg40;
    VOLATILE UINT32 ch_map_reg41;
    VOLATILE UINT32 ch_map_reg42;
    VOLATILE UINT32 ch_map_reg43;
    VOLATILE UINT32 ch_map_reg44;
    VOLATILE UINT32 ch_map_reg45;
    VOLATILE UINT32 ch_map_reg46;
    VOLATILE UINT32 ch_map_reg47;
    VOLATILE UINT32 ch_map_reg48;
    VOLATILE UINT32 ch_map_reg49;
    VOLATILE UINT32 ch_map_reg50;
    VOLATILE UINT32 ch_map_reg51;
    VOLATILE UINT32 ch_map_reg52;
    VOLATILE UINT32 ch_map_reg53;
    VOLATILE UINT32 ch_map_reg54;
    VOLATILE UINT32 ch_map_reg55;
    VOLATILE UINT32 ch_map_reg56;
    VOLATILE UINT32 ch_map_reg57;
    VOLATILE UINT32 ch_map_reg58;
    VOLATILE UINT32 ch_map_reg59;
    VOLATILE UINT32 ch_map_reg60;
    VOLATILE UINT32 ch_map_reg61;
    VOLATILE UINT32 ch_map_reg62;
    VOLATILE UINT32 ch_map_reg63;
    VOLATILE UINT32 ch_map_reg64;
    VOLATILE UINT32 ch_map_reg65;
    VOLATILE UINT32 ch_map_reg66;
    VOLATILE UINT32 ch_map_reg67;
    VOLATILE UINT32 ch_map_reg68;
    VOLATILE UINT32 ch_map_reg69;
    VOLATILE UINT32 ch_map_reg70;
    VOLATILE UINT32 ch_map_reg71;
    VOLATILE UINT32 ch_map_reg72;
    VOLATILE UINT32 ch_map_reg73;
    VOLATILE UINT32 ch_map_reg74;
    VOLATILE UINT32 ch_map_reg75;
    VOLATILE UINT32 ch_map_reg76;
    VOLATILE UINT32 ch_map_reg77;
    VOLATILE UINT32 ch_map_reg78;
    VOLATILE UINT32 ch_map_reg79;
    VOLATILE UINT32 ch_map_reg80;
    VOLATILE UINT32 ch_map_reg81;
    VOLATILE UINT32 ch_map_reg82;
    VOLATILE UINT32 ch_map_reg83;
    VOLATILE UINT32 ch_map_reg84;
    VOLATILE UINT32 ch_map_reg85;
    VOLATILE UINT32 ch_map_reg86;
    VOLATILE UINT32 ch_map_reg87;
    VOLATILE UINT32 ch_map_reg88;
    VOLATILE UINT32 ch_map_reg89;
    VOLATILE UINT32 ch_map_reg90;
    VOLATILE UINT32 ch_map_reg91;
    VOLATILE UINT32 ch_map_reg92;
    VOLATILE UINT32 ch_map_reg93;
    VOLATILE UINT32 ch_map_reg94;
    VOLATILE UINT32 ch_map_reg95;
    VOLATILE UINT32 ch_map_reg96;
    VOLATILE UINT32 ch_map_reg97;
    VOLATILE UINT32 ch_map_reg98;
    VOLATILE UINT32 ch_map_reg99;
    VOLATILE UINT32 ch_map_reg100;
    VOLATILE UINT32 ch_map_reg101;
    VOLATILE UINT32 ch_map_reg102;
    VOLATILE UINT32 ch_map_reg103;
    VOLATILE UINT32 ch_map_reg104;
    VOLATILE UINT32 ch_map_reg105;
    VOLATILE UINT32 ch_map_reg106;
    VOLATILE UINT32 ch_map_reg107;
    VOLATILE UINT32 ch_map_reg108;
    VOLATILE UINT32 ch_map_reg109;
    VOLATILE UINT32 ch_map_reg110;
    VOLATILE UINT32 ch_map_reg111;
    VOLATILE UINT32 ch_map_reg112;
    VOLATILE UINT32 ch_map_reg113;
    VOLATILE UINT32 ch_map_reg114;
    VOLATILE UINT32 ch_map_reg115;
    VOLATILE UINT32 ch_map_reg116;
    VOLATILE UINT32 ch_map_reg117;
    VOLATILE UINT32 ch_map_reg118;
    VOLATILE UINT32 ch_map_reg119;
    VOLATILE UINT32 ch_map_reg120;
    VOLATILE UINT32 ch_map_reg121;
    VOLATILE UINT32 ch_map_reg122;
    VOLATILE UINT32 ch_map_reg123;
    VOLATILE UINT32 ch_map_reg124;
    VOLATILE UINT32 ch_map_reg125;
    VOLATILE UINT32 ch_map_reg126;
    VOLATILE UINT32 ch_map_reg127;
    VOLATILE UINT32 ch_map_reg128;
    VOLATILE UINT32 ch_map_reg129;
    VOLATILE UINT32 ch_map_reg130;
    VOLATILE UINT32 ch_map_reg131;
    VOLATILE UINT32 ch_map_reg132;
    VOLATILE UINT32 ch_map_reg133;
    VOLATILE UINT32 ch_map_reg134;
    VOLATILE UINT32 ch_map_reg135;
    VOLATILE UINT32 ch_map_reg136;
    VOLATILE UINT32 ch_map_reg137;
    VOLATILE UINT32 ch_map_reg138;
    VOLATILE UINT32 ch_map_reg139;
    VOLATILE UINT32 ch_map_reg140;
    VOLATILE UINT32 ch_map_reg141;
    VOLATILE UINT32 ch_map_reg142;
    VOLATILE UINT32 ch_map_reg143;
    VOLATILE UINT32 ch_map_reg144;
    VOLATILE UINT32 ch_map_reg145;
    VOLATILE UINT32 ch_map_reg146;
    VOLATILE UINT32 ch_map_reg147;
    VOLATILE UINT32 ch_map_reg148;
    VOLATILE UINT32 ch_map_reg149;
    VOLATILE UINT32 ch_map_reg150;
    VOLATILE UINT32 ch_map_reg151;
    VOLATILE UINT32 ch_map_reg152;
    VOLATILE UINT32 ch_map_reg153;
    VOLATILE UINT32 ch_map_reg154;
    VOLATILE UINT32 ch_map_reg155;
    VOLATILE UINT32 ch_map_reg156;
    VOLATILE UINT32 ch_map_reg157;
    VOLATILE UINT32 ch_map_reg158;
    VOLATILE UINT32 ch_map_reg159;
    VOLATILE UINT32 ch_map_reg160;
    VOLATILE UINT32 ch_map_reg161;
    VOLATILE UINT32 ch_map_reg162;
    VOLATILE UINT32 ch_map_reg163;
    VOLATILE UINT32 ch_map_reg164;
    VOLATILE UINT32 ch_map_reg165;
    VOLATILE UINT32 ch_map_reg166;
    VOLATILE UINT32 ch_map_reg167;
    VOLATILE UINT32 ch_map_reg168;
    VOLATILE UINT32 ch_map_reg169;
    VOLATILE UINT32 ch_map_reg170;
    VOLATILE UINT32 ch_map_reg171;
    VOLATILE UINT32 ch_map_reg172;
    VOLATILE UINT32 ch_map_reg173;
    VOLATILE UINT32 ch_map_reg174;
    VOLATILE UINT32 ch_map_reg175;
    VOLATILE UINT32 ch_map_reg176;
    VOLATILE UINT32 ch_map_reg177;
    VOLATILE UINT32 ch_map_reg178;
    VOLATILE UINT32 ch_map_reg179;
    VOLATILE UINT32 ch_map_reg180;
    VOLATILE UINT32 ch_map_reg181;
    VOLATILE UINT32 ch_map_reg182;
    VOLATILE UINT32 ch_map_reg183;
    VOLATILE UINT32 ch_map_reg184;
    VOLATILE UINT32 ch_map_reg185;
    VOLATILE UINT32 ch_map_reg186;
    VOLATILE UINT32 ch_map_reg187;
    VOLATILE UINT32 ch_map_reg188;
    VOLATILE UINT32 ch_map_reg189;
    VOLATILE UINT32 ch_map_reg190;
    VOLATILE UINT32 ch_map_reg191;
    VOLATILE UINT32 ch_map_reg192;
    VOLATILE UINT32 ch_map_reg193;
    VOLATILE UINT32 ch_map_reg194;
    VOLATILE UINT32 ch_map_reg195;
    VOLATILE UINT32 ch_map_reg196;
    VOLATILE UINT32 ch_map_reg197;
    VOLATILE UINT32 ch_map_reg198;
    VOLATILE UINT32 ch_map_reg199;
    VOLATILE UINT32 ch_map_reg200;
    VOLATILE UINT32 ch_map_reg201;
    VOLATILE UINT32 ch_map_reg202;
    VOLATILE UINT32 ch_map_reg203;
    VOLATILE UINT32 ch_map_reg204;
    VOLATILE UINT32 ch_map_reg205;
    VOLATILE UINT32 ch_map_reg206;
    VOLATILE UINT32 ch_map_reg207;
    VOLATILE UINT32 ch_map_reg208;
    VOLATILE UINT32 ch_map_reg209;
    VOLATILE UINT32 ch_map_reg210;
    VOLATILE UINT32 ch_map_reg211;
    VOLATILE UINT32 ch_map_reg212;
    VOLATILE UINT32 ch_map_reg213;
    VOLATILE UINT32 ch_map_reg214;
    VOLATILE UINT32 ch_map_reg215;
    VOLATILE UINT32 ch_map_reg216;
    VOLATILE UINT32 ch_map_reg217;
    VOLATILE UINT32 ch_map_reg218;
    VOLATILE UINT32 ch_map_reg219;
    VOLATILE UINT32 ch_map_reg220;
    VOLATILE UINT32 ch_map_reg221;
    VOLATILE UINT32 ch_map_reg222;
    VOLATILE UINT32 ch_map_reg223;
    VOLATILE UINT32 ch_map_reg224;
    VOLATILE UINT32 ch_map_reg225;
    VOLATILE UINT32 ch_map_reg226;
    VOLATILE UINT32 ch_map_reg227;
    VOLATILE UINT32 ch_map_reg228;
    VOLATILE UINT32 ch_map_reg229;
    VOLATILE UINT32 ch_map_reg230;
    VOLATILE UINT32 ch_map_reg231;
    VOLATILE UINT32 ch_map_reg232;
    VOLATILE UINT32 ch_map_reg233;
    VOLATILE UINT32 ch_map_reg234;
    VOLATILE UINT32 ch_map_reg235;
    VOLATILE UINT32 ch_map_reg236;
    VOLATILE UINT32 ch_map_reg237;
    VOLATILE UINT32 ch_map_reg238;
    VOLATILE UINT32 ch_map_reg239;
    VOLATILE UINT32 ch_map_reg240;
    VOLATILE UINT32 ch_map_reg241;
    VOLATILE UINT32 ch_map_reg242;
    VOLATILE UINT32 ch_map_reg243;
    VOLATILE UINT32 ch_map_reg244;
    VOLATILE UINT32 ch_map_reg245;
    VOLATILE UINT32 ch_map_reg246;
    VOLATILE UINT32 ch_map_reg247;
    VOLATILE UINT32 ch_map_reg248;
    VOLATILE UINT32 ch_map_reg249;
    VOLATILE UINT32 ch_map_reg250;
    VOLATILE UINT32 ch_map_reg251;
    VOLATILE UINT32 ch_map_reg252;
    VOLATILE UINT32 ch_map_reg253;
    VOLATILE UINT32 ch_map_reg254;
    VOLATILE UINT32 ch_map_reg255;
#else
    VOLATILE UINT8  ch_map[1024];			/*Channel Map Registers*/
#endif
#ifdef CSL_MODIFICATION    
    VOLATILE UINT32 hint_map_reg0;
    VOLATILE UINT32 hint_map_reg1;
    VOLATILE UINT32 hint_map_reg2;
    VOLATILE UINT32 hint_map_reg3;
    VOLATILE UINT32 hint_map_reg4;
    VOLATILE UINT32 hint_map_reg5;
    VOLATILE UINT32 hint_map_reg6;
    VOLATILE UINT32 hint_map_reg7;
    VOLATILE UINT32 hint_map_reg8;
    VOLATILE UINT32 hint_map_reg9;
    VOLATILE UINT32 hint_map_reg10;
    VOLATILE UINT32 hint_map_reg11;
    VOLATILE UINT32 hint_map_reg12;
    VOLATILE UINT32 hint_map_reg13;
    VOLATILE UINT32 hint_map_reg14;
    VOLATILE UINT32 hint_map_reg15;
    VOLATILE UINT32 hint_map_reg16;
    VOLATILE UINT32 hint_map_reg17;
    VOLATILE UINT32 hint_map_reg18;
    VOLATILE UINT32 hint_map_reg19;
    VOLATILE UINT32 hint_map_reg20;
    VOLATILE UINT32 hint_map_reg21;
    VOLATILE UINT32 hint_map_reg22;
    VOLATILE UINT32 hint_map_reg23;
    VOLATILE UINT32 hint_map_reg24;
    VOLATILE UINT32 hint_map_reg25;
    VOLATILE UINT32 hint_map_reg26;
    VOLATILE UINT32 hint_map_reg27;
    VOLATILE UINT32 hint_map_reg28;
    VOLATILE UINT32 hint_map_reg29;
    VOLATILE UINT32 hint_map_reg30;
    VOLATILE UINT32 hint_map_reg31;
    VOLATILE UINT32 hint_map_reg32;
    VOLATILE UINT32 hint_map_reg33;
    VOLATILE UINT32 hint_map_reg34;
    VOLATILE UINT32 hint_map_reg35;
    VOLATILE UINT32 hint_map_reg36;
    VOLATILE UINT32 hint_map_reg37;
    VOLATILE UINT32 hint_map_reg38;
    VOLATILE UINT32 hint_map_reg39;
    VOLATILE UINT32 hint_map_reg40;
    VOLATILE UINT32 hint_map_reg41;
    VOLATILE UINT32 hint_map_reg42;
    VOLATILE UINT32 hint_map_reg43;
    VOLATILE UINT32 hint_map_reg44;
    VOLATILE UINT32 hint_map_reg45;
    VOLATILE UINT32 hint_map_reg46;
    VOLATILE UINT32 hint_map_reg47;
    VOLATILE UINT32 hint_map_reg48;
    VOLATILE UINT32 hint_map_reg49;
    VOLATILE UINT32 hint_map_reg50;
    VOLATILE UINT32 hint_map_reg51;
    VOLATILE UINT32 hint_map_reg52;
    VOLATILE UINT32 hint_map_reg53;
    VOLATILE UINT32 hint_map_reg54;
    VOLATILE UINT32 hint_map_reg55;
    VOLATILE UINT32 hint_map_reg56;
    VOLATILE UINT32 hint_map_reg57;
    VOLATILE UINT32 hint_map_reg58;
    VOLATILE UINT32 hint_map_reg59;
    VOLATILE UINT32 hint_map_reg60;
    VOLATILE UINT32 hint_map_reg61;
    VOLATILE UINT32 hint_map_reg62;
    VOLATILE UINT32 hint_map_reg63;
#else
//    VOLATILE UINT32 hint_map[64];			/*Host Map Registers*/
    VOLATILE UINT8 hint_map[256];			/*Host Map Registers*/
#endif
#ifdef CSL_MODIFICATION    
    VOLATILE UINT32 pri_hint_reg0;
    VOLATILE UINT32 pri_hint_reg1;
    VOLATILE UINT32 pri_hint_reg2;
    VOLATILE UINT32 pri_hint_reg3;
    VOLATILE UINT32 pri_hint_reg4;
    VOLATILE UINT32 pri_hint_reg5;
    VOLATILE UINT32 pri_hint_reg6;
    VOLATILE UINT32 pri_hint_reg7;
    VOLATILE UINT32 pri_hint_reg8;
    VOLATILE UINT32 pri_hint_reg9;
    VOLATILE UINT32 pri_hint_reg10;
    VOLATILE UINT32 pri_hint_reg11;
    VOLATILE UINT32 pri_hint_reg12;
    VOLATILE UINT32 pri_hint_reg13;
    VOLATILE UINT32 pri_hint_reg14;
    VOLATILE UINT32 pri_hint_reg15;
    VOLATILE UINT32 pri_hint_reg16;
    VOLATILE UINT32 pri_hint_reg17;
    VOLATILE UINT32 pri_hint_reg18;
    VOLATILE UINT32 pri_hint_reg19;
    VOLATILE UINT32 pri_hint_reg20;
    VOLATILE UINT32 pri_hint_reg21;
    VOLATILE UINT32 pri_hint_reg22;
    VOLATILE UINT32 pri_hint_reg23;
    VOLATILE UINT32 pri_hint_reg24;
    VOLATILE UINT32 pri_hint_reg25;
    VOLATILE UINT32 pri_hint_reg26;
    VOLATILE UINT32 pri_hint_reg27;
    VOLATILE UINT32 pri_hint_reg28;
    VOLATILE UINT32 pri_hint_reg29;
    VOLATILE UINT32 pri_hint_reg30;
    VOLATILE UINT32 pri_hint_reg31;
    VOLATILE UINT32 pri_hint_reg32;
    VOLATILE UINT32 pri_hint_reg33;
    VOLATILE UINT32 pri_hint_reg34;
    VOLATILE UINT32 pri_hint_reg35;
    VOLATILE UINT32 pri_hint_reg36;
    VOLATILE UINT32 pri_hint_reg37;
    VOLATILE UINT32 pri_hint_reg38;
    VOLATILE UINT32 pri_hint_reg39;
    VOLATILE UINT32 pri_hint_reg40;
    VOLATILE UINT32 pri_hint_reg41;
    VOLATILE UINT32 pri_hint_reg42;
    VOLATILE UINT32 pri_hint_reg43;
    VOLATILE UINT32 pri_hint_reg44;
    VOLATILE UINT32 pri_hint_reg45;
    VOLATILE UINT32 pri_hint_reg46;
    VOLATILE UINT32 pri_hint_reg47;
    VOLATILE UINT32 pri_hint_reg48;
    VOLATILE UINT32 pri_hint_reg49;
    VOLATILE UINT32 pri_hint_reg50;
    VOLATILE UINT32 pri_hint_reg51;
    VOLATILE UINT32 pri_hint_reg52;
    VOLATILE UINT32 pri_hint_reg53;
    VOLATILE UINT32 pri_hint_reg54;
    VOLATILE UINT32 pri_hint_reg55;
    VOLATILE UINT32 pri_hint_reg56;
    VOLATILE UINT32 pri_hint_reg57;
    VOLATILE UINT32 pri_hint_reg58;
    VOLATILE UINT32 pri_hint_reg59;
    VOLATILE UINT32 pri_hint_reg60;
    VOLATILE UINT32 pri_hint_reg61;
    VOLATILE UINT32 pri_hint_reg62;
    VOLATILE UINT32 pri_hint_reg63;
    VOLATILE UINT32 pri_hint_reg64;
    VOLATILE UINT32 pri_hint_reg65;
    VOLATILE UINT32 pri_hint_reg66;
    VOLATILE UINT32 pri_hint_reg67;
    VOLATILE UINT32 pri_hint_reg68;
    VOLATILE UINT32 pri_hint_reg69;
    VOLATILE UINT32 pri_hint_reg70;
    VOLATILE UINT32 pri_hint_reg71;
    VOLATILE UINT32 pri_hint_reg72;
    VOLATILE UINT32 pri_hint_reg73;
    VOLATILE UINT32 pri_hint_reg74;
    VOLATILE UINT32 pri_hint_reg75;
    VOLATILE UINT32 pri_hint_reg76;
    VOLATILE UINT32 pri_hint_reg77;
    VOLATILE UINT32 pri_hint_reg78;
    VOLATILE UINT32 pri_hint_reg79;
    VOLATILE UINT32 pri_hint_reg80;
    VOLATILE UINT32 pri_hint_reg81;
    VOLATILE UINT32 pri_hint_reg82;
    VOLATILE UINT32 pri_hint_reg83;
    VOLATILE UINT32 pri_hint_reg84;
    VOLATILE UINT32 pri_hint_reg85;
    VOLATILE UINT32 pri_hint_reg86;
    VOLATILE UINT32 pri_hint_reg87;
    VOLATILE UINT32 pri_hint_reg88;
    VOLATILE UINT32 pri_hint_reg89;
    VOLATILE UINT32 pri_hint_reg90;
    VOLATILE UINT32 pri_hint_reg91;
    VOLATILE UINT32 pri_hint_reg92;
    VOLATILE UINT32 pri_hint_reg93;
    VOLATILE UINT32 pri_hint_reg94;
    VOLATILE UINT32 pri_hint_reg95;
    VOLATILE UINT32 pri_hint_reg96;
    VOLATILE UINT32 pri_hint_reg97;
    VOLATILE UINT32 pri_hint_reg98;
    VOLATILE UINT32 pri_hint_reg99;
    VOLATILE UINT32 pri_hint_reg100;
    VOLATILE UINT32 pri_hint_reg101;
    VOLATILE UINT32 pri_hint_reg102;
    VOLATILE UINT32 pri_hint_reg103;
    VOLATILE UINT32 pri_hint_reg104;
    VOLATILE UINT32 pri_hint_reg105;
    VOLATILE UINT32 pri_hint_reg106;
    VOLATILE UINT32 pri_hint_reg107;
    VOLATILE UINT32 pri_hint_reg108;
    VOLATILE UINT32 pri_hint_reg109;
    VOLATILE UINT32 pri_hint_reg110;
    VOLATILE UINT32 pri_hint_reg111;
    VOLATILE UINT32 pri_hint_reg112;
    VOLATILE UINT32 pri_hint_reg113;
    VOLATILE UINT32 pri_hint_reg114;
    VOLATILE UINT32 pri_hint_reg115;
    VOLATILE UINT32 pri_hint_reg116;
    VOLATILE UINT32 pri_hint_reg117;
    VOLATILE UINT32 pri_hint_reg118;
    VOLATILE UINT32 pri_hint_reg119;
    VOLATILE UINT32 pri_hint_reg120;
    VOLATILE UINT32 pri_hint_reg121;
    VOLATILE UINT32 pri_hint_reg122;
    VOLATILE UINT32 pri_hint_reg123;
    VOLATILE UINT32 pri_hint_reg124;
    VOLATILE UINT32 pri_hint_reg125;
    VOLATILE UINT32 pri_hint_reg126;
    VOLATILE UINT32 pri_hint_reg127;
    VOLATILE UINT32 pri_hint_reg128;
    VOLATILE UINT32 pri_hint_reg129;
    VOLATILE UINT32 pri_hint_reg130;
    VOLATILE UINT32 pri_hint_reg131;
    VOLATILE UINT32 pri_hint_reg132;
    VOLATILE UINT32 pri_hint_reg133;
    VOLATILE UINT32 pri_hint_reg134;
    VOLATILE UINT32 pri_hint_reg135;
    VOLATILE UINT32 pri_hint_reg136;
    VOLATILE UINT32 pri_hint_reg137;
    VOLATILE UINT32 pri_hint_reg138;
    VOLATILE UINT32 pri_hint_reg139;
    VOLATILE UINT32 pri_hint_reg140;
    VOLATILE UINT32 pri_hint_reg141;
    VOLATILE UINT32 pri_hint_reg142;
    VOLATILE UINT32 pri_hint_reg143;
    VOLATILE UINT32 pri_hint_reg144;
    VOLATILE UINT32 pri_hint_reg145;
    VOLATILE UINT32 pri_hint_reg146;
    VOLATILE UINT32 pri_hint_reg147;
    VOLATILE UINT32 pri_hint_reg148;
    VOLATILE UINT32 pri_hint_reg149;
    VOLATILE UINT32 pri_hint_reg150;
    VOLATILE UINT32 pri_hint_reg151;
    VOLATILE UINT32 pri_hint_reg152;
    VOLATILE UINT32 pri_hint_reg153;
    VOLATILE UINT32 pri_hint_reg154;
    VOLATILE UINT32 pri_hint_reg155;
    VOLATILE UINT32 pri_hint_reg156;
    VOLATILE UINT32 pri_hint_reg157;
    VOLATILE UINT32 pri_hint_reg158;
    VOLATILE UINT32 pri_hint_reg159;
    VOLATILE UINT32 pri_hint_reg160;
    VOLATILE UINT32 pri_hint_reg161;
    VOLATILE UINT32 pri_hint_reg162;
    VOLATILE UINT32 pri_hint_reg163;
    VOLATILE UINT32 pri_hint_reg164;
    VOLATILE UINT32 pri_hint_reg165;
    VOLATILE UINT32 pri_hint_reg166;
    VOLATILE UINT32 pri_hint_reg167;
    VOLATILE UINT32 pri_hint_reg168;
    VOLATILE UINT32 pri_hint_reg169;
    VOLATILE UINT32 pri_hint_reg170;
    VOLATILE UINT32 pri_hint_reg171;
    VOLATILE UINT32 pri_hint_reg172;
    VOLATILE UINT32 pri_hint_reg173;
    VOLATILE UINT32 pri_hint_reg174;
    VOLATILE UINT32 pri_hint_reg175;
    VOLATILE UINT32 pri_hint_reg176;
    VOLATILE UINT32 pri_hint_reg177;
    VOLATILE UINT32 pri_hint_reg178;
    VOLATILE UINT32 pri_hint_reg179;
    VOLATILE UINT32 pri_hint_reg180;
    VOLATILE UINT32 pri_hint_reg181;
    VOLATILE UINT32 pri_hint_reg182;
    VOLATILE UINT32 pri_hint_reg183;
    VOLATILE UINT32 pri_hint_reg184;
    VOLATILE UINT32 pri_hint_reg185;
    VOLATILE UINT32 pri_hint_reg186;
    VOLATILE UINT32 pri_hint_reg187;
    VOLATILE UINT32 pri_hint_reg188;
    VOLATILE UINT32 pri_hint_reg189;
    VOLATILE UINT32 pri_hint_reg190;
    VOLATILE UINT32 pri_hint_reg191;
    VOLATILE UINT32 pri_hint_reg192;
    VOLATILE UINT32 pri_hint_reg193;
    VOLATILE UINT32 pri_hint_reg194;
    VOLATILE UINT32 pri_hint_reg195;
    VOLATILE UINT32 pri_hint_reg196;
    VOLATILE UINT32 pri_hint_reg197;
    VOLATILE UINT32 pri_hint_reg198;
    VOLATILE UINT32 pri_hint_reg199;
    VOLATILE UINT32 pri_hint_reg200;
    VOLATILE UINT32 pri_hint_reg201;
    VOLATILE UINT32 pri_hint_reg202;
    VOLATILE UINT32 pri_hint_reg203;
    VOLATILE UINT32 pri_hint_reg204;
    VOLATILE UINT32 pri_hint_reg205;
    VOLATILE UINT32 pri_hint_reg206;
    VOLATILE UINT32 pri_hint_reg207;
    VOLATILE UINT32 pri_hint_reg208;
    VOLATILE UINT32 pri_hint_reg209;
    VOLATILE UINT32 pri_hint_reg210;
    VOLATILE UINT32 pri_hint_reg211;
    VOLATILE UINT32 pri_hint_reg212;
    VOLATILE UINT32 pri_hint_reg213;
    VOLATILE UINT32 pri_hint_reg214;
    VOLATILE UINT32 pri_hint_reg215;
    VOLATILE UINT32 pri_hint_reg216;
    VOLATILE UINT32 pri_hint_reg217;
    VOLATILE UINT32 pri_hint_reg218;
    VOLATILE UINT32 pri_hint_reg219;
    VOLATILE UINT32 pri_hint_reg220;
    VOLATILE UINT32 pri_hint_reg221;
    VOLATILE UINT32 pri_hint_reg222;
    VOLATILE UINT32 pri_hint_reg223;
    VOLATILE UINT32 pri_hint_reg224;
    VOLATILE UINT32 pri_hint_reg225;
    VOLATILE UINT32 pri_hint_reg226;
    VOLATILE UINT32 pri_hint_reg227;
    VOLATILE UINT32 pri_hint_reg228;
    VOLATILE UINT32 pri_hint_reg229;
    VOLATILE UINT32 pri_hint_reg230;
    VOLATILE UINT32 pri_hint_reg231;
    VOLATILE UINT32 pri_hint_reg232;
    VOLATILE UINT32 pri_hint_reg233;
    VOLATILE UINT32 pri_hint_reg234;
    VOLATILE UINT32 pri_hint_reg235;
    VOLATILE UINT32 pri_hint_reg236;
    VOLATILE UINT32 pri_hint_reg237;
    VOLATILE UINT32 pri_hint_reg238;
    VOLATILE UINT32 pri_hint_reg239;
    VOLATILE UINT32 pri_hint_reg240;
    VOLATILE UINT32 pri_hint_reg241;
    VOLATILE UINT32 pri_hint_reg242;
    VOLATILE UINT32 pri_hint_reg243;
    VOLATILE UINT32 pri_hint_reg244;
    VOLATILE UINT32 pri_hint_reg245;
    VOLATILE UINT32 pri_hint_reg246;
    VOLATILE UINT32 pri_hint_reg247;
    VOLATILE UINT32 pri_hint_reg248;
    VOLATILE UINT32 pri_hint_reg249;
    VOLATILE UINT32 pri_hint_reg250;
    VOLATILE UINT32 pri_hint_reg251;
    VOLATILE UINT32 pri_hint_reg252;
    VOLATILE UINT32 pri_hint_reg253;
    VOLATILE UINT32 pri_hint_reg254;
    VOLATILE UINT32 pri_hint_reg255;
#else
    VOLATILE UINT32 pri_hint_reg[256];		/*Host Interrupt Prioritized Index Registers*/
#endif
#ifdef CSL_MODIFICATION
    VOLATILE UINT32 polarity_reg0;
    VOLATILE UINT32 polarity_reg1;
    VOLATILE UINT32 polarity_reg2;
    VOLATILE UINT32 polarity_reg3;
    VOLATILE UINT32 polarity_reg4;
    VOLATILE UINT32 polarity_reg5;
    VOLATILE UINT32 polarity_reg6;
    VOLATILE UINT32 polarity_reg7;
    VOLATILE UINT32 polarity_reg8;
    VOLATILE UINT32 polarity_reg9;
    VOLATILE UINT32 polarity_reg10;
    VOLATILE UINT32 polarity_reg11;
    VOLATILE UINT32 polarity_reg12;
    VOLATILE UINT32 polarity_reg13;
    VOLATILE UINT32 polarity_reg14;
    VOLATILE UINT32 polarity_reg15;
    VOLATILE UINT32 polarity_reg16;
    VOLATILE UINT32 polarity_reg17;
    VOLATILE UINT32 polarity_reg18;
    VOLATILE UINT32 polarity_reg19;
    VOLATILE UINT32 polarity_reg20;
    VOLATILE UINT32 polarity_reg21;
    VOLATILE UINT32 polarity_reg22;
    VOLATILE UINT32 polarity_reg23;
    VOLATILE UINT32 polarity_reg24;
    VOLATILE UINT32 polarity_reg25;
    VOLATILE UINT32 polarity_reg26;
    VOLATILE UINT32 polarity_reg27;
    VOLATILE UINT32 polarity_reg28;
    VOLATILE UINT32 polarity_reg29;
    VOLATILE UINT32 polarity_reg30;
    VOLATILE UINT32 polarity_reg31;
#else
    VOLATILE UINT32 polarity_reg[32];
#endif
#ifdef CSL_MODIFICATION
    VOLATILE UINT32 type_reg0;
    VOLATILE UINT32 type_reg1;
    VOLATILE UINT32 type_reg2;
    VOLATILE UINT32 type_reg3;
    VOLATILE UINT32 type_reg4;
    VOLATILE UINT32 type_reg5;
    VOLATILE UINT32 type_reg6;
    VOLATILE UINT32 type_reg7;
    VOLATILE UINT32 type_reg8;
    VOLATILE UINT32 type_reg9;
    VOLATILE UINT32 type_reg10;
    VOLATILE UINT32 type_reg11;
    VOLATILE UINT32 type_reg12;
    VOLATILE UINT32 type_reg13;
    VOLATILE UINT32 type_reg14;
    VOLATILE UINT32 type_reg15;
    VOLATILE UINT32 type_reg16;
    VOLATILE UINT32 type_reg17;
    VOLATILE UINT32 type_reg18;
    VOLATILE UINT32 type_reg19;
    VOLATILE UINT32 type_reg20;
    VOLATILE UINT32 type_reg21;
    VOLATILE UINT32 type_reg22;
    VOLATILE UINT32 type_reg23;
    VOLATILE UINT32 type_reg24;
    VOLATILE UINT32 type_reg25;
    VOLATILE UINT32 type_reg26;
    VOLATILE UINT32 type_reg27;
    VOLATILE UINT32 type_reg28;
    VOLATILE UINT32 type_reg29;
    VOLATILE UINT32 type_reg30;
    VOLATILE UINT32 type_reg31;
#else
    VOLATILE UINT32 type_reg[32];
#endif    
    VOLATILE UINT8 Rsvd7[256];
#ifdef CSL_MODIFICATION    
    VOLATILE UINT32 dbg_select_reg0;
    VOLATILE UINT32 dbg_select_reg1;
    VOLATILE UINT32 dbg_select_reg2;
    VOLATILE UINT32 dbg_select_reg3;
    VOLATILE UINT32 dbg_select_reg4;
    VOLATILE UINT32 dbg_select_reg5;
    VOLATILE UINT32 dbg_select_reg6;
    VOLATILE UINT32 dbg_select_reg7;
    VOLATILE UINT32 dbg_select_reg8;
    VOLATILE UINT32 dbg_select_reg9;
    VOLATILE UINT32 dbg_select_reg10;
    VOLATILE UINT32 dbg_select_reg11;
    VOLATILE UINT32 dbg_select_reg12;
    VOLATILE UINT32 dbg_select_reg13;
    VOLATILE UINT32 dbg_select_reg14;
    VOLATILE UINT32 dbg_select_reg15;
    VOLATILE UINT32 dbg_select_reg16;
    VOLATILE UINT32 dbg_select_reg17;
    VOLATILE UINT32 dbg_select_reg18;
    VOLATILE UINT32 dbg_select_reg19;
    VOLATILE UINT32 dbg_select_reg20;
    VOLATILE UINT32 dbg_select_reg21;
    VOLATILE UINT32 dbg_select_reg22;
    VOLATILE UINT32 dbg_select_reg23;
    VOLATILE UINT32 dbg_select_reg24;
    VOLATILE UINT32 dbg_select_reg25;
    VOLATILE UINT32 dbg_select_reg26;
    VOLATILE UINT32 dbg_select_reg27;
    VOLATILE UINT32 dbg_select_reg28;
    VOLATILE UINT32 dbg_select_reg29;
    VOLATILE UINT32 dbg_select_reg30;
    VOLATILE UINT32 dbg_select_reg31;
    VOLATILE UINT32 dbg_select_reg32;
    VOLATILE UINT32 dbg_select_reg33;
    VOLATILE UINT32 dbg_select_reg34;
    VOLATILE UINT32 dbg_select_reg35;
    VOLATILE UINT32 dbg_select_reg36;
    VOLATILE UINT32 dbg_select_reg37;
    VOLATILE UINT32 dbg_select_reg38;
    VOLATILE UINT32 dbg_select_reg39;
    VOLATILE UINT32 dbg_select_reg40;
    VOLATILE UINT32 dbg_select_reg41;
    VOLATILE UINT32 dbg_select_reg42;
    VOLATILE UINT32 dbg_select_reg43;
    VOLATILE UINT32 dbg_select_reg44;
    VOLATILE UINT32 dbg_select_reg45;
    VOLATILE UINT32 dbg_select_reg46;
    VOLATILE UINT32 dbg_select_reg47;
    VOLATILE UINT32 dbg_select_reg48;
    VOLATILE UINT32 dbg_select_reg49;
    VOLATILE UINT32 dbg_select_reg50;
    VOLATILE UINT32 dbg_select_reg51;
    VOLATILE UINT32 dbg_select_reg52;
    VOLATILE UINT32 dbg_select_reg53;
    VOLATILE UINT32 dbg_select_reg54;
    VOLATILE UINT32 dbg_select_reg55;
    VOLATILE UINT32 dbg_select_reg56;
    VOLATILE UINT32 dbg_select_reg57;
    VOLATILE UINT32 dbg_select_reg58;
    VOLATILE UINT32 dbg_select_reg59;
    VOLATILE UINT32 dbg_select_reg60;
    VOLATILE UINT32 dbg_select_reg61;
    VOLATILE UINT32 dbg_select_reg62;
    VOLATILE UINT32 dbg_select_reg63;
#else
    VOLATILE UINT32 dbg_select_reg[64];
#endif
#ifdef CSL_MODIFICATION  
    VOLATILE UINT32 secure_enable_reg0;
    VOLATILE UINT32 secure_enable_reg1;
    VOLATILE UINT32 secure_enable_reg2;
    VOLATILE UINT32 secure_enable_reg3;
    VOLATILE UINT32 secure_enable_reg4;
    VOLATILE UINT32 secure_enable_reg5;
    VOLATILE UINT32 secure_enable_reg6;
    VOLATILE UINT32 secure_enable_reg7;
    VOLATILE UINT32 secure_enable_reg8;
    VOLATILE UINT32 secure_enable_reg9;
    VOLATILE UINT32 secure_enable_reg10;
    VOLATILE UINT32 secure_enable_reg11;
    VOLATILE UINT32 secure_enable_reg12;
    VOLATILE UINT32 secure_enable_reg13;
    VOLATILE UINT32 secure_enable_reg14;
    VOLATILE UINT32 secure_enable_reg15;
    VOLATILE UINT32 secure_enable_reg16;
    VOLATILE UINT32 secure_enable_reg17;
    VOLATILE UINT32 secure_enable_reg18;
    VOLATILE UINT32 secure_enable_reg19;
    VOLATILE UINT32 secure_enable_reg20;
    VOLATILE UINT32 secure_enable_reg21;
    VOLATILE UINT32 secure_enable_reg22;
    VOLATILE UINT32 secure_enable_reg23;
    VOLATILE UINT32 secure_enable_reg24;
    VOLATILE UINT32 secure_enable_reg25;
    VOLATILE UINT32 secure_enable_reg26;
    VOLATILE UINT32 secure_enable_reg27;
    VOLATILE UINT32 secure_enable_reg28;
    VOLATILE UINT32 secure_enable_reg29;
    VOLATILE UINT32 secure_enable_reg30;
    VOLATILE UINT32 secure_enable_reg31;
#else
    VOLATILE UINT32 secure_enable_reg[32];
#endif
#ifdef CSL_MODIFICATION  
    VOLATILE UINT32 secure_enable_clr_reg0;
    VOLATILE UINT32 secure_enable_clr_reg1;
    VOLATILE UINT32 secure_enable_clr_reg2;
    VOLATILE UINT32 secure_enable_clr_reg3;
    VOLATILE UINT32 secure_enable_clr_reg4;
    VOLATILE UINT32 secure_enable_clr_reg5;
    VOLATILE UINT32 secure_enable_clr_reg6;
    VOLATILE UINT32 secure_enable_clr_reg7;
    VOLATILE UINT32 secure_enable_clr_reg8;
    VOLATILE UINT32 secure_enable_clr_reg9;
    VOLATILE UINT32 secure_enable_clr_reg10;
    VOLATILE UINT32 secure_enable_clr_reg11;
    VOLATILE UINT32 secure_enable_clr_reg12;
    VOLATILE UINT32 secure_enable_clr_reg13;
    VOLATILE UINT32 secure_enable_clr_reg14;
    VOLATILE UINT32 secure_enable_clr_reg15;
    VOLATILE UINT32 secure_enable_clr_reg16;
    VOLATILE UINT32 secure_enable_clr_reg17;
    VOLATILE UINT32 secure_enable_clr_reg18;
    VOLATILE UINT32 secure_enable_clr_reg19;
    VOLATILE UINT32 secure_enable_clr_reg20;
    VOLATILE UINT32 secure_enable_clr_reg21;
    VOLATILE UINT32 secure_enable_clr_reg22;
    VOLATILE UINT32 secure_enable_clr_reg23;
    VOLATILE UINT32 secure_enable_clr_reg24;
    VOLATILE UINT32 secure_enable_clr_reg25;
    VOLATILE UINT32 secure_enable_clr_reg26;
    VOLATILE UINT32 secure_enable_clr_reg27;
    VOLATILE UINT32 secure_enable_clr_reg28;
    VOLATILE UINT32 secure_enable_clr_reg29;
    VOLATILE UINT32 secure_enable_clr_reg30;
    VOLATILE UINT32 secure_enable_clr_reg31;
#else
    VOLATILE UINT32 secure_enable_clr_reg[32];
#endif
#ifdef CSL_MODIFICATION   
    VOLATILE UINT32 nest_level_reg0;
    VOLATILE UINT32 nest_level_reg1;
    VOLATILE UINT32 nest_level_reg2;
    VOLATILE UINT32 nest_level_reg3;
    VOLATILE UINT32 nest_level_reg4;
    VOLATILE UINT32 nest_level_reg5;
    VOLATILE UINT32 nest_level_reg6;
    VOLATILE UINT32 nest_level_reg7;
    VOLATILE UINT32 nest_level_reg8;
    VOLATILE UINT32 nest_level_reg9;
    VOLATILE UINT32 nest_level_reg10;
    VOLATILE UINT32 nest_level_reg11;
    VOLATILE UINT32 nest_level_reg12;
    VOLATILE UINT32 nest_level_reg13;
    VOLATILE UINT32 nest_level_reg14;
    VOLATILE UINT32 nest_level_reg15;
    VOLATILE UINT32 nest_level_reg16;
    VOLATILE UINT32 nest_level_reg17;
    VOLATILE UINT32 nest_level_reg18;
    VOLATILE UINT32 nest_level_reg19;
    VOLATILE UINT32 nest_level_reg20;
    VOLATILE UINT32 nest_level_reg21;
    VOLATILE UINT32 nest_level_reg22;
    VOLATILE UINT32 nest_level_reg23;
    VOLATILE UINT32 nest_level_reg24;
    VOLATILE UINT32 nest_level_reg25;
    VOLATILE UINT32 nest_level_reg26;
    VOLATILE UINT32 nest_level_reg27;
    VOLATILE UINT32 nest_level_reg28;
    VOLATILE UINT32 nest_level_reg29;
    VOLATILE UINT32 nest_level_reg30;
    VOLATILE UINT32 nest_level_reg31;
    VOLATILE UINT32 nest_level_reg32;
    VOLATILE UINT32 nest_level_reg33;
    VOLATILE UINT32 nest_level_reg34;
    VOLATILE UINT32 nest_level_reg35;
    VOLATILE UINT32 nest_level_reg36;
    VOLATILE UINT32 nest_level_reg37;
    VOLATILE UINT32 nest_level_reg38;
    VOLATILE UINT32 nest_level_reg39;
    VOLATILE UINT32 nest_level_reg40;
    VOLATILE UINT32 nest_level_reg41;
    VOLATILE UINT32 nest_level_reg42;
    VOLATILE UINT32 nest_level_reg43;
    VOLATILE UINT32 nest_level_reg44;
    VOLATILE UINT32 nest_level_reg45;
    VOLATILE UINT32 nest_level_reg46;
    VOLATILE UINT32 nest_level_reg47;
    VOLATILE UINT32 nest_level_reg48;
    VOLATILE UINT32 nest_level_reg49;
    VOLATILE UINT32 nest_level_reg50;
    VOLATILE UINT32 nest_level_reg51;
    VOLATILE UINT32 nest_level_reg52;
    VOLATILE UINT32 nest_level_reg53;
    VOLATILE UINT32 nest_level_reg54;
    VOLATILE UINT32 nest_level_reg55;
    VOLATILE UINT32 nest_level_reg56;
    VOLATILE UINT32 nest_level_reg57;
    VOLATILE UINT32 nest_level_reg58;
    VOLATILE UINT32 nest_level_reg59;
    VOLATILE UINT32 nest_level_reg60;
    VOLATILE UINT32 nest_level_reg61;
    VOLATILE UINT32 nest_level_reg62;
    VOLATILE UINT32 nest_level_reg63;
    VOLATILE UINT32 nest_level_reg64;
    VOLATILE UINT32 nest_level_reg65;
    VOLATILE UINT32 nest_level_reg66;
    VOLATILE UINT32 nest_level_reg67;
    VOLATILE UINT32 nest_level_reg68;
    VOLATILE UINT32 nest_level_reg69;
    VOLATILE UINT32 nest_level_reg70;
    VOLATILE UINT32 nest_level_reg71;
    VOLATILE UINT32 nest_level_reg72;
    VOLATILE UINT32 nest_level_reg73;
    VOLATILE UINT32 nest_level_reg74;
    VOLATILE UINT32 nest_level_reg75;
    VOLATILE UINT32 nest_level_reg76;
    VOLATILE UINT32 nest_level_reg77;
    VOLATILE UINT32 nest_level_reg78;
    VOLATILE UINT32 nest_level_reg79;
    VOLATILE UINT32 nest_level_reg80;
    VOLATILE UINT32 nest_level_reg81;
    VOLATILE UINT32 nest_level_reg82;
    VOLATILE UINT32 nest_level_reg83;
    VOLATILE UINT32 nest_level_reg84;
    VOLATILE UINT32 nest_level_reg85;
    VOLATILE UINT32 nest_level_reg86;
    VOLATILE UINT32 nest_level_reg87;
    VOLATILE UINT32 nest_level_reg88;
    VOLATILE UINT32 nest_level_reg89;
    VOLATILE UINT32 nest_level_reg90;
    VOLATILE UINT32 nest_level_reg91;
    VOLATILE UINT32 nest_level_reg92;
    VOLATILE UINT32 nest_level_reg93;
    VOLATILE UINT32 nest_level_reg94;
    VOLATILE UINT32 nest_level_reg95;
    VOLATILE UINT32 nest_level_reg96;
    VOLATILE UINT32 nest_level_reg97;
    VOLATILE UINT32 nest_level_reg98;
    VOLATILE UINT32 nest_level_reg99;
    VOLATILE UINT32 nest_level_reg100;
    VOLATILE UINT32 nest_level_reg101;
    VOLATILE UINT32 nest_level_reg102;
    VOLATILE UINT32 nest_level_reg103;
    VOLATILE UINT32 nest_level_reg104;
    VOLATILE UINT32 nest_level_reg105;
    VOLATILE UINT32 nest_level_reg106;
    VOLATILE UINT32 nest_level_reg107;
    VOLATILE UINT32 nest_level_reg108;
    VOLATILE UINT32 nest_level_reg109;
    VOLATILE UINT32 nest_level_reg110;
    VOLATILE UINT32 nest_level_reg111;
    VOLATILE UINT32 nest_level_reg112;
    VOLATILE UINT32 nest_level_reg113;
    VOLATILE UINT32 nest_level_reg114;
    VOLATILE UINT32 nest_level_reg115;
    VOLATILE UINT32 nest_level_reg116;
    VOLATILE UINT32 nest_level_reg117;
    VOLATILE UINT32 nest_level_reg118;
    VOLATILE UINT32 nest_level_reg119;
    VOLATILE UINT32 nest_level_reg120;
    VOLATILE UINT32 nest_level_reg121;
    VOLATILE UINT32 nest_level_reg122;
    VOLATILE UINT32 nest_level_reg123;
    VOLATILE UINT32 nest_level_reg124;
    VOLATILE UINT32 nest_level_reg125;
    VOLATILE UINT32 nest_level_reg126;
    VOLATILE UINT32 nest_level_reg127;
    VOLATILE UINT32 nest_level_reg128;
    VOLATILE UINT32 nest_level_reg129;
    VOLATILE UINT32 nest_level_reg130;
    VOLATILE UINT32 nest_level_reg131;
    VOLATILE UINT32 nest_level_reg132;
    VOLATILE UINT32 nest_level_reg133;
    VOLATILE UINT32 nest_level_reg134;
    VOLATILE UINT32 nest_level_reg135;
    VOLATILE UINT32 nest_level_reg136;
    VOLATILE UINT32 nest_level_reg137;
    VOLATILE UINT32 nest_level_reg138;
    VOLATILE UINT32 nest_level_reg139;
    VOLATILE UINT32 nest_level_reg140;
    VOLATILE UINT32 nest_level_reg141;
    VOLATILE UINT32 nest_level_reg142;
    VOLATILE UINT32 nest_level_reg143;
    VOLATILE UINT32 nest_level_reg144;
    VOLATILE UINT32 nest_level_reg145;
    VOLATILE UINT32 nest_level_reg146;
    VOLATILE UINT32 nest_level_reg147;
    VOLATILE UINT32 nest_level_reg148;
    VOLATILE UINT32 nest_level_reg149;
    VOLATILE UINT32 nest_level_reg150;
    VOLATILE UINT32 nest_level_reg151;
    VOLATILE UINT32 nest_level_reg152;
    VOLATILE UINT32 nest_level_reg153;
    VOLATILE UINT32 nest_level_reg154;
    VOLATILE UINT32 nest_level_reg155;
    VOLATILE UINT32 nest_level_reg156;
    VOLATILE UINT32 nest_level_reg157;
    VOLATILE UINT32 nest_level_reg158;
    VOLATILE UINT32 nest_level_reg159;
    VOLATILE UINT32 nest_level_reg160;
    VOLATILE UINT32 nest_level_reg161;
    VOLATILE UINT32 nest_level_reg162;
    VOLATILE UINT32 nest_level_reg163;
    VOLATILE UINT32 nest_level_reg164;
    VOLATILE UINT32 nest_level_reg165;
    VOLATILE UINT32 nest_level_reg166;
    VOLATILE UINT32 nest_level_reg167;
    VOLATILE UINT32 nest_level_reg168;
    VOLATILE UINT32 nest_level_reg169;
    VOLATILE UINT32 nest_level_reg170;
    VOLATILE UINT32 nest_level_reg171;
    VOLATILE UINT32 nest_level_reg172;
    VOLATILE UINT32 nest_level_reg173;
    VOLATILE UINT32 nest_level_reg174;
    VOLATILE UINT32 nest_level_reg175;
    VOLATILE UINT32 nest_level_reg176;
    VOLATILE UINT32 nest_level_reg177;
    VOLATILE UINT32 nest_level_reg178;
    VOLATILE UINT32 nest_level_reg179;
    VOLATILE UINT32 nest_level_reg180;
    VOLATILE UINT32 nest_level_reg181;
    VOLATILE UINT32 nest_level_reg182;
    VOLATILE UINT32 nest_level_reg183;
    VOLATILE UINT32 nest_level_reg184;
    VOLATILE UINT32 nest_level_reg185;
    VOLATILE UINT32 nest_level_reg186;
    VOLATILE UINT32 nest_level_reg187;
    VOLATILE UINT32 nest_level_reg188;
    VOLATILE UINT32 nest_level_reg189;
    VOLATILE UINT32 nest_level_reg190;
    VOLATILE UINT32 nest_level_reg191;
    VOLATILE UINT32 nest_level_reg192;
    VOLATILE UINT32 nest_level_reg193;
    VOLATILE UINT32 nest_level_reg194;
    VOLATILE UINT32 nest_level_reg195;
    VOLATILE UINT32 nest_level_reg196;
    VOLATILE UINT32 nest_level_reg197;
    VOLATILE UINT32 nest_level_reg198;
    VOLATILE UINT32 nest_level_reg199;
    VOLATILE UINT32 nest_level_reg200;
    VOLATILE UINT32 nest_level_reg201;
    VOLATILE UINT32 nest_level_reg202;
    VOLATILE UINT32 nest_level_reg203;
    VOLATILE UINT32 nest_level_reg204;
    VOLATILE UINT32 nest_level_reg205;
    VOLATILE UINT32 nest_level_reg206;
    VOLATILE UINT32 nest_level_reg207;
    VOLATILE UINT32 nest_level_reg208;
    VOLATILE UINT32 nest_level_reg209;
    VOLATILE UINT32 nest_level_reg210;
    VOLATILE UINT32 nest_level_reg211;
    VOLATILE UINT32 nest_level_reg212;
    VOLATILE UINT32 nest_level_reg213;
    VOLATILE UINT32 nest_level_reg214;
    VOLATILE UINT32 nest_level_reg215;
    VOLATILE UINT32 nest_level_reg216;
    VOLATILE UINT32 nest_level_reg217;
    VOLATILE UINT32 nest_level_reg218;
    VOLATILE UINT32 nest_level_reg219;
    VOLATILE UINT32 nest_level_reg220;
    VOLATILE UINT32 nest_level_reg221;
    VOLATILE UINT32 nest_level_reg222;
    VOLATILE UINT32 nest_level_reg223;
    VOLATILE UINT32 nest_level_reg224;
    VOLATILE UINT32 nest_level_reg225;
    VOLATILE UINT32 nest_level_reg226;
    VOLATILE UINT32 nest_level_reg227;
    VOLATILE UINT32 nest_level_reg228;
    VOLATILE UINT32 nest_level_reg229;
    VOLATILE UINT32 nest_level_reg230;
    VOLATILE UINT32 nest_level_reg231;
    VOLATILE UINT32 nest_level_reg232;
    VOLATILE UINT32 nest_level_reg233;
    VOLATILE UINT32 nest_level_reg234;
    VOLATILE UINT32 nest_level_reg235;
    VOLATILE UINT32 nest_level_reg236;
    VOLATILE UINT32 nest_level_reg237;
    VOLATILE UINT32 nest_level_reg238;
    VOLATILE UINT32 nest_level_reg239;
    VOLATILE UINT32 nest_level_reg240;
    VOLATILE UINT32 nest_level_reg241;
    VOLATILE UINT32 nest_level_reg242;
    VOLATILE UINT32 nest_level_reg243;
    VOLATILE UINT32 nest_level_reg244;
    VOLATILE UINT32 nest_level_reg245;
    VOLATILE UINT32 nest_level_reg246;
    VOLATILE UINT32 nest_level_reg247;
    VOLATILE UINT32 nest_level_reg248;
    VOLATILE UINT32 nest_level_reg249;
    VOLATILE UINT32 nest_level_reg250;
    VOLATILE UINT32 nest_level_reg251;
    VOLATILE UINT32 nest_level_reg252;
    VOLATILE UINT32 nest_level_reg253;
    VOLATILE UINT32 nest_level_reg254;
    VOLATILE UINT32 nest_level_reg255;
#else
    VOLATILE UINT32 nest_level_reg[256];
#endif
#ifdef CSL_MODIFICATION    
    VOLATILE UINT32 enable_hint_reg0;
    VOLATILE UINT32 enable_hint_reg1;
    VOLATILE UINT32 enable_hint_reg2;
    VOLATILE UINT32 enable_hint_reg3;
    VOLATILE UINT32 enable_hint_reg4;
    VOLATILE UINT32 enable_hint_reg5;
    VOLATILE UINT32 enable_hint_reg6;
    VOLATILE UINT32 enable_hint_reg7;
#else
    VOLATILE UINT32 enable_hint_reg[8];			/*Host Interrupt Enable Registers*/
#endif    
    VOLATILE UINT8 Rsvd8[2784];
#ifdef CSL_MODIFICATION   
    VOLATILE UINT32 vector_address_reg_0;
    VOLATILE UINT32 vector_address_reg_1;
    VOLATILE UINT32 vector_address_reg_2;
    VOLATILE UINT32 vector_address_reg_3;
    VOLATILE UINT32 vector_address_reg_4;
    VOLATILE UINT32 vector_address_reg_5;
    VOLATILE UINT32 vector_address_reg_6;
    VOLATILE UINT32 vector_address_reg_7;
    VOLATILE UINT32 vector_address_reg_8;
    VOLATILE UINT32 vector_address_reg_9;
    VOLATILE UINT32 vector_address_reg_10;
    VOLATILE UINT32 vector_address_reg_11;
    VOLATILE UINT32 vector_address_reg_12;
    VOLATILE UINT32 vector_address_reg_13;
    VOLATILE UINT32 vector_address_reg_14;
    VOLATILE UINT32 vector_address_reg_15;
    VOLATILE UINT32 vector_address_reg_16;
    VOLATILE UINT32 vector_address_reg_17;
    VOLATILE UINT32 vector_address_reg_18;
    VOLATILE UINT32 vector_address_reg_19;
    VOLATILE UINT32 vector_address_reg_20;
    VOLATILE UINT32 vector_address_reg_21;
    VOLATILE UINT32 vector_address_reg_22;
    VOLATILE UINT32 vector_address_reg_23;
    VOLATILE UINT32 vector_address_reg_24;
    VOLATILE UINT32 vector_address_reg_25;
    VOLATILE UINT32 vector_address_reg_26;
    VOLATILE UINT32 vector_address_reg_27;
    VOLATILE UINT32 vector_address_reg_28;
    VOLATILE UINT32 vector_address_reg_29;
    VOLATILE UINT32 vector_address_reg_30;
    VOLATILE UINT32 vector_address_reg_31;
    VOLATILE UINT32 vector_address_reg_32;
    VOLATILE UINT32 vector_address_reg_33;
    VOLATILE UINT32 vector_address_reg_34;
    VOLATILE UINT32 vector_address_reg_35;
    VOLATILE UINT32 vector_address_reg_36;
    VOLATILE UINT32 vector_address_reg_37;
    VOLATILE UINT32 vector_address_reg_38;
    VOLATILE UINT32 vector_address_reg_39;
    VOLATILE UINT32 vector_address_reg_40;
    VOLATILE UINT32 vector_address_reg_41;
    VOLATILE UINT32 vector_address_reg_42;
    VOLATILE UINT32 vector_address_reg_43;
    VOLATILE UINT32 vector_address_reg_44;
    VOLATILE UINT32 vector_address_reg_45;
    VOLATILE UINT32 vector_address_reg_46;
    VOLATILE UINT32 vector_address_reg_47;
    VOLATILE UINT32 vector_address_reg_48;
    VOLATILE UINT32 vector_address_reg_49;
    VOLATILE UINT32 vector_address_reg_50;
    VOLATILE UINT32 vector_address_reg_51;
    VOLATILE UINT32 vector_address_reg_52;
    VOLATILE UINT32 vector_address_reg_53;
    VOLATILE UINT32 vector_address_reg_54;
    VOLATILE UINT32 vector_address_reg_55;
    VOLATILE UINT32 vector_address_reg_56;
    VOLATILE UINT32 vector_address_reg_57;
    VOLATILE UINT32 vector_address_reg_58;
    VOLATILE UINT32 vector_address_reg_59;
    VOLATILE UINT32 vector_address_reg_60;
    VOLATILE UINT32 vector_address_reg_61;
    VOLATILE UINT32 vector_address_reg_62;
    VOLATILE UINT32 vector_address_reg_63;
    VOLATILE UINT32 vector_address_reg_64;
    VOLATILE UINT32 vector_address_reg_65;
    VOLATILE UINT32 vector_address_reg_66;
    VOLATILE UINT32 vector_address_reg_67;
    VOLATILE UINT32 vector_address_reg_68;
    VOLATILE UINT32 vector_address_reg_69;
    VOLATILE UINT32 vector_address_reg_70;
    VOLATILE UINT32 vector_address_reg_71;
    VOLATILE UINT32 vector_address_reg_72;
    VOLATILE UINT32 vector_address_reg_73;
    VOLATILE UINT32 vector_address_reg_74;
    VOLATILE UINT32 vector_address_reg_75;
    VOLATILE UINT32 vector_address_reg_76;
    VOLATILE UINT32 vector_address_reg_77;
    VOLATILE UINT32 vector_address_reg_78;
    VOLATILE UINT32 vector_address_reg_79;
    VOLATILE UINT32 vector_address_reg_80;
    VOLATILE UINT32 vector_address_reg_81;
    VOLATILE UINT32 vector_address_reg_82;
    VOLATILE UINT32 vector_address_reg_83;
    VOLATILE UINT32 vector_address_reg_84;
    VOLATILE UINT32 vector_address_reg_85;
    VOLATILE UINT32 vector_address_reg_86;
    VOLATILE UINT32 vector_address_reg_87;
    VOLATILE UINT32 vector_address_reg_88;
    VOLATILE UINT32 vector_address_reg_89;
    VOLATILE UINT32 vector_address_reg_90;
    VOLATILE UINT32 vector_address_reg_91;
    VOLATILE UINT32 vector_address_reg_92;
    VOLATILE UINT32 vector_address_reg_93;
    VOLATILE UINT32 vector_address_reg_94;
    VOLATILE UINT32 vector_address_reg_95;
    VOLATILE UINT32 vector_address_reg_96;
    VOLATILE UINT32 vector_address_reg_97;
    VOLATILE UINT32 vector_address_reg_98;
    VOLATILE UINT32 vector_address_reg_99;
    VOLATILE UINT32 vector_address_reg_100;
    VOLATILE UINT32 vector_address_reg_101;
    VOLATILE UINT32 vector_address_reg_102;
    VOLATILE UINT32 vector_address_reg_103;
    VOLATILE UINT32 vector_address_reg_104;
    VOLATILE UINT32 vector_address_reg_105;
    VOLATILE UINT32 vector_address_reg_106;
    VOLATILE UINT32 vector_address_reg_107;
    VOLATILE UINT32 vector_address_reg_108;
    VOLATILE UINT32 vector_address_reg_109;
    VOLATILE UINT32 vector_address_reg_110;
    VOLATILE UINT32 vector_address_reg_111;
    VOLATILE UINT32 vector_address_reg_112;
    VOLATILE UINT32 vector_address_reg_113;
    VOLATILE UINT32 vector_address_reg_114;
    VOLATILE UINT32 vector_address_reg_115;
    VOLATILE UINT32 vector_address_reg_116;
    VOLATILE UINT32 vector_address_reg_117;
    VOLATILE UINT32 vector_address_reg_118;
    VOLATILE UINT32 vector_address_reg_119;
    VOLATILE UINT32 vector_address_reg_120;
    VOLATILE UINT32 vector_address_reg_121;
    VOLATILE UINT32 vector_address_reg_122;
    VOLATILE UINT32 vector_address_reg_123;
    VOLATILE UINT32 vector_address_reg_124;
    VOLATILE UINT32 vector_address_reg_125;
    VOLATILE UINT32 vector_address_reg_126;
    VOLATILE UINT32 vector_address_reg_127;
    VOLATILE UINT32 vector_address_reg_128;
    VOLATILE UINT32 vector_address_reg_129;
    VOLATILE UINT32 vector_address_reg_130;
    VOLATILE UINT32 vector_address_reg_131;
    VOLATILE UINT32 vector_address_reg_132;
    VOLATILE UINT32 vector_address_reg_133;
    VOLATILE UINT32 vector_address_reg_134;
    VOLATILE UINT32 vector_address_reg_135;
    VOLATILE UINT32 vector_address_reg_136;
    VOLATILE UINT32 vector_address_reg_137;
    VOLATILE UINT32 vector_address_reg_138;
    VOLATILE UINT32 vector_address_reg_139;
    VOLATILE UINT32 vector_address_reg_140;
    VOLATILE UINT32 vector_address_reg_141;
    VOLATILE UINT32 vector_address_reg_142;
    VOLATILE UINT32 vector_address_reg_143;
    VOLATILE UINT32 vector_address_reg_144;
    VOLATILE UINT32 vector_address_reg_145;
    VOLATILE UINT32 vector_address_reg_146;
    VOLATILE UINT32 vector_address_reg_147;
    VOLATILE UINT32 vector_address_reg_148;
    VOLATILE UINT32 vector_address_reg_149;
    VOLATILE UINT32 vector_address_reg_150;
    VOLATILE UINT32 vector_address_reg_151;
    VOLATILE UINT32 vector_address_reg_152;
    VOLATILE UINT32 vector_address_reg_153;
    VOLATILE UINT32 vector_address_reg_154;
    VOLATILE UINT32 vector_address_reg_155;
    VOLATILE UINT32 vector_address_reg_156;
    VOLATILE UINT32 vector_address_reg_157;
    VOLATILE UINT32 vector_address_reg_158;
    VOLATILE UINT32 vector_address_reg_159;
    VOLATILE UINT32 vector_address_reg_160;
    VOLATILE UINT32 vector_address_reg_161;
    VOLATILE UINT32 vector_address_reg_162;
    VOLATILE UINT32 vector_address_reg_163;
    VOLATILE UINT32 vector_address_reg_164;
    VOLATILE UINT32 vector_address_reg_165;
    VOLATILE UINT32 vector_address_reg_166;
    VOLATILE UINT32 vector_address_reg_167;
    VOLATILE UINT32 vector_address_reg_168;
    VOLATILE UINT32 vector_address_reg_169;
    VOLATILE UINT32 vector_address_reg_170;
    VOLATILE UINT32 vector_address_reg_171;
    VOLATILE UINT32 vector_address_reg_172;
    VOLATILE UINT32 vector_address_reg_173;
    VOLATILE UINT32 vector_address_reg_174;
    VOLATILE UINT32 vector_address_reg_175;
    VOLATILE UINT32 vector_address_reg_176;
    VOLATILE UINT32 vector_address_reg_177;
    VOLATILE UINT32 vector_address_reg_178;
    VOLATILE UINT32 vector_address_reg_179;
    VOLATILE UINT32 vector_address_reg_180;
    VOLATILE UINT32 vector_address_reg_181;
    VOLATILE UINT32 vector_address_reg_182;
    VOLATILE UINT32 vector_address_reg_183;
    VOLATILE UINT32 vector_address_reg_184;
    VOLATILE UINT32 vector_address_reg_185;
    VOLATILE UINT32 vector_address_reg_186;
    VOLATILE UINT32 vector_address_reg_187;
    VOLATILE UINT32 vector_address_reg_188;
    VOLATILE UINT32 vector_address_reg_189;
    VOLATILE UINT32 vector_address_reg_190;
    VOLATILE UINT32 vector_address_reg_191;
    VOLATILE UINT32 vector_address_reg_192;
    VOLATILE UINT32 vector_address_reg_193;
    VOLATILE UINT32 vector_address_reg_194;
    VOLATILE UINT32 vector_address_reg_195;
    VOLATILE UINT32 vector_address_reg_196;
    VOLATILE UINT32 vector_address_reg_197;
    VOLATILE UINT32 vector_address_reg_198;
    VOLATILE UINT32 vector_address_reg_199;
    VOLATILE UINT32 vector_address_reg_200;
    VOLATILE UINT32 vector_address_reg_201;
    VOLATILE UINT32 vector_address_reg_202;
    VOLATILE UINT32 vector_address_reg_203;
    VOLATILE UINT32 vector_address_reg_204;
    VOLATILE UINT32 vector_address_reg_205;
    VOLATILE UINT32 vector_address_reg_206;
    VOLATILE UINT32 vector_address_reg_207;
    VOLATILE UINT32 vector_address_reg_208;
    VOLATILE UINT32 vector_address_reg_209;
    VOLATILE UINT32 vector_address_reg_210;
    VOLATILE UINT32 vector_address_reg_211;
    VOLATILE UINT32 vector_address_reg_212;
    VOLATILE UINT32 vector_address_reg_213;
    VOLATILE UINT32 vector_address_reg_214;
    VOLATILE UINT32 vector_address_reg_215;
    VOLATILE UINT32 vector_address_reg_216;
    VOLATILE UINT32 vector_address_reg_217;
    VOLATILE UINT32 vector_address_reg_218;
    VOLATILE UINT32 vector_address_reg_219;
    VOLATILE UINT32 vector_address_reg_220;
    VOLATILE UINT32 vector_address_reg_221;
    VOLATILE UINT32 vector_address_reg_222;
    VOLATILE UINT32 vector_address_reg_223;
    VOLATILE UINT32 vector_address_reg_224;
    VOLATILE UINT32 vector_address_reg_225;
    VOLATILE UINT32 vector_address_reg_226;
    VOLATILE UINT32 vector_address_reg_227;
    VOLATILE UINT32 vector_address_reg_228;
    VOLATILE UINT32 vector_address_reg_229;
    VOLATILE UINT32 vector_address_reg_230;
    VOLATILE UINT32 vector_address_reg_231;
    VOLATILE UINT32 vector_address_reg_232;
    VOLATILE UINT32 vector_address_reg_233;
    VOLATILE UINT32 vector_address_reg_234;
    VOLATILE UINT32 vector_address_reg_235;
    VOLATILE UINT32 vector_address_reg_236;
    VOLATILE UINT32 vector_address_reg_237;
    VOLATILE UINT32 vector_address_reg_238;
    VOLATILE UINT32 vector_address_reg_239;
    VOLATILE UINT32 vector_address_reg_240;
    VOLATILE UINT32 vector_address_reg_241;
    VOLATILE UINT32 vector_address_reg_242;
    VOLATILE UINT32 vector_address_reg_243;
    VOLATILE UINT32 vector_address_reg_244;
    VOLATILE UINT32 vector_address_reg_245;
    VOLATILE UINT32 vector_address_reg_246;
    VOLATILE UINT32 vector_address_reg_247;
    VOLATILE UINT32 vector_address_reg_248;
    VOLATILE UINT32 vector_address_reg_249;
    VOLATILE UINT32 vector_address_reg_250;
    VOLATILE UINT32 vector_address_reg_251;
    VOLATILE UINT32 vector_address_reg_252;
    VOLATILE UINT32 vector_address_reg_253;
    VOLATILE UINT32 vector_address_reg_254;
    VOLATILE UINT32 vector_address_reg_255;
    VOLATILE UINT32 vector_address_reg_256;
    VOLATILE UINT32 vector_address_reg_257;
    VOLATILE UINT32 vector_address_reg_258;
    VOLATILE UINT32 vector_address_reg_259;
    VOLATILE UINT32 vector_address_reg_260;
    VOLATILE UINT32 vector_address_reg_261;
    VOLATILE UINT32 vector_address_reg_262;
    VOLATILE UINT32 vector_address_reg_263;
    VOLATILE UINT32 vector_address_reg_264;
    VOLATILE UINT32 vector_address_reg_265;
    VOLATILE UINT32 vector_address_reg_266;
    VOLATILE UINT32 vector_address_reg_267;
    VOLATILE UINT32 vector_address_reg_268;
    VOLATILE UINT32 vector_address_reg_269;
    VOLATILE UINT32 vector_address_reg_270;
    VOLATILE UINT32 vector_address_reg_271;
    VOLATILE UINT32 vector_address_reg_272;
    VOLATILE UINT32 vector_address_reg_273;
    VOLATILE UINT32 vector_address_reg_274;
    VOLATILE UINT32 vector_address_reg_275;
    VOLATILE UINT32 vector_address_reg_276;
    VOLATILE UINT32 vector_address_reg_277;
    VOLATILE UINT32 vector_address_reg_278;
    VOLATILE UINT32 vector_address_reg_279;
    VOLATILE UINT32 vector_address_reg_280;
    VOLATILE UINT32 vector_address_reg_281;
    VOLATILE UINT32 vector_address_reg_282;
    VOLATILE UINT32 vector_address_reg_283;
    VOLATILE UINT32 vector_address_reg_284;
    VOLATILE UINT32 vector_address_reg_285;
    VOLATILE UINT32 vector_address_reg_286;
    VOLATILE UINT32 vector_address_reg_287;
    VOLATILE UINT32 vector_address_reg_288;
    VOLATILE UINT32 vector_address_reg_289;
    VOLATILE UINT32 vector_address_reg_290;
    VOLATILE UINT32 vector_address_reg_291;
    VOLATILE UINT32 vector_address_reg_292;
    VOLATILE UINT32 vector_address_reg_293;
    VOLATILE UINT32 vector_address_reg_294;
    VOLATILE UINT32 vector_address_reg_295;
    VOLATILE UINT32 vector_address_reg_296;
    VOLATILE UINT32 vector_address_reg_297;
    VOLATILE UINT32 vector_address_reg_298;
    VOLATILE UINT32 vector_address_reg_299;
    VOLATILE UINT32 vector_address_reg_300;
    VOLATILE UINT32 vector_address_reg_301;
    VOLATILE UINT32 vector_address_reg_302;
    VOLATILE UINT32 vector_address_reg_303;
    VOLATILE UINT32 vector_address_reg_304;
    VOLATILE UINT32 vector_address_reg_305;
    VOLATILE UINT32 vector_address_reg_306;
    VOLATILE UINT32 vector_address_reg_307;
    VOLATILE UINT32 vector_address_reg_308;
    VOLATILE UINT32 vector_address_reg_309;
    VOLATILE UINT32 vector_address_reg_310;
    VOLATILE UINT32 vector_address_reg_311;
    VOLATILE UINT32 vector_address_reg_312;
    VOLATILE UINT32 vector_address_reg_313;
    VOLATILE UINT32 vector_address_reg_314;
    VOLATILE UINT32 vector_address_reg_315;
    VOLATILE UINT32 vector_address_reg_316;
    VOLATILE UINT32 vector_address_reg_317;
    VOLATILE UINT32 vector_address_reg_318;
    VOLATILE UINT32 vector_address_reg_319;
    VOLATILE UINT32 vector_address_reg_320;
    VOLATILE UINT32 vector_address_reg_321;
    VOLATILE UINT32 vector_address_reg_322;
    VOLATILE UINT32 vector_address_reg_323;
    VOLATILE UINT32 vector_address_reg_324;
    VOLATILE UINT32 vector_address_reg_325;
    VOLATILE UINT32 vector_address_reg_326;
    VOLATILE UINT32 vector_address_reg_327;
    VOLATILE UINT32 vector_address_reg_328;
    VOLATILE UINT32 vector_address_reg_329;
    VOLATILE UINT32 vector_address_reg_330;
    VOLATILE UINT32 vector_address_reg_331;
    VOLATILE UINT32 vector_address_reg_332;
    VOLATILE UINT32 vector_address_reg_333;
    VOLATILE UINT32 vector_address_reg_334;
    VOLATILE UINT32 vector_address_reg_335;
    VOLATILE UINT32 vector_address_reg_336;
    VOLATILE UINT32 vector_address_reg_337;
    VOLATILE UINT32 vector_address_reg_338;
    VOLATILE UINT32 vector_address_reg_339;
    VOLATILE UINT32 vector_address_reg_340;
    VOLATILE UINT32 vector_address_reg_341;
    VOLATILE UINT32 vector_address_reg_342;
    VOLATILE UINT32 vector_address_reg_343;
    VOLATILE UINT32 vector_address_reg_344;
    VOLATILE UINT32 vector_address_reg_345;
    VOLATILE UINT32 vector_address_reg_346;
    VOLATILE UINT32 vector_address_reg_347;
    VOLATILE UINT32 vector_address_reg_348;
    VOLATILE UINT32 vector_address_reg_349;
    VOLATILE UINT32 vector_address_reg_350;
    VOLATILE UINT32 vector_address_reg_351;
    VOLATILE UINT32 vector_address_reg_352;
    VOLATILE UINT32 vector_address_reg_353;
    VOLATILE UINT32 vector_address_reg_354;
    VOLATILE UINT32 vector_address_reg_355;
    VOLATILE UINT32 vector_address_reg_356;
    VOLATILE UINT32 vector_address_reg_357;
    VOLATILE UINT32 vector_address_reg_358;
    VOLATILE UINT32 vector_address_reg_359;
    VOLATILE UINT32 vector_address_reg_360;
    VOLATILE UINT32 vector_address_reg_361;
    VOLATILE UINT32 vector_address_reg_362;
    VOLATILE UINT32 vector_address_reg_363;
    VOLATILE UINT32 vector_address_reg_364;
    VOLATILE UINT32 vector_address_reg_365;
    VOLATILE UINT32 vector_address_reg_366;
    VOLATILE UINT32 vector_address_reg_367;
    VOLATILE UINT32 vector_address_reg_368;
    VOLATILE UINT32 vector_address_reg_369;
    VOLATILE UINT32 vector_address_reg_370;
    VOLATILE UINT32 vector_address_reg_371;
    VOLATILE UINT32 vector_address_reg_372;
    VOLATILE UINT32 vector_address_reg_373;
    VOLATILE UINT32 vector_address_reg_374;
    VOLATILE UINT32 vector_address_reg_375;
    VOLATILE UINT32 vector_address_reg_376;
    VOLATILE UINT32 vector_address_reg_377;
    VOLATILE UINT32 vector_address_reg_378;
    VOLATILE UINT32 vector_address_reg_379;
    VOLATILE UINT32 vector_address_reg_380;
    VOLATILE UINT32 vector_address_reg_381;
    VOLATILE UINT32 vector_address_reg_382;
    VOLATILE UINT32 vector_address_reg_383;
    VOLATILE UINT32 vector_address_reg_384;
    VOLATILE UINT32 vector_address_reg_385;
    VOLATILE UINT32 vector_address_reg_386;
    VOLATILE UINT32 vector_address_reg_387;
    VOLATILE UINT32 vector_address_reg_388;
    VOLATILE UINT32 vector_address_reg_389;
    VOLATILE UINT32 vector_address_reg_390;
    VOLATILE UINT32 vector_address_reg_391;
    VOLATILE UINT32 vector_address_reg_392;
    VOLATILE UINT32 vector_address_reg_393;
    VOLATILE UINT32 vector_address_reg_394;
    VOLATILE UINT32 vector_address_reg_395;
    VOLATILE UINT32 vector_address_reg_396;
    VOLATILE UINT32 vector_address_reg_397;
    VOLATILE UINT32 vector_address_reg_398;
    VOLATILE UINT32 vector_address_reg_399;
    VOLATILE UINT32 vector_address_reg_400;
    VOLATILE UINT32 vector_address_reg_401;
    VOLATILE UINT32 vector_address_reg_402;
    VOLATILE UINT32 vector_address_reg_403;
    VOLATILE UINT32 vector_address_reg_404;
    VOLATILE UINT32 vector_address_reg_405;
    VOLATILE UINT32 vector_address_reg_406;
    VOLATILE UINT32 vector_address_reg_407;
    VOLATILE UINT32 vector_address_reg_408;
    VOLATILE UINT32 vector_address_reg_409;
    VOLATILE UINT32 vector_address_reg_410;
    VOLATILE UINT32 vector_address_reg_411;
    VOLATILE UINT32 vector_address_reg_412;
    VOLATILE UINT32 vector_address_reg_413;
    VOLATILE UINT32 vector_address_reg_414;
    VOLATILE UINT32 vector_address_reg_415;
    VOLATILE UINT32 vector_address_reg_416;
    VOLATILE UINT32 vector_address_reg_417;
    VOLATILE UINT32 vector_address_reg_418;
    VOLATILE UINT32 vector_address_reg_419;
    VOLATILE UINT32 vector_address_reg_420;
    VOLATILE UINT32 vector_address_reg_421;
    VOLATILE UINT32 vector_address_reg_422;
    VOLATILE UINT32 vector_address_reg_423;
    VOLATILE UINT32 vector_address_reg_424;
    VOLATILE UINT32 vector_address_reg_425;
    VOLATILE UINT32 vector_address_reg_426;
    VOLATILE UINT32 vector_address_reg_427;
    VOLATILE UINT32 vector_address_reg_428;
    VOLATILE UINT32 vector_address_reg_429;
    VOLATILE UINT32 vector_address_reg_430;
    VOLATILE UINT32 vector_address_reg_431;
    VOLATILE UINT32 vector_address_reg_432;
    VOLATILE UINT32 vector_address_reg_433;
    VOLATILE UINT32 vector_address_reg_434;
    VOLATILE UINT32 vector_address_reg_435;
    VOLATILE UINT32 vector_address_reg_436;
    VOLATILE UINT32 vector_address_reg_437;
    VOLATILE UINT32 vector_address_reg_438;
    VOLATILE UINT32 vector_address_reg_439;
    VOLATILE UINT32 vector_address_reg_440;
    VOLATILE UINT32 vector_address_reg_441;
    VOLATILE UINT32 vector_address_reg_442;
    VOLATILE UINT32 vector_address_reg_443;
    VOLATILE UINT32 vector_address_reg_444;
    VOLATILE UINT32 vector_address_reg_445;
    VOLATILE UINT32 vector_address_reg_446;
    VOLATILE UINT32 vector_address_reg_447;
    VOLATILE UINT32 vector_address_reg_448;
    VOLATILE UINT32 vector_address_reg_449;
    VOLATILE UINT32 vector_address_reg_450;
    VOLATILE UINT32 vector_address_reg_451;
    VOLATILE UINT32 vector_address_reg_452;
    VOLATILE UINT32 vector_address_reg_453;
    VOLATILE UINT32 vector_address_reg_454;
    VOLATILE UINT32 vector_address_reg_455;
    VOLATILE UINT32 vector_address_reg_456;
    VOLATILE UINT32 vector_address_reg_457;
    VOLATILE UINT32 vector_address_reg_458;
    VOLATILE UINT32 vector_address_reg_459;
    VOLATILE UINT32 vector_address_reg_460;
    VOLATILE UINT32 vector_address_reg_461;
    VOLATILE UINT32 vector_address_reg_462;
    VOLATILE UINT32 vector_address_reg_463;
    VOLATILE UINT32 vector_address_reg_464;
    VOLATILE UINT32 vector_address_reg_465;
    VOLATILE UINT32 vector_address_reg_466;
    VOLATILE UINT32 vector_address_reg_467;
    VOLATILE UINT32 vector_address_reg_468;
    VOLATILE UINT32 vector_address_reg_469;
    VOLATILE UINT32 vector_address_reg_470;
    VOLATILE UINT32 vector_address_reg_471;
    VOLATILE UINT32 vector_address_reg_472;
    VOLATILE UINT32 vector_address_reg_473;
    VOLATILE UINT32 vector_address_reg_474;
    VOLATILE UINT32 vector_address_reg_475;
    VOLATILE UINT32 vector_address_reg_476;
    VOLATILE UINT32 vector_address_reg_477;
    VOLATILE UINT32 vector_address_reg_478;
    VOLATILE UINT32 vector_address_reg_479;
    VOLATILE UINT32 vector_address_reg_480;
    VOLATILE UINT32 vector_address_reg_481;
    VOLATILE UINT32 vector_address_reg_482;
    VOLATILE UINT32 vector_address_reg_483;
    VOLATILE UINT32 vector_address_reg_484;
    VOLATILE UINT32 vector_address_reg_485;
    VOLATILE UINT32 vector_address_reg_486;
    VOLATILE UINT32 vector_address_reg_487;
    VOLATILE UINT32 vector_address_reg_488;
    VOLATILE UINT32 vector_address_reg_489;
    VOLATILE UINT32 vector_address_reg_490;
    VOLATILE UINT32 vector_address_reg_491;
    VOLATILE UINT32 vector_address_reg_492;
    VOLATILE UINT32 vector_address_reg_493;
    VOLATILE UINT32 vector_address_reg_494;
    VOLATILE UINT32 vector_address_reg_495;
    VOLATILE UINT32 vector_address_reg_496;
    VOLATILE UINT32 vector_address_reg_497;
    VOLATILE UINT32 vector_address_reg_498;
    VOLATILE UINT32 vector_address_reg_499;
    VOLATILE UINT32 vector_address_reg_500;
    VOLATILE UINT32 vector_address_reg_501;
    VOLATILE UINT32 vector_address_reg_502;
    VOLATILE UINT32 vector_address_reg_503;
    VOLATILE UINT32 vector_address_reg_504;
    VOLATILE UINT32 vector_address_reg_505;
    VOLATILE UINT32 vector_address_reg_506;
    VOLATILE UINT32 vector_address_reg_507;
    VOLATILE UINT32 vector_address_reg_508;
    VOLATILE UINT32 vector_address_reg_509;
    VOLATILE UINT32 vector_address_reg_510;
    VOLATILE UINT32 vector_address_reg_511;
    VOLATILE UINT32 vector_address_reg_512;
    VOLATILE UINT32 vector_address_reg_513;
    VOLATILE UINT32 vector_address_reg_514;
    VOLATILE UINT32 vector_address_reg_515;
    VOLATILE UINT32 vector_address_reg_516;
    VOLATILE UINT32 vector_address_reg_517;
    VOLATILE UINT32 vector_address_reg_518;
    VOLATILE UINT32 vector_address_reg_519;
    VOLATILE UINT32 vector_address_reg_520;
    VOLATILE UINT32 vector_address_reg_521;
    VOLATILE UINT32 vector_address_reg_522;
    VOLATILE UINT32 vector_address_reg_523;
    VOLATILE UINT32 vector_address_reg_524;
    VOLATILE UINT32 vector_address_reg_525;
    VOLATILE UINT32 vector_address_reg_526;
    VOLATILE UINT32 vector_address_reg_527;
    VOLATILE UINT32 vector_address_reg_528;
    VOLATILE UINT32 vector_address_reg_529;
    VOLATILE UINT32 vector_address_reg_530;
    VOLATILE UINT32 vector_address_reg_531;
    VOLATILE UINT32 vector_address_reg_532;
    VOLATILE UINT32 vector_address_reg_533;
    VOLATILE UINT32 vector_address_reg_534;
    VOLATILE UINT32 vector_address_reg_535;
    VOLATILE UINT32 vector_address_reg_536;
    VOLATILE UINT32 vector_address_reg_537;
    VOLATILE UINT32 vector_address_reg_538;
    VOLATILE UINT32 vector_address_reg_539;
    VOLATILE UINT32 vector_address_reg_540;
    VOLATILE UINT32 vector_address_reg_541;
    VOLATILE UINT32 vector_address_reg_542;
    VOLATILE UINT32 vector_address_reg_543;
    VOLATILE UINT32 vector_address_reg_544;
    VOLATILE UINT32 vector_address_reg_545;
    VOLATILE UINT32 vector_address_reg_546;
    VOLATILE UINT32 vector_address_reg_547;
    VOLATILE UINT32 vector_address_reg_548;
    VOLATILE UINT32 vector_address_reg_549;
    VOLATILE UINT32 vector_address_reg_550;
    VOLATILE UINT32 vector_address_reg_551;
    VOLATILE UINT32 vector_address_reg_552;
    VOLATILE UINT32 vector_address_reg_553;
    VOLATILE UINT32 vector_address_reg_554;
    VOLATILE UINT32 vector_address_reg_555;
    VOLATILE UINT32 vector_address_reg_556;
    VOLATILE UINT32 vector_address_reg_557;
    VOLATILE UINT32 vector_address_reg_558;
    VOLATILE UINT32 vector_address_reg_559;
    VOLATILE UINT32 vector_address_reg_560;
    VOLATILE UINT32 vector_address_reg_561;
    VOLATILE UINT32 vector_address_reg_562;
    VOLATILE UINT32 vector_address_reg_563;
    VOLATILE UINT32 vector_address_reg_564;
    VOLATILE UINT32 vector_address_reg_565;
    VOLATILE UINT32 vector_address_reg_566;
    VOLATILE UINT32 vector_address_reg_567;
    VOLATILE UINT32 vector_address_reg_568;
    VOLATILE UINT32 vector_address_reg_569;
    VOLATILE UINT32 vector_address_reg_570;
    VOLATILE UINT32 vector_address_reg_571;
    VOLATILE UINT32 vector_address_reg_572;
    VOLATILE UINT32 vector_address_reg_573;
    VOLATILE UINT32 vector_address_reg_574;
    VOLATILE UINT32 vector_address_reg_575;
    VOLATILE UINT32 vector_address_reg_576;
    VOLATILE UINT32 vector_address_reg_577;
    VOLATILE UINT32 vector_address_reg_578;
    VOLATILE UINT32 vector_address_reg_579;
    VOLATILE UINT32 vector_address_reg_580;
    VOLATILE UINT32 vector_address_reg_581;
    VOLATILE UINT32 vector_address_reg_582;
    VOLATILE UINT32 vector_address_reg_583;
    VOLATILE UINT32 vector_address_reg_584;
    VOLATILE UINT32 vector_address_reg_585;
    VOLATILE UINT32 vector_address_reg_586;
    VOLATILE UINT32 vector_address_reg_587;
    VOLATILE UINT32 vector_address_reg_588;
    VOLATILE UINT32 vector_address_reg_589;
    VOLATILE UINT32 vector_address_reg_590;
    VOLATILE UINT32 vector_address_reg_591;
    VOLATILE UINT32 vector_address_reg_592;
    VOLATILE UINT32 vector_address_reg_593;
    VOLATILE UINT32 vector_address_reg_594;
    VOLATILE UINT32 vector_address_reg_595;
    VOLATILE UINT32 vector_address_reg_596;
    VOLATILE UINT32 vector_address_reg_597;
    VOLATILE UINT32 vector_address_reg_598;
    VOLATILE UINT32 vector_address_reg_599;
    VOLATILE UINT32 vector_address_reg_600;
    VOLATILE UINT32 vector_address_reg_601;
    VOLATILE UINT32 vector_address_reg_602;
    VOLATILE UINT32 vector_address_reg_603;
    VOLATILE UINT32 vector_address_reg_604;
    VOLATILE UINT32 vector_address_reg_605;
    VOLATILE UINT32 vector_address_reg_606;
    VOLATILE UINT32 vector_address_reg_607;
    VOLATILE UINT32 vector_address_reg_608;
    VOLATILE UINT32 vector_address_reg_609;
    VOLATILE UINT32 vector_address_reg_610;
    VOLATILE UINT32 vector_address_reg_611;
    VOLATILE UINT32 vector_address_reg_612;
    VOLATILE UINT32 vector_address_reg_613;
    VOLATILE UINT32 vector_address_reg_614;
    VOLATILE UINT32 vector_address_reg_615;
    VOLATILE UINT32 vector_address_reg_616;
    VOLATILE UINT32 vector_address_reg_617;
    VOLATILE UINT32 vector_address_reg_618;
    VOLATILE UINT32 vector_address_reg_619;
    VOLATILE UINT32 vector_address_reg_620;
    VOLATILE UINT32 vector_address_reg_621;
    VOLATILE UINT32 vector_address_reg_622;
    VOLATILE UINT32 vector_address_reg_623;
    VOLATILE UINT32 vector_address_reg_624;
    VOLATILE UINT32 vector_address_reg_625;
    VOLATILE UINT32 vector_address_reg_626;
    VOLATILE UINT32 vector_address_reg_627;
    VOLATILE UINT32 vector_address_reg_628;
    VOLATILE UINT32 vector_address_reg_629;
    VOLATILE UINT32 vector_address_reg_630;
    VOLATILE UINT32 vector_address_reg_631;
    VOLATILE UINT32 vector_address_reg_632;
    VOLATILE UINT32 vector_address_reg_633;
    VOLATILE UINT32 vector_address_reg_634;
    VOLATILE UINT32 vector_address_reg_635;
    VOLATILE UINT32 vector_address_reg_636;
    VOLATILE UINT32 vector_address_reg_637;
    VOLATILE UINT32 vector_address_reg_638;
    VOLATILE UINT32 vector_address_reg_639;
    VOLATILE UINT32 vector_address_reg_640;
    VOLATILE UINT32 vector_address_reg_641;
    VOLATILE UINT32 vector_address_reg_642;
    VOLATILE UINT32 vector_address_reg_643;
    VOLATILE UINT32 vector_address_reg_644;
    VOLATILE UINT32 vector_address_reg_645;
    VOLATILE UINT32 vector_address_reg_646;
    VOLATILE UINT32 vector_address_reg_647;
    VOLATILE UINT32 vector_address_reg_648;
    VOLATILE UINT32 vector_address_reg_649;
    VOLATILE UINT32 vector_address_reg_650;
    VOLATILE UINT32 vector_address_reg_651;
    VOLATILE UINT32 vector_address_reg_652;
    VOLATILE UINT32 vector_address_reg_653;
    VOLATILE UINT32 vector_address_reg_654;
    VOLATILE UINT32 vector_address_reg_655;
    VOLATILE UINT32 vector_address_reg_656;
    VOLATILE UINT32 vector_address_reg_657;
    VOLATILE UINT32 vector_address_reg_658;
    VOLATILE UINT32 vector_address_reg_659;
    VOLATILE UINT32 vector_address_reg_660;
    VOLATILE UINT32 vector_address_reg_661;
    VOLATILE UINT32 vector_address_reg_662;
    VOLATILE UINT32 vector_address_reg_663;
    VOLATILE UINT32 vector_address_reg_664;
    VOLATILE UINT32 vector_address_reg_665;
    VOLATILE UINT32 vector_address_reg_666;
    VOLATILE UINT32 vector_address_reg_667;
    VOLATILE UINT32 vector_address_reg_668;
    VOLATILE UINT32 vector_address_reg_669;
    VOLATILE UINT32 vector_address_reg_670;
    VOLATILE UINT32 vector_address_reg_671;
    VOLATILE UINT32 vector_address_reg_672;
    VOLATILE UINT32 vector_address_reg_673;
    VOLATILE UINT32 vector_address_reg_674;
    VOLATILE UINT32 vector_address_reg_675;
    VOLATILE UINT32 vector_address_reg_676;
    VOLATILE UINT32 vector_address_reg_677;
    VOLATILE UINT32 vector_address_reg_678;
    VOLATILE UINT32 vector_address_reg_679;
    VOLATILE UINT32 vector_address_reg_680;
    VOLATILE UINT32 vector_address_reg_681;
    VOLATILE UINT32 vector_address_reg_682;
    VOLATILE UINT32 vector_address_reg_683;
    VOLATILE UINT32 vector_address_reg_684;
    VOLATILE UINT32 vector_address_reg_685;
    VOLATILE UINT32 vector_address_reg_686;
    VOLATILE UINT32 vector_address_reg_687;
    VOLATILE UINT32 vector_address_reg_688;
    VOLATILE UINT32 vector_address_reg_689;
    VOLATILE UINT32 vector_address_reg_690;
    VOLATILE UINT32 vector_address_reg_691;
    VOLATILE UINT32 vector_address_reg_692;
    VOLATILE UINT32 vector_address_reg_693;
    VOLATILE UINT32 vector_address_reg_694;
    VOLATILE UINT32 vector_address_reg_695;
    VOLATILE UINT32 vector_address_reg_696;
    VOLATILE UINT32 vector_address_reg_697;
    VOLATILE UINT32 vector_address_reg_698;
    VOLATILE UINT32 vector_address_reg_699;
    VOLATILE UINT32 vector_address_reg_700;
    VOLATILE UINT32 vector_address_reg_701;
    VOLATILE UINT32 vector_address_reg_702;
    VOLATILE UINT32 vector_address_reg_703;
    VOLATILE UINT32 vector_address_reg_704;
    VOLATILE UINT32 vector_address_reg_705;
    VOLATILE UINT32 vector_address_reg_706;
    VOLATILE UINT32 vector_address_reg_707;
    VOLATILE UINT32 vector_address_reg_708;
    VOLATILE UINT32 vector_address_reg_709;
    VOLATILE UINT32 vector_address_reg_710;
    VOLATILE UINT32 vector_address_reg_711;
    VOLATILE UINT32 vector_address_reg_712;
    VOLATILE UINT32 vector_address_reg_713;
    VOLATILE UINT32 vector_address_reg_714;
    VOLATILE UINT32 vector_address_reg_715;
    VOLATILE UINT32 vector_address_reg_716;
    VOLATILE UINT32 vector_address_reg_717;
    VOLATILE UINT32 vector_address_reg_718;
    VOLATILE UINT32 vector_address_reg_719;
    VOLATILE UINT32 vector_address_reg_720;
    VOLATILE UINT32 vector_address_reg_721;
    VOLATILE UINT32 vector_address_reg_722;
    VOLATILE UINT32 vector_address_reg_723;
    VOLATILE UINT32 vector_address_reg_724;
    VOLATILE UINT32 vector_address_reg_725;
    VOLATILE UINT32 vector_address_reg_726;
    VOLATILE UINT32 vector_address_reg_727;
    VOLATILE UINT32 vector_address_reg_728;
    VOLATILE UINT32 vector_address_reg_729;
    VOLATILE UINT32 vector_address_reg_730;
    VOLATILE UINT32 vector_address_reg_731;
    VOLATILE UINT32 vector_address_reg_732;
    VOLATILE UINT32 vector_address_reg_733;
    VOLATILE UINT32 vector_address_reg_734;
    VOLATILE UINT32 vector_address_reg_735;
    VOLATILE UINT32 vector_address_reg_736;
    VOLATILE UINT32 vector_address_reg_737;
    VOLATILE UINT32 vector_address_reg_738;
    VOLATILE UINT32 vector_address_reg_739;
    VOLATILE UINT32 vector_address_reg_740;
    VOLATILE UINT32 vector_address_reg_741;
    VOLATILE UINT32 vector_address_reg_742;
    VOLATILE UINT32 vector_address_reg_743;
    VOLATILE UINT32 vector_address_reg_744;
    VOLATILE UINT32 vector_address_reg_745;
    VOLATILE UINT32 vector_address_reg_746;
    VOLATILE UINT32 vector_address_reg_747;
    VOLATILE UINT32 vector_address_reg_748;
    VOLATILE UINT32 vector_address_reg_749;
    VOLATILE UINT32 vector_address_reg_750;
    VOLATILE UINT32 vector_address_reg_751;
    VOLATILE UINT32 vector_address_reg_752;
    VOLATILE UINT32 vector_address_reg_753;
    VOLATILE UINT32 vector_address_reg_754;
    VOLATILE UINT32 vector_address_reg_755;
    VOLATILE UINT32 vector_address_reg_756;
    VOLATILE UINT32 vector_address_reg_757;
    VOLATILE UINT32 vector_address_reg_758;
    VOLATILE UINT32 vector_address_reg_759;
    VOLATILE UINT32 vector_address_reg_760;
    VOLATILE UINT32 vector_address_reg_761;
    VOLATILE UINT32 vector_address_reg_762;
    VOLATILE UINT32 vector_address_reg_763;
    VOLATILE UINT32 vector_address_reg_764;
    VOLATILE UINT32 vector_address_reg_765;
    VOLATILE UINT32 vector_address_reg_766;
    VOLATILE UINT32 vector_address_reg_767;
    VOLATILE UINT32 vector_address_reg_768;
    VOLATILE UINT32 vector_address_reg_769;
    VOLATILE UINT32 vector_address_reg_770;
    VOLATILE UINT32 vector_address_reg_771;
    VOLATILE UINT32 vector_address_reg_772;
    VOLATILE UINT32 vector_address_reg_773;
    VOLATILE UINT32 vector_address_reg_774;
    VOLATILE UINT32 vector_address_reg_775;
    VOLATILE UINT32 vector_address_reg_776;
    VOLATILE UINT32 vector_address_reg_777;
    VOLATILE UINT32 vector_address_reg_778;
    VOLATILE UINT32 vector_address_reg_779;
    VOLATILE UINT32 vector_address_reg_780;
    VOLATILE UINT32 vector_address_reg_781;
    VOLATILE UINT32 vector_address_reg_782;
    VOLATILE UINT32 vector_address_reg_783;
    VOLATILE UINT32 vector_address_reg_784;
    VOLATILE UINT32 vector_address_reg_785;
    VOLATILE UINT32 vector_address_reg_786;
    VOLATILE UINT32 vector_address_reg_787;
    VOLATILE UINT32 vector_address_reg_788;
    VOLATILE UINT32 vector_address_reg_789;
    VOLATILE UINT32 vector_address_reg_790;
    VOLATILE UINT32 vector_address_reg_791;
    VOLATILE UINT32 vector_address_reg_792;
    VOLATILE UINT32 vector_address_reg_793;
    VOLATILE UINT32 vector_address_reg_794;
    VOLATILE UINT32 vector_address_reg_795;
    VOLATILE UINT32 vector_address_reg_796;
    VOLATILE UINT32 vector_address_reg_797;
    VOLATILE UINT32 vector_address_reg_798;
    VOLATILE UINT32 vector_address_reg_799;
    VOLATILE UINT32 vector_address_reg_800;
    VOLATILE UINT32 vector_address_reg_801;
    VOLATILE UINT32 vector_address_reg_802;
    VOLATILE UINT32 vector_address_reg_803;
    VOLATILE UINT32 vector_address_reg_804;
    VOLATILE UINT32 vector_address_reg_805;
    VOLATILE UINT32 vector_address_reg_806;
    VOLATILE UINT32 vector_address_reg_807;
    VOLATILE UINT32 vector_address_reg_808;
    VOLATILE UINT32 vector_address_reg_809;
    VOLATILE UINT32 vector_address_reg_810;
    VOLATILE UINT32 vector_address_reg_811;
    VOLATILE UINT32 vector_address_reg_812;
    VOLATILE UINT32 vector_address_reg_813;
    VOLATILE UINT32 vector_address_reg_814;
    VOLATILE UINT32 vector_address_reg_815;
    VOLATILE UINT32 vector_address_reg_816;
    VOLATILE UINT32 vector_address_reg_817;
    VOLATILE UINT32 vector_address_reg_818;
    VOLATILE UINT32 vector_address_reg_819;
    VOLATILE UINT32 vector_address_reg_820;
    VOLATILE UINT32 vector_address_reg_821;
    VOLATILE UINT32 vector_address_reg_822;
    VOLATILE UINT32 vector_address_reg_823;
    VOLATILE UINT32 vector_address_reg_824;
    VOLATILE UINT32 vector_address_reg_825;
    VOLATILE UINT32 vector_address_reg_826;
    VOLATILE UINT32 vector_address_reg_827;
    VOLATILE UINT32 vector_address_reg_828;
    VOLATILE UINT32 vector_address_reg_829;
    VOLATILE UINT32 vector_address_reg_830;
    VOLATILE UINT32 vector_address_reg_831;
    VOLATILE UINT32 vector_address_reg_832;
    VOLATILE UINT32 vector_address_reg_833;
    VOLATILE UINT32 vector_address_reg_834;
    VOLATILE UINT32 vector_address_reg_835;
    VOLATILE UINT32 vector_address_reg_836;
    VOLATILE UINT32 vector_address_reg_837;
    VOLATILE UINT32 vector_address_reg_838;
    VOLATILE UINT32 vector_address_reg_839;
    VOLATILE UINT32 vector_address_reg_840;
    VOLATILE UINT32 vector_address_reg_841;
    VOLATILE UINT32 vector_address_reg_842;
    VOLATILE UINT32 vector_address_reg_843;
    VOLATILE UINT32 vector_address_reg_844;
    VOLATILE UINT32 vector_address_reg_845;
    VOLATILE UINT32 vector_address_reg_846;
    VOLATILE UINT32 vector_address_reg_847;
    VOLATILE UINT32 vector_address_reg_848;
    VOLATILE UINT32 vector_address_reg_849;
    VOLATILE UINT32 vector_address_reg_850;
    VOLATILE UINT32 vector_address_reg_851;
    VOLATILE UINT32 vector_address_reg_852;
    VOLATILE UINT32 vector_address_reg_853;
    VOLATILE UINT32 vector_address_reg_854;
    VOLATILE UINT32 vector_address_reg_855;
    VOLATILE UINT32 vector_address_reg_856;
    VOLATILE UINT32 vector_address_reg_857;
    VOLATILE UINT32 vector_address_reg_858;
    VOLATILE UINT32 vector_address_reg_859;
    VOLATILE UINT32 vector_address_reg_860;
    VOLATILE UINT32 vector_address_reg_861;
    VOLATILE UINT32 vector_address_reg_862;
    VOLATILE UINT32 vector_address_reg_863;
    VOLATILE UINT32 vector_address_reg_864;
    VOLATILE UINT32 vector_address_reg_865;
    VOLATILE UINT32 vector_address_reg_866;
    VOLATILE UINT32 vector_address_reg_867;
    VOLATILE UINT32 vector_address_reg_868;
    VOLATILE UINT32 vector_address_reg_869;
    VOLATILE UINT32 vector_address_reg_870;
    VOLATILE UINT32 vector_address_reg_871;
    VOLATILE UINT32 vector_address_reg_872;
    VOLATILE UINT32 vector_address_reg_873;
    VOLATILE UINT32 vector_address_reg_874;
    VOLATILE UINT32 vector_address_reg_875;
    VOLATILE UINT32 vector_address_reg_876;
    VOLATILE UINT32 vector_address_reg_877;
    VOLATILE UINT32 vector_address_reg_878;
    VOLATILE UINT32 vector_address_reg_879;
    VOLATILE UINT32 vector_address_reg_880;
    VOLATILE UINT32 vector_address_reg_881;
    VOLATILE UINT32 vector_address_reg_882;
    VOLATILE UINT32 vector_address_reg_883;
    VOLATILE UINT32 vector_address_reg_884;
    VOLATILE UINT32 vector_address_reg_885;
    VOLATILE UINT32 vector_address_reg_886;
    VOLATILE UINT32 vector_address_reg_887;
    VOLATILE UINT32 vector_address_reg_888;
    VOLATILE UINT32 vector_address_reg_889;
    VOLATILE UINT32 vector_address_reg_890;
    VOLATILE UINT32 vector_address_reg_891;
    VOLATILE UINT32 vector_address_reg_892;
    VOLATILE UINT32 vector_address_reg_893;
    VOLATILE UINT32 vector_address_reg_894;
    VOLATILE UINT32 vector_address_reg_895;
    VOLATILE UINT32 vector_address_reg_896;
    VOLATILE UINT32 vector_address_reg_897;
    VOLATILE UINT32 vector_address_reg_898;
    VOLATILE UINT32 vector_address_reg_899;
    VOLATILE UINT32 vector_address_reg_900;
    VOLATILE UINT32 vector_address_reg_901;
    VOLATILE UINT32 vector_address_reg_902;
    VOLATILE UINT32 vector_address_reg_903;
    VOLATILE UINT32 vector_address_reg_904;
    VOLATILE UINT32 vector_address_reg_905;
    VOLATILE UINT32 vector_address_reg_906;
    VOLATILE UINT32 vector_address_reg_907;
    VOLATILE UINT32 vector_address_reg_908;
    VOLATILE UINT32 vector_address_reg_909;
    VOLATILE UINT32 vector_address_reg_910;
    VOLATILE UINT32 vector_address_reg_911;
    VOLATILE UINT32 vector_address_reg_912;
    VOLATILE UINT32 vector_address_reg_913;
    VOLATILE UINT32 vector_address_reg_914;
    VOLATILE UINT32 vector_address_reg_915;
    VOLATILE UINT32 vector_address_reg_916;
    VOLATILE UINT32 vector_address_reg_917;
    VOLATILE UINT32 vector_address_reg_918;
    VOLATILE UINT32 vector_address_reg_919;
    VOLATILE UINT32 vector_address_reg_920;
    VOLATILE UINT32 vector_address_reg_921;
    VOLATILE UINT32 vector_address_reg_922;
    VOLATILE UINT32 vector_address_reg_923;
    VOLATILE UINT32 vector_address_reg_924;
    VOLATILE UINT32 vector_address_reg_925;
    VOLATILE UINT32 vector_address_reg_926;
    VOLATILE UINT32 vector_address_reg_927;
    VOLATILE UINT32 vector_address_reg_928;
    VOLATILE UINT32 vector_address_reg_929;
    VOLATILE UINT32 vector_address_reg_930;
    VOLATILE UINT32 vector_address_reg_931;
    VOLATILE UINT32 vector_address_reg_932;
    VOLATILE UINT32 vector_address_reg_933;
    VOLATILE UINT32 vector_address_reg_934;
    VOLATILE UINT32 vector_address_reg_935;
    VOLATILE UINT32 vector_address_reg_936;
    VOLATILE UINT32 vector_address_reg_937;
    VOLATILE UINT32 vector_address_reg_938;
    VOLATILE UINT32 vector_address_reg_939;
    VOLATILE UINT32 vector_address_reg_940;
    VOLATILE UINT32 vector_address_reg_941;
    VOLATILE UINT32 vector_address_reg_942;
    VOLATILE UINT32 vector_address_reg_943;
    VOLATILE UINT32 vector_address_reg_944;
    VOLATILE UINT32 vector_address_reg_945;
    VOLATILE UINT32 vector_address_reg_946;
    VOLATILE UINT32 vector_address_reg_947;
    VOLATILE UINT32 vector_address_reg_948;
    VOLATILE UINT32 vector_address_reg_949;
    VOLATILE UINT32 vector_address_reg_950;
    VOLATILE UINT32 vector_address_reg_951;
    VOLATILE UINT32 vector_address_reg_952;
    VOLATILE UINT32 vector_address_reg_953;
    VOLATILE UINT32 vector_address_reg_954;
    VOLATILE UINT32 vector_address_reg_955;
    VOLATILE UINT32 vector_address_reg_956;
    VOLATILE UINT32 vector_address_reg_957;
    VOLATILE UINT32 vector_address_reg_958;
    VOLATILE UINT32 vector_address_reg_959;
    VOLATILE UINT32 vector_address_reg_960;
    VOLATILE UINT32 vector_address_reg_961;
    VOLATILE UINT32 vector_address_reg_962;
    VOLATILE UINT32 vector_address_reg_963;
    VOLATILE UINT32 vector_address_reg_964;
    VOLATILE UINT32 vector_address_reg_965;
    VOLATILE UINT32 vector_address_reg_966;
    VOLATILE UINT32 vector_address_reg_967;
    VOLATILE UINT32 vector_address_reg_968;
    VOLATILE UINT32 vector_address_reg_969;
    VOLATILE UINT32 vector_address_reg_970;
    VOLATILE UINT32 vector_address_reg_971;
    VOLATILE UINT32 vector_address_reg_972;
    VOLATILE UINT32 vector_address_reg_973;
    VOLATILE UINT32 vector_address_reg_974;
    VOLATILE UINT32 vector_address_reg_975;
    VOLATILE UINT32 vector_address_reg_976;
    VOLATILE UINT32 vector_address_reg_977;
    VOLATILE UINT32 vector_address_reg_978;
    VOLATILE UINT32 vector_address_reg_979;
    VOLATILE UINT32 vector_address_reg_980;
    VOLATILE UINT32 vector_address_reg_981;
    VOLATILE UINT32 vector_address_reg_982;
    VOLATILE UINT32 vector_address_reg_983;
    VOLATILE UINT32 vector_address_reg_984;
    VOLATILE UINT32 vector_address_reg_985;
    VOLATILE UINT32 vector_address_reg_986;
    VOLATILE UINT32 vector_address_reg_987;
    VOLATILE UINT32 vector_address_reg_988;
    VOLATILE UINT32 vector_address_reg_989;
    VOLATILE UINT32 vector_address_reg_990;
    VOLATILE UINT32 vector_address_reg_991;
    VOLATILE UINT32 vector_address_reg_992;
    VOLATILE UINT32 vector_address_reg_993;
    VOLATILE UINT32 vector_address_reg_994;
    VOLATILE UINT32 vector_address_reg_995;
    VOLATILE UINT32 vector_address_reg_996;
    VOLATILE UINT32 vector_address_reg_997;
    VOLATILE UINT32 vector_address_reg_998;
    VOLATILE UINT32 vector_address_reg_999;
    VOLATILE UINT32 vector_address_reg_1000;
    VOLATILE UINT32 vector_address_reg_1001;
    VOLATILE UINT32 vector_address_reg_1002;
    VOLATILE UINT32 vector_address_reg_1003;
    VOLATILE UINT32 vector_address_reg_1004;
    VOLATILE UINT32 vector_address_reg_1005;
    VOLATILE UINT32 vector_address_reg_1006;
    VOLATILE UINT32 vector_address_reg_1007;
    VOLATILE UINT32 vector_address_reg_1008;
    VOLATILE UINT32 vector_address_reg_1009;
    VOLATILE UINT32 vector_address_reg_1010;
    VOLATILE UINT32 vector_address_reg_1011;
    VOLATILE UINT32 vector_address_reg_1012;
    VOLATILE UINT32 vector_address_reg_1013;
    VOLATILE UINT32 vector_address_reg_1014;
    VOLATILE UINT32 vector_address_reg_1015;
    VOLATILE UINT32 vector_address_reg_1016;
    VOLATILE UINT32 vector_address_reg_1017;
    VOLATILE UINT32 vector_address_reg_1018;
    VOLATILE UINT32 vector_address_reg_1019;
    VOLATILE UINT32 vector_address_reg_1020;
    VOLATILE UINT32 vector_address_reg_1021;
    VOLATILE UINT32 vector_address_reg_1022;
    VOLATILE UINT32 vector_address_reg_1023;
#else
    VOLATILE UINT32 VECTOR_ADDRESS_REG[1024];
#endif
} CIC_REG;



typedef void (*CHANNEL_ISR_FUNC)(INT32 nArg);
typedef struct channel_c_vector
{
	CHANNEL_ISR_FUNC	channelIsrFunc;
	INT32 		nArg;
}CHANNEL_C_VECTOR;

typedef struct __cic_isr_vector
{
	/*1个CIC最大256个通道，每个通道可以容纳256个system事件
	  *目前设计策略是对应系统事件ID=通道ID=HOST 中断ID，1
	  *个通道只对应1个系统事件*/
	CHANNEL_C_VECTOR channelIsrTable/*[CORE_MAX_NUM]*/[CHANNEL_MAX_NUM][CHANNEL_MAX_SYSTENID];	
}CIC_ISR_VECTOR;

IMPORT CIC_ISR_VECTOR g_cicIsrTable[CIC_MAX_NUM];

/*global declarations*/
IMPORT INT32 cicChannelIsrRegisterC(UINT8 eventId, UINT32 cicEventId, CHANNEL_ISR_FUNC pChannelIsrFunc, INT32 nArg,BOOL enableInt);
IMPORT void cicChannelIsrDispatchC(UINT8 cicNum);

/* function declaration */



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__IRQ_DSP6746__*/






       
        
        
        

  
 
  
  


  

