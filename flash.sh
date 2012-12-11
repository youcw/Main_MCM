#!/bin/sh
if [ "$UID" = "0" ];then
        SUDO=
else
        SUDO=sudo
fi

FASTBOOT=tools/fastboot/fastboot

if [ $# -lt 1 ];then
        echo 
        echo "Usage:"
        echo "          $0 all          #uboot, kernel, ramdisk, system"
        echo "          $0 uboot"
        echo "          $0 kernel"
        echo "          $0 ramdisk"
        echo "          $0 system"
        echo "          $0 reboot"
fi

if [ "$1" = "uboot" -o "$1" = "all" ];then
        $SUDO $FASTBOOT flash bootloader images/u-boot.bin
fi

if [ "$1" = "kernel" -o "$1" = "all" ];then
        $SUDO $FASTBOOT flash kernel images/kernel.bin
fi

if [ "$1" = "ramdisk" -o "$1" = "all" ];then
       $SUDO $FASTBOOT flash ramdisk images/ramdisk.img
fi

if [ "$1" = "system" -o "$1" = "all" ];then
       $SUDO $FASTBOOT flash system images/system.img
fi

if [ "$1" = "reboot" -o "$1" = "all" ];then
       $SUDO $FASTBOOT reboot
fi
