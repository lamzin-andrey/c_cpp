#!/bin/bash

#This simple example using system calls 
#open
#read
#write

#and link *.o files created with g++ and gcc (extern "C" {...} dor dummies. ( I dummy, I forgot it )  ) )

#And create a shared library in linux


gcc -c landio.c
g++ -c main.cpp
g++ landio.o main.o -o gpp.run
./gpp.run

# Create dymamic shared library and executable file. and use it with 

# true man http://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index

mkdir so
rm so/liblandio.so
rm so/liblandio.a

gcc -c -fPIC landio.c -o so/landio.o
#ar rcs so/liblandio.a so/other.o so/answer.o
ar rcs so/liblandio.a so/landio.o

gcc -shared so/landio.o  -o so/liblandio.so

#g++ -c -fPIC main.cpp -o main.o
g++ -c main.cpp -o main.o
# Note the order:
#   -ltq84-shared needs to be placed AFTER main.c

#gcc  bin/main.o -Lbin/shared -ltq84 -o bin/use-shared-library
g++ main.o -Lso -llandio -o gppd.run
./gppd.run

#dynamic 
d=$(pwd)
#LD_LIBRARY_PATH="$d/so" #fail in xubuntu 22.04
sudo cp $d/so/liblandio.so /usr/lib/liblandio.so
#echo $LD_LIBRARY_PATH   #fail in xubuntu 22.04
./gppd.run


