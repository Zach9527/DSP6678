################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c6000_7.4.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./common/irq.obj" \
"./common/delay.obj" \
"./common/common.obj" \
"./drv/uart_dsp6678.obj" \
"./drv/psc_dsp667x.obj" \
"./drv/progress_bar.obj" \
"./drv/pll_dsp667x.obj" \
"./drv/irq_dsp667x.obj" \
"./drv/flashdrv.obj" \
"./drv/emif_dsp667x.obj" \
"./drv/ddr_dsp667x.obj" \
"./drv/cic_dsp667x.obj" \
"./drv/bootCfg_dsp667x.obj" \
"./drv/EMIF16_NormalTest.obj" \
"./drv/DDR_NormalTest.obj" \
"./vecs.obj" \
"./bootloader.obj" \
"./boot.obj" \
"../BootLoaderLink.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include drv/subdir_vars.mk
-include common/subdir_vars.mk
-include subdir_rules.mk
-include drv/subdir_rules.mk
-include common/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: dspbootloader.out

# Tool invocations
dspbootloader.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=coffabi -g --display_error_number --diag_warning=225 --diag_wrap=off -z -m"dspbootloader.map" -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/lib" -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="dspbootloader_linkInfo.xml" --rom_model -o "dspbootloader.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C6000_EXECUTABLE_OUTPUTS__QUOTED) "dspbootloader.out"
	-$(RM) "bootloader.pp" "drv\DDR_NormalTest.pp" "drv\EMIF16_NormalTest.pp" "drv\bootCfg_dsp667x.pp" "drv\cic_dsp667x.pp" "drv\ddr_dsp667x.pp" "drv\emif_dsp667x.pp" "drv\flashdrv.pp" "drv\irq_dsp667x.pp" "drv\pll_dsp667x.pp" "drv\progress_bar.pp" "drv\psc_dsp667x.pp" "drv\uart_dsp6678.pp" "common\common.pp" "common\delay.pp" "common\irq.pp" 
	-$(RM) "boot.obj" "bootloader.obj" "vecs.obj" "drv\DDR_NormalTest.obj" "drv\EMIF16_NormalTest.obj" "drv\bootCfg_dsp667x.obj" "drv\cic_dsp667x.obj" "drv\ddr_dsp667x.obj" "drv\emif_dsp667x.obj" "drv\flashdrv.obj" "drv\irq_dsp667x.obj" "drv\pll_dsp667x.obj" "drv\progress_bar.obj" "drv\psc_dsp667x.obj" "drv\uart_dsp6678.obj" "common\common.obj" "common\delay.obj" "common\irq.obj" 
	-$(RM) "boot.pp" "vecs.pp" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-..\EMIF16_BootLoader.bat
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

