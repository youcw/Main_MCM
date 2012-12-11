all:
	make -C $(SRC_PATH)/kernel M=`pwd` modules 
	cp regeditor_drv.ko $(SRC_PATH)/system/modules 
clean:
	make -C $(SRC_PATH)/kernel M=`pwd` modules clean
	rm -rf modules.order *.o *.ko *.mod.* Module*

obj-m	+= regeditor_drv.o
