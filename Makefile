
#SOC := s5l8930
#SOC := msm8960
SOC := exynos5250
VICMOD := pl192mod

#SERIES := cortex-a8
#SERIES := cortex-a9
SERIES := cortex-a15

MKDIR := ../make

include $(MKDIR)/Makefile_arm_fb.common

.PHONY : all
.PHONY : build
.PHONY : includes
.PHONY : clean

all:
	@$(MAKE) -s check
	@$(MAKE) -s clean
	@$(MAKE) -s includes
	@$(MAKE) -s build
	
build:
	@$(MAKE) -s check
	@echo "building modules"	
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory s5l8930mod build; fi
	@if test $(SOC) = msm8960; then $(MAKE) -s --directory msm8960mod build; fi
	@if test $(SOC) = exynos5250; then $(MAKE) -s --directory exynos5250mod build; fi
	@$(MAKE) -s --directory pl192mod build
	@if test $(SERIES) = cortex-a9; then @$(MAKE) -s --directory a9mod build; fi
	@$(MAKE) -s --directory bkptmod build
	@$(MAKE) -s --directory pgtblmod build
	@$(MAKE) -s --directory cryptomod build
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory wdtmod build; fi
	#@$(MAKE) -s --directory linmod build
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory openibootmod build; fi
	#@$(MAKE) -s --directory gdbmod build
	#@$(MAKE) -s --directory injectmod build
	#@$(MAKE) -s --directory testmod build

check:
	@echo "checking toolchain"
	@if test "$(PREFIX)" = "" ; then echo "A toolchain has not been specified. Define PREFIX, for example \"make PREFIX=arm-linux-gnueabi-\""; exit 2; fi
	@if ! [ -x "`which $(LD) 2>/dev/null`" ]; then echo LD = "$(LD) not found"; exit 2; fi
	@if ! [ -x "`which $(CC) 2>/dev/null`" ]; then echo "CC = $(CC) not found"; exit 2; fi
	@if ! [ -x "`which $(AR) 2>/dev/null`" ]; then echo "AR = $(AR) not found"; exit 2; fi
	@if ! [ -x "`which $(NM) 2>/dev/null`" ]; then echo "NM = $(NM) not found"; exit 2; fi
	@if ! [ -x "`which $(OBJDUMP) 2>/dev/null`" ]; then echo "OBJDUMP = $(OBJDUMP) not found"; exit 2; fi
	@if ! [ -x "`which $(OBJCOPY) 2>/dev/null`" ]; then echo "OBJCOPY = $(OBJCOPY) not found"; exit 2; fi

includes:
	@echo "including modules"
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory s5l8930mod includes; fi
	@if test $(SOC) = msm8960; then $(MAKE) -s --directory msm8960mod includes; fi
	@if test $(SOC) = exynos5250; then $(MAKE) -s --directory exynos5250mod includes; fi
	@$(MAKE) -s --directory pl192mod includes
	@if test $(SERIES) = cortex-a9; then @$(MAKE) -s --directory a9mod includes; fi
	@$(MAKE) -s --directory bkptmod includes
	@$(MAKE) -s --directory pgtblmod includes
	@$(MAKE) -s --directory cryptomod includes
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory wdtmod includes; fi
	#@$(MAKE) -s --directory linmod includes
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory openibootmod includes; fi
	#@$(MAKE) -s --directory gdbmod includes
	#@$(MAKE) -s --directory injectmod includes
	#@$(MAKE) -s --directory testmod includes

clean:
	@echo "cleaning modules"
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory s5l8930mod clean; fi
	@if test $(SOC) = msm8960; then $(MAKE) -s --directory msm8960mod clean; fi
	@if test $(SOC) = exynos5250; then $(MAKE) -s --directory exynos5250mod clean; fi
	@$(MAKE) -s --directory pl192mod clean
	@if test $(SERIES) = cortex-a9; then @$(MAKE) -s --directory a9mod clean; fi
	@$(MAKE) -s --directory bkptmod clean
	@$(MAKE) -s --directory pgtblmod clean
	@$(MAKE) -s --directory cryptomod clean
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory wdtmod clean; fi
	#@$(MAKE) -s --directory linmod clean
	@if test $(SOC) = s5l8930; then $(MAKE) -s --directory openibootmod clean; fi
	#@$(MAKE) -s --directory gdbmod clean
	#@$(MAKE) -s --directory injectmod clean
	#@$(MAKE) -s --directory testmod clean
