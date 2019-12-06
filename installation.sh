#!/bin/bash 

sudo apt-get install libqt5x11extras5-dev xorg-dev libglib2.0-dev
cd bin
/usr/lib/qt5/bin/qmake ./../src/clienttoggl.pro
make