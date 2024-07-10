#!/bin/bash
rm usbos.run
g++ -c utilsstd.cpp -o utilsstd.o
g++ -c dphp.cpp -o dphp.o
g++ -c install_usbos.cpp -o main.o
#g++ -no-pie -Xlinker utilsstd.o dphp.o main.o -o cuter.run
g++ -Xlinker utilsstd.o dphp.o main.o -o usbos.run
