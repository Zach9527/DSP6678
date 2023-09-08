/*
 文件名称：irq_dsp667x.h
摘要：
*/
/* 修改历史:

2016.3.12,lujun创建文件
*/

#ifndef __IRQ_DSP667x__
#define __IRQ_DSP667x__

#ifdef __cplusplus
extern "C" {
#endif

/*include*/

/*defines*/
#define EVENT_TOTAL_NUM		128		 /*事件总数*/

#define EVENT_EVT0 																		(0 	) 
#define EVENT_EVT1 																		(1 	)  
#define EVENT_EVT2 																		(2 	)  
#define EVENT_EVT3 																		(3 	)  
#define EVENT_TETBHFULLINT_N 															(4 	)    
#define EVENT_TETBFULLINT_N 															(5 	) 
#define EVENT_TETBACQINT_N 																(6 	)  
#define EVENT_TETBOVFLINT_N 															(7 	)   
#define EVENT_TETBUNFLINT_N 															(8 	) 
#define EVENT_EMU_DTDMA 																(9 	) 
#define EVENT_MSMC_MPF_ERROR 															(10	)        
#define EVENT_EMU_RTDXRX																(11	) 
#define EVENT_EMU_RTDXTX																(12	)  
#define EVENT_IDMA0 																	(13	)  
#define EVENT_IDMA1 																	(14	)  
#define EVENT_SEMERR_N 																	(15	)  
#define EVENT_SEMINT_N 																	(16	)  
#define EVENT_PCIE_MSI_INT_N 															(17	)  
#define EVENT_TSIP0_ERRINT_N 															(18	)  
#define EVENT_TSIP1_ERRINT_N 															(19	)  
#define EVENT_INTDST_N_16 																(20	)  
#define EVENT_CIC0_OUT32_0_11_N_CIC1_OUT32_0_11_N_4		            					(21	) 
#define EVENT_CIC0_OUT32_1_11_N_CIC1_OUT32_1_11_N_4		            					(22	) 
#define EVENT_CIC0_OUT32_2_11_N_CIC1_OUT32_2_11_N_4		            					(23	)  
#define EVENT_CIC0_OUT32_3_11_N_CIC1_OUT32_3_11_N_4		            					(24	)  
#define EVENT_CIC0_OUT32_4_11_N_CIC1_OUT32_4_11_N_4		           						(25	) 
#define EVENT_CIC0_OUT32_5_11_N_CIC1_OUT32_5_11_N_4		            					(26	)  
#define EVENT_CIC0_OUT32_6_11_N_CIC1_OUT32_6_11_N_4		            					(27	)  
#define EVENT_CIC0_OUT32_7_11_N_CIC1_OUT32_7_11_N_4		            					(28	)  
#define EVENT_CIC0_OUT32_8_11_N_CIC1_OUT32_8_11_N_4		            					(29	)  
#define EVENT_CIC0_OUT32_9_11_N_CIC1_OUT32_9_11_N_4 		        					(30	)  
#define EVENT_CIC0_OUT32_10_11_N_CIC1_OUT32_10_11_N_4		        					(31	)  
#define EVENT_QM_INT_LOW_0 														            (32	)  
#define EVENT_QM_INT_LOW_1 														            (33	) 
#define EVENT_QM_INT_LOW_2 														            (34	) 
#define EVENT_QM_INT_LOW_3 														            (35	) 
#define EVENT_QM_INT_LOW_4 														            (36	) 
#define EVENT_QM_INT_LOW_5 														            (37	) 
#define EVENT_QM_INT_LOW_6 														            (38	) 
#define EVENT_QM_INT_LOW_7 														            (39	) 
#define EVENT_QM_INT_LOW_8 														            (40	) 
#define EVENT_QM_INT_LOW_9 														            (41	) 
#define EVENT_QM_INT_LOW_10														            (42	) 
#define EVENT_QM_INT_LOW_11														            (43	) 
#define EVENT_QM_INT_LOW_12														            (44	) 
#define EVENT_QM_INT_LOW_13														            (45	) 
#define EVENT_QM_INT_LOW_14														            (46	) 
#define EVENT_QM_INT_LOW_15														            (47	) 
#define EVENT_QM_INT_HIGH_N 														        (48	) 
#define EVENT_QM_INT_HIGH_N_8 													            (49	) 
#define EVENT_QM_INT_HIGH_N_16 												            	(50	) 
#define EVENT_QM_INT_HIGH_N_24 												            	(51	) 
#define EVENT_TSIP0_RFSINT_N 													            (52	) 
#define EVENT_TSIP0_RSFINT_N 													            (53	) 
#define EVENT_TSIP0_XFSINT_N 													            (54	) 
#define EVENT_TSIP0_XSFINT_N 													            (55	) 
#define EVENT_TSIP1_RFSINT_N 													            (56	) 
#define EVENT_TSIP1_RSFINT_N 													            (57	) 
#define EVENT_TSIP1_XFSINT_N 													            (58	) 
#define EVENT_TSIP1_XSFINT_N 													            (59	) 
#define EVENT_REV0                                                							(60	) 
#define EVENT_REV1                                               							(61	) 
#define EVENT_CIC0_OUT_2_8_N_CIC1_OUT_2_8_N_4					            			    (62	) 
#define EVENT_CIC0_OUT_3_8_N_CIC1_OUT_3_8_N_4					            			    (63	) 
#define EVENT_TINTL_N 																	    (64	) 
#define EVENT_TINTH_N 																	    (65	) 
#define EVENT_TINT8L 																	    (66	) 
#define EVENT_TINT8H 																	    (67	) 
#define EVENT_TINT9L 																	    (68	) 
#define EVENT_TINT9H 																	    (69	) 
#define EVENT_TINT10L 																	    (70	) 
#define EVENT_TINT10H 																	    (71	) 
#define EVENT_TINT11L 																	    (72	) 
#define EVENT_TINT11H 																	    (73	) 
#define EVENT_TINT12L 																	    (74	) 
#define EVENT_TINT12H 																	    (75	) 
#define EVENT_TINT13L 																	    (76	) 
#define EVENT_TINT13H 																	    (77	) 
#define EVENT_TINT14L 																	    (78	) 
#define EVENT_TINT14H 																	    (79	) 
#define EVENT_TINT15L 																	    (80	) 
#define EVENT_TINT15H 																	    (81	) 
#define EVENT_GPINT8 																	    (82	) 
#define EVENT_GPINT9  																	    (83	) 
#define EVENT_GPINT10 																	    (84	) 
#define EVENT_GPINT11 																	    (85	) 
#define EVENT_GPINT12 																	    (86	) 
#define EVENT_GPINT13 																	    (87	) 
#define EVENT_GPINT14 																	    (88	) 
#define EVENT_GPINT15 																	    (89	) 
#define EVENT_GPINT_N 																	    (90	) 
#define EVENT_IPC_LOCAL 																    (91	) 
#define EVENT_CIC0_OUT_4_8_N_CIC1_OUT_4_8_N_4					            				(92	) 
#define EVENT_CIC0_OUT_5_8_N_CIC1_OUT_5_8_N_4					            				(93	) 
#define EVENT_CIC0_OUT_6_8_N_CIC1_OUT_6_8_N_4					            				(94	) 
#define EVENT_CIC0_OUT_7_8_N_CIC1_OUT_7_8_N_4					            				(95	) 
#define EVENT_INTERR 																	   	(96	) 
#define EVENT_EMC_IDMAERR 															        (97	) 
#define EVENT_RSV2                                               							(98	) 
#define EVENT_RSV3                                              							(99	) 
 #define EVENT_EFIINTA 																        (100) 
 #define EVENT_EFIINTB 																        (101) 
 #define EVENT_CIC0_OUT0_CIC1_OUT0 										            		(102)         
 #define EVENT_CIC0_OUT1_CIC1_OUT1 										            		(103) 
 #define EVENT_CIC0_OUT8_CIC1_OUT8 										            		(104) 
 #define EVENT_CIC0_OUT9_CIC1_OUT9 										            		(105) 
 #define EVENT_CIC0_OUT16_CIC1_OUT16 									            		(106) 
 #define EVENT_CIC0_OUT17_CIC1_OUT17 									           	 		(107) 
 #define EVENT_CIC0_OUT24_CIC1_OUT24 									            		(108) 
 #define EVENT_CIC0_OUT25_CIC1_OUT25 									            		(109) 
 #define EVENT_MDMAERREVT 													         		(110) 
 #define EVENT_RSV4                                               							(111) 
 #define EVENT_EDMA3CC0_EDMACC_AETEVT 									          			(112) 
 #define EVENT_PMC_ED 														          		(113) 
 #define EVENT_EDMA3CC1_EDMACC_AETEVT 									          			(114) 
 #define EVENT_EDMA3CC2_EDMACC_AETEVT 									          			(115) 
 #define EVENT_UMC_ED1 														          		(116) 
 #define EVENT_UMC_ED2 														          		(117) 
 #define EVENT_PDC_INT 														          		(118) 
 #define EVENT_SYS_CMPA 													          		(119) 
 #define EVENT_PMC_CMPA 													          		(120)            
 #define EVENT_PMC_DMPA 													          		(121) 
 #define EVENT_DMC_CMPA 													          		(122) 
 #define EVTFE_DMC_DMPA 													          		(123) 
 #define EVTFF_UMC_CMPA 													          		(124) 
 #define UMC_DMPA 															          		(125) 
 #define EMC_CMPA															          		(126) 
 #define EMC_BUSERR				 											          		(127) 
 #define INTDST0																			(0x14)								


 #define EVTFE_ID_NMI	   0xFE		/*不可屏蔽中断事件id*/
 #define EVTFF_ID_ALL	   0xFF		/*所有中断事件ID*/


/*typedef*/
typedef void (*EVENT_ISR_FUNC)(INT32 nArg);
typedef struct event_c_vector
{
	EVENT_ISR_FUNC	eventIsrFunc;
	INT32 		nArg;
}EVNET_C_VECTOR;

/*global declarations*/

/* function declaration */
IMPORT STATUS intInit(void);
IMPORT void intGlobalEnable(void);
IMPORT UINT32 intGlobalDisable(void);
IMPORT void intGlobalRestore(UINT32 unRestoreValue);
IMPORT  void intNmiEnable(void);
IMPORT  void intNmiDisable(void);
IMPORT STATUS intEnable(UINT32 unIntNum);
IMPORT STATUS intDisable(UINT32 unIntNum);
IMPORT INLINE STATUS intClear(UINT32 unIntNum);
IMPORT INLINE STATUS intEventMap(UINT32 unEvnetId, UINT32 unIntNum);
IMPORT void eventIsrDispatchC(UINT32 unEvnetGroupId);
IMPORT INT32 eventIsrRegisterC(UINT32 unEvnetId, EVENT_ISR_FUNC eventIsrFunc, INT32 nArg,BOOL enableInt);
IMPORT STATUS eventAddC(UINT32 unEvnetId);
IMPORT STATUS eventRemoveC(UINT32 unEvnetId);
IMPORT STATUS eventAddE(UINT32 unEvnetId);
IMPORT STATUS eventRemoveE(UINT32 unEvnetId);
IMPORT STATUS intEventSet(UINT32 unEvnetId);
IMPORT STATUS intEventClear(UINT32 unEvnetId);
IMPORT  STATUS eventMap(UINT32 unEvnetId, UINT32 unIntNum);



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__IRQ_DSP6746__*/






       
        
        
        

  
 
  
  


  
  
       
       
    
    






















    
    
    
    
    
    
    
    
    
      
  


  
  
  
  
  
  
  
  




              
              
            
            
            
            
             
             
             
             
             
             
             
             
             
             
             
             
            
              
             
             
             
             
             
             
              
           




            
         


          
          








         


             


          
          
          
           
           
           
           
           
           
        

