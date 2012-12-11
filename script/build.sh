#!/bin/sh

MKYAFFS2IMAGE=tools/images_tools/mkyaffs2image
CheckLog()
{
        if [ $1 = "" -o ! -e tmp/log/$1.log ];then
                return 1
        fi

        if grep "warning:" tmp/log/$1.log || grep "Warning:" tmp/log/$1.log ;then
                echo "\033[33mWarning.\033[0m"
                echo "There has some warning. Please see $1 log in tmp/log/$l.log"
        fi

        if grep "error:" tmp/log/$1.log || grep "Error:" tmp/log/$1.log ;then
                echo "\033[31m[Error.]\033[0m"
                grep "error:" tmp/log/$1.log
                echo "There has some error. Please see $1 log in tmp/log/$1.log"
                return 1
        fi
        
        return 0
}

BuildUboot()
{
        DONE_FLAG=1 
        echo "\033[32mBuild UBoot \033[0m"
        
        if [ ! -e u-boot ]; then
                echo "\033[31mu-boot directory not found!\033[0m"
                return
        fi
        
        (cd u-boot && make CW210_config && make all) > tmp/log/uboot.log 2>&1 
        
        if ! CheckLog uboot;then
                DONE_FLAG=0
        fi

        if [ "$DONE_FLAG" = "1" ];then
                cp u-boot/u-boot.bin images/               
        else
                exit 1;
        fi
}

BuildKernel()
{
        DONE_FLAG=1
        echo "\033[32mBuild Kernel \033[0m"
        
        if [ ! -e kernel ];then
                echo "\033[31mkernel directory not found!\033[0m"
                return
        fi

        if [ -e kernel/.config ];then
                echo "\033[36mkernel config file .config found,use it for kernel build\033[0m"
        else
                echo "\033[36mkernel config file .config not found, make kernel config\033[0m"
                (cd kernel && cp config_ok .config) > /dev/null 2>&1
        fi

        (cd kernel && make zImage) > tmp/log/kernel.log 2>&1

        if ! CheckLog kernel;then
                DONE_FLAG=0
        fi

        if [ "$DONE_FLAG" = "1" ];then
                cp kernel/arch/arm/boot/zImage images/kernel.bin
                echo "\033[32m[Done]\033[0m"
        else
                exit 1;
        fi
}

BuildRamdisk()
{
        echo "\033[32mBuild Ramdisk \033[0m"
        dd if=/dev/zero of=initrd.img bs=1k count=8192
        sudo mkfs.ext2 -F initrd.img
        sudo mount -t ext2 -o loop initrd.img /mnt
        sudo cp rootfs/* /mnt/ -fr
        sudo umount /mnt/
        gzip --best -c initrd.img > ramdisk.img
        mv ramdisk.img images/
        rm initrd.img
}

BuildSystem()
{
        echo "\033[32mBuild System \033[0m"
       
        $MKYAFFS2IMAGE system system.img
        mv system.img images/
        
        echo "\033[32m[Done]\033[0m" 
}

BuildApp()
{
        DONE_FLAG=1
        echo "\033[32mBuild App \033[0m"
        if [ ! -e board/src/Main ];then
                echo "\033[33m Main directory not found!\033[0m"
                return
        else
                (cd board/src/Main && make clean && make) > tmp/log/Main.log 2>&1
        fi
        
        if ! CheckLog Main;then
                DONE_FLAG=0
        fi

        if [ "$DONE_FLAG" = "1" ];then
                cp board/src/Main/Main system/app
                echo "\033[32m[Main Done]\033[0m"
        else
                exit 1;
        fi
        
        if [ ! -e pc/PCOM ];then
                echo "\033[33m PCOM directory not found!\033[0m"
                return
        else
                (cd pc/PCOM && make distclean && qmake-qt4 -project && qmake-qt4 && make) > tmp/log/pcom.log 2>&1
        fi
        
        if ! CheckLog pcom;then
                DONE_FLAG=0
        fi

        if [ "$DONE_FLAG" = "1" ];then
                cp pc/PCOM/PCOM images/
                echo "\033[32m[PCOM Done]\033[0m"
        else
                exit 1;
        fi
        
        if [ ! -e server ];then
                echo "\033[33m server directory not found!\033[0m"
                return
        else
                (cd server && make distclean && ../tools/bin/qmake -project && ../tools/bin/qmake && make) > tmp/log/server.log 2>&1
        fi
        
        if ! CheckLog server;then
                DONE_FLAG=0
        fi

        if [ "$DONE_FLAG" = "1" ];then
                cp server/server system/app
                echo "\033[32m[server Done]\033[0m"
        else
                exit 1;
        fi
}

BuildDrivers()
{
        DONE_FLAG=1
        echo "\033[32mBuild Drivers \033[0m"
        if [ ! -e drivers ];then
                echo "\033[33m drivers directory not found!\033[0m"
                return
        else
                (cd drivers && make) > tmp/log/drivers.log 2>&1
        fi
        
        if ! CheckLog drivers;then
                DONE_FLAG=0
        fi

        if [ "$DONE_FLAG" = "1" ];then
                (cd drivers && find . -name *.ko | xargs cp *.ko system/modules/)
                echo "\033[32m[Done]\033[0m"
        else
                exit 1;
        fi
}

if [ "$1" = "uboot" ]; then
        BuildUboot
elif [ "$1" = "kernel" ]; then
        BuildKernel
elif [ "$1" = "ramdisk" ];then
        BuildRamdisk
elif [ "$1" = "system" ];then
        BuildSystem
elif [ "$1" = "app" ];then
        BuildApp
elif [ "$1" = "drivers" ];then
        BuildDrivers
fi
