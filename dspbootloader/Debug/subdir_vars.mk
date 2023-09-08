################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../BootLoaderLink.cmd 

ASM_SRCS += \
../boot.asm \
../vecs.asm 

C_SRCS += \
../bootloader.c 

OBJS += \
./boot.obj \
./bootloader.obj \
./vecs.obj 

ASM_DEPS += \
./boot.pp \
./vecs.pp 

C_DEPS += \
./bootloader.pp 

C_DEPS__QUOTED += \
"bootloader.pp" 

OBJS__QUOTED += \
"boot.obj" \
"bootloader.obj" \
"vecs.obj" 

ASM_DEPS__QUOTED += \
"boot.pp" \
"vecs.pp" 

ASM_SRCS__QUOTED += \
"../boot.asm" \
"../vecs.asm" 

C_SRCS__QUOTED += \
"../bootloader.c" 


