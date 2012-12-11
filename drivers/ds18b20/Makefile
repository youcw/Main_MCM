all:
	make -C $(SRC_PATH)/kernel M=`pwd` modules 
	cp ds18b20_drv.ko $(SRC_PATH)/system/modules/ 
clean:
	make -C $(SRC_PATH)/kernel M=`pwd` modules clean
	rm -rf modules.order *.o *.ko *.mod.* Module*

obj-m	+= ds18b20_drv.o
