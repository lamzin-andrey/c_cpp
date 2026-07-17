#SHS


rm testcrypt.kex

#rm obj/landio.o
/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c ../dummyphpc/landio.c -o obj/landio.o


rm obj/dphp.o
/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c ../dummyphpc/dphpc.c  -o obj/dphp.o


rm obj/crypton.o
/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c crypton.c -o obj/crypton.o

rm obj/main.o
/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c main.c -o obj/main.o

/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc obj/landio.o obj/dphp.o obj/crypton.o obj/main.o -o testcrypt.kex
testcrypt.kex

pkill tcc
#pkill shell
