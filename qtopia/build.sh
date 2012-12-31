#!/bin/sh
./configure -opensource -embedded arm -xplatform qws/linux-arm-g++ -host-little-endian -little-endian -qt-sql-sqlite -no-webkit -qt-libtiff -qt-libmng -qt-mouse-tslib -qt-mouse-pc -no-mouse-linuxtp -I /usr/local/tslib/include -L /usr/local/tslib/lib -prefix /usr/local/qt

