-heap  0x800
-stack 0x1000

MEMORY
{
	/* Local L2, 0.5~1MB*/
	VECTORS: 	o = 0x00800000  l = 0x00000200
	LL2_RW_DATA: 	o = 0x10803000  l = 0x0007D000	//0x10800400~0x10803000´æ·Å¶þ¼¶bootloader

	/* Shared L2 2~4MB*/
	SL2: 		o = 0x0C01A800  l = 0x00300000
	
	/* External DDR3, upto 2GB per core */
	DDR3_CODE: 	o = 0x80000000  l = 0x00600000   /*set memory protection attribitue as execution only*/
	DDR3_RW_DATA: 	o = 0x80600000  l = 0x00A00000   /*set memory protection attribitue as read/write*/
}

SECTIONS
{
	vecs       	>    VECTORS 

	.text           >    LL2_RW_DATA
	.cinit          >    LL2_RW_DATA
	.const          >    LL2_RW_DATA
	.switch         >    LL2_RW_DATA

	.stack          >    LL2_RW_DATA
	GROUP
	{
		.neardata
		.rodata
		.bss
	} 		>    LL2_RW_DATA
	.far            >    LL2_RW_DATA
	.fardata        >    LL2_RW_DATA
	.cio            >    LL2_RW_DATA
	.sysmem         >    SL2
	QMSS_Data:linkingRAM1 		> 	SL2
	QMSS_Data:Descriptor_SL2 	> 	SL2
	PacketData:buffer_SL2 		> 	SL2
	QMSS_Data:Descriptor_LL2 	> 	DDR3_CODE
	PacketData:buffer_LL2 		> 	DDR3_CODE
	QMSS_Data:Descriptor_DDR 	> 	DDR3_RW_DATA
	PacketData:buffer_DDR 		> 	DDR3_RW_DATA
	.UART_DATA_BUF              >   DDR3_RW_DATA
}


