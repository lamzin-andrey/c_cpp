#!/bin/bash

#gcc -c landio.c -o obj/landio.o
gcc -c dphpc.c  -o obj/dphp.o
gcc -c main.c -o obj/main.o
gcc obj/landio.o obj/dphp.o obj/main.o -o test.ex
./test.ex
