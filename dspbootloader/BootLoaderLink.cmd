-stack 0x800
-heap  0x200


//-l ..\lib\rts6600_coff.lib

MEMORY
{
  BOOT				o = 800000h           l = 400h	 //1K
  VECTOR 			o = 800400h 		  l = 400h	 //1K
  BOOTLOADER		o = 0xc000000          l = 1A800h //106K

}

SECTIONS
{
    .boot 			> 		BOOT
    .vecs			>		VECTOR
 
    .cinit      	>       BOOTLOADER
    .text       	>       BOOTLOADER
    .stack      	>       BOOTLOADER
    .bss        	>       BOOTLOADER
    .const      	>       BOOTLOADER
    .data       	>       BOOTLOADER
    .far        	>       BOOTLOADER
    .switch     	>       BOOTLOADER
    .sysmem     	>       BOOTLOADER
    .tables     	>       BOOTLOADER
    .cio        	>       BOOTLOADER
    .fardata    	>       BOOTLOADER
    .rodata	    	>       BOOTLOADER
    .neardata		>       BOOTLOADER

}                             
