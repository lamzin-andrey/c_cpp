#!/bin/bash
rm tst.isp
#g++ -c utilsstd.cpp -o utilsstd.o
g++ -c  dphp.cpp -o dphp.o
g++ -c main.cpp -o main.o
g++ -Xlinker utilsstd.o dphp.o main.o -o tst.isp
