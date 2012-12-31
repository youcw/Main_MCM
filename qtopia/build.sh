#!/bin/sh
#please add -lts to mkspecs/qws/linux-arm-g++/qmake.conf
#修改qmake.conf，添加如下内容：
#QMAKE_CC                = arm-linux-gcc -lts
#QMAKE_CXX               = arm-linux-g++ -lts
#QMAKE_LINK              = arm-linux-g++ -lts
#QMAKE_LINK_SHLIB        = arm-linux-g++ -lts
#保证环境变量设置正确
./configure -opensource -embedded arm -xplatform qws/linux-arm-g++ -host-little-endian -little-endian -qt-sql-sqlite -no-webkit -qt-libtiff -qt-libmng -qt-libjpeg -qt-libpng -qt-mouse-tslib -qt-mouse-pc -qt-kbd-linuxinput -no-mouse-linuxtp -I /usr/local/tslib/include -L /usr/local/tslib/lib -prefix /usr/local/qt

