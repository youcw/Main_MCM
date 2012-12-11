all:
	make -C $(SRC_PATH)/kernel M=`pwd` modules 
	cp adc_drv.ko $(SRC_PATH)/system/modules/ 
clean:
	make -C $(SRC_PATH)/kernel M=`pwd` modules clean
	rm -rf modules.order *.ko *.o *.mod.* Module*

obj-m	+= adc_drv.o
