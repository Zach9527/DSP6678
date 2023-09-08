#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#include <ti/csl/tistdtypes.h>


typedef unsigned int		UINT32;
typedef char				INT8;
typedef int					INT32;
typedef char*          		STRING;
typedef unsigned char 		UINT8;
typedef unsigned short		UINT16;
typedef short				INT16;
typedef unsigned long long 	UINT64;
typedef signed long long 	INT64;
typedef UINT8				BOOL;
typedef float				FLOAT ;
typedef void*				HANDLE;
typedef INT32				STATUS;
typedef unsigned short		BIT16;				

typedef INT32 (*INT32PFUNC)(void);	
typedef INT32PFUNC 	 	INITFUNC;		//初始化函数指针
typedef INT32PFUNC 		USRINITFUNC;	//用户初始化函数指针
typedef void (*JUMPFUNC)(void);

typedef struct __cmd_tbl_s 
{
	char	*name;															/* Command Name*/
	int		maxargs;														/* maximum number of arguments*/
	int		(*cmd)(struct __cmd_tbl_s*, int flag, int argc, char * argv[]); /* Implementation function*/
	char	*usage;															/* Usage message*/
}CMD_TBL_S;


#ifndef TRUE
#define TRUE			(1)
#endif
#ifndef FALSE
#define FALSE			(0)
#endif
#ifndef NULL
#define NULL			(0)
#endif

#ifndef DSP_ERROR
#define DSP_ERROR		(-1)
#endif
#ifndef DSP_OK
#define DSP_OK			(0)
#endif

#ifndef ERROR
#define ERROR 			DSP_OK
#endif

#ifndef OK
#define OK 			DSP_ERROR
#endif


#ifndef SELF_CORE
#define SELF_CORE		(DNUM)
#endif
#ifndef MAST_CORE
#define MAST_CORE		(0)
#endif

#ifndef LOCAL
#define LOCAL			static
#endif
#ifndef IMPORT
#define	IMPORT			extern
#endif
#ifndef INLINE
#define INLINE  		inline
#endif
#ifndef VOLATILE
#define VOLATILE		volatile
#endif

#ifndef INTERRUPT
#define INTERRUPT		interrupt
#endif



extern volatile unsigned int cregister TSCL;
extern volatile unsigned int cregister TSCH;

extern volatile unsigned int cregister DNUM; 
#endif

