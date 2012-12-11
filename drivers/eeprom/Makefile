all:
	make -C $(SRC_PATH)/kernel M=`pwd` modules 
	cp at24cxx.ko $(SRC_PATH)/system/modules/ -av
clean:
	make -C $(SRC_PATH)/kernel M=`pwd` modules clean
	rm -rf modules.order *.o *.ko *.mod.* Module.*

obj-m	+= at24cxx.o
