#!/bin/bash
rm cuter.run
g++ -c utilsstd.cpp -o utilsstd.o
g++ -c dphp.cpp -o dphp.o
g++ -c cuter.cpp -o main.o
g++ -no-pie -Xlinker utilsstd.o dphp.o main.o -o cuter.run
