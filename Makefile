.PHONY:help all uboot kernel app ramdisk system clean drivers

SRC_PATH=$(shell pwd)
export SRC_PATH

help:
	@echo "Usage:"
	@echo "\tmake uboot	# Compile UBoot"
	@echo "\tmake kernel	# Compile Linux Kernel"
	@echo "\tmake ramdisk	# Generate ramdisk.img"
	@echo "\tmake system 	# Generate system.img"
	@echo "\tmake app	# Build Project applicatins"
	@echo "\tmake drivers	# Build drivers"
	@echo "\tmake all	# make uboot kernel ramdisk system app drivers"

uboot kernel ramdisk system app drivers:
	@script/build.sh $@

all:
	@script/build.sh uboot
	@script/build.sh kernel
	@script/build.sh drivers
	@script/build.sh app
	@script/build.sh ramdisk
	@script/build.sh system
clean:
	rm -fr images/*
	rm -fr system/modules/*.ko
	rm -fr system/app/*
	make -C board/src/Main
	make -C u-boot distclean
	make -C drivers clean
	make -C kernel clean
