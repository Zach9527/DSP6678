
;定义全局符号
	.global _copy_code

	.title  "Flash bootup utility for fft_dsp"
	.option D,T
DEBUG	.set	1
;定义宏
	.if DEBUG
COPY_TABLE    	.equ    0x70000400;0x70000400(dsp6678);0x64000400(dsp6416);0x60000400(dsp6455);0x60000400(dsp6748)
	.endif

;	.if DSP667X_ASM
;COPY_TABLE    	.equ    0x70000400
;	.endif
;	.if DSP674X_ASM
;COPY_TABLE    	.equ    0x60000400
;	.endif



	.sect ".boot"
	.global _boot
_boot:  
	;配置字
	;.int	0x00000001
	b 	_copy_code
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x10
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x20
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x30
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x40
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x50
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x60
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x70
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x80
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0x90
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0xa0
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0xb0
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0xc0
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0xd0
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0xe0
	NOP     1
	NOP     1
	NOP     1
	NOP     1
	;; 0xf0
	.byte   0x6f		;o
	.byte   0x72		;r
	.byte   0x63		;c
	.byte   0x5f		;_
	.byte   0x44		;D
	.byte   0x53		;S
	.byte   0x50		;P
	.byte   0x36		;6
	.byte   0x36		;6
	.byte   0x37		;7
	.byte   0x58		;X
	.byte   0
***********************************************************************
* Function: _copy_code
* Description: copy code from to ram and jump to c start
***********************************************************************
	.sect ".boot"
    .global _copy_code
_copy_code:
	MVKL  COPY_TABLE, a0
	MVKH  COPY_TABLE, a0
	MVK 0x0, A5

	;LOAD ENTRY POINT
	ZERO A1
	ZERO A2
	LDHU   *A0++, A1
	NOP 5				
	LDHU    *A0++, A2
	NOP 5
	SHL   A2,16,A2	;SMALL
	;SHL   A1,16,A1	;BIG
	ADD   A1,A2,A1  ; 	A1中为跳转地址
				
copy_section_top:
        ;LOAD LENGTH
        NOP 5
        ZERO A2
		ZERO A3
        LDHU 	  *A0++, A2
        NOP 5
        LDHU     *A0++,A3
        NOP 5
        SHL			A3,16,A3    	;SMALL
        ;SHL			A2,16,A2    	;BIG
        ADD     A2,A3,A2			;A2中包含段长信息
        
        ;LOAD DEST ADDR
        ZERO A3
		ZERO A4
        LDHU			*A0++,A3
        NOP 5
        LDHU			*A0++,A4
        NOP 5
        SHL			A4,16,A4      	;SMALL
        ;SHL			A3,16,A3	;BIG
        ADD     A3,A4,A3			;A3中包含目的地址        
        ADD     A3,A5,A3			;plus iram base addr

	MV A2, A10
boot_lenth_check:
	AND     3, A10, A2
 [!A2]	b boot_lenth_ok			;A10不能被4整除
	nop   5
	MVK    1, A11
	ADD    A11, A10, A10
	b	boot_lenth_check
	nop   5
boot_lenth_ok:

	MV A10, A2
	NOP 5

 [!A2]  b copy_done            ; have we copied all sections?
        nop   5

copy_loop:
		NOP 5
        LDHU		 *A0++,A4
        NOP 5
 		SUB    A2,2,A2
 	    NOP 5	

 		STH		 A4,*A3++
 		NOP 5
 
 		SUB    A2,1, A2		
 [!A2]  ADD    A2,3, A2	
 [ A2]  ADD    A2,1, A2		
 [ A2]  b     copy_loop        ; setup branch if not done
         NOP 5
 [!A2]  b     copy_section_top
         NOP 5
;****************************************************************************
;* Jump to entry point
;****************************************************************************
copy_done:
        b    .S2 A1
        nop   5

