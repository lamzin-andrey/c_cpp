#SHS

rm obj/main.o
rm test.kex

#rm obj/landio.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landio.c -o obj/landio.o

#rm obj/dphp.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c dphpc.c  -o obj/dphp.o

/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c test.c -o obj/main.o
/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc obj/landio.o obj/dphp.o obj/main.o -o test.kex

pkill tcc

test.kex

exit
