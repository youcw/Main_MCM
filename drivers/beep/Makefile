all:
	make -C $(SRC_PATH)/kernel M=`pwd` modules 
	cp beep_drv.ko $(SRC_PATH)/system/modules -av
clean:
	make -C $(SRC_PATH)/kernel M=`pwd` modules clean
	rm -rf modules.order *.o *.ko *.mod.* Module*

obj-m	+= beep_drv.o
