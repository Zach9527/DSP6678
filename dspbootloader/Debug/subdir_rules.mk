################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
boot.obj: ../boot.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=coffabi -g --include_path="D:/ORC2242/ORC2242/orc2242/dspbootloader/drv" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/ORC2242/ORC2242/orc2242/dspbootloader/common" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="boot.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bootloader.obj: ../bootloader.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=coffabi -g --include_path="D:/ORC2242/ORC2242/orc2242/dspbootloader/drv" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/ORC2242/ORC2242/orc2242/dspbootloader/common" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="bootloader.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

vecs.obj: ../vecs.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=coffabi -g --include_path="D:/ORC2242/ORC2242/orc2242/dspbootloader/drv" --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/ORC2242/ORC2242/orc2242/dspbootloader/common" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages/ti/csl" --include_path="C:/ti/pdk_C6678_1_1_2_6/packages" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="vecs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


