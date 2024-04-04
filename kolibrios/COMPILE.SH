#SHS

rm obj/main.o
rm test.kex

#rm obj/landio.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landlib/dummyphpc/landio.c -o obj/landio.o

#rm obj/dphp.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landlib/dummyphpc/dphpc.c  -o obj/dphp.o

#rm obj/landimage.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landlib/desktop/sys/landimage.c  -o obj/landimage.o

#rm obj/landinput.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landlib/desktop/sys/landinput.c  -o obj/landinput.o

rm obj/lldenv.o
/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landlib/desktop/api/env.c  -o obj/lldenv.o

#rm obj/lldmw.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landlib/desktop/api/mw.c  -o obj/lldmw.o


#rm obj/micron.o
#/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c landlib/desktop/sys/micron.c  -o obj/micron.o


/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc -c main.c -o obj/main.o
/sd0/1/lives/kolibri/isoContent/kolibrios/develop/tcc/tcc obj/landio.o obj/dphp.o obj/landinput.o obj/landimage.o obj/micron.o obj/lldmw.o obj/lldenv.o obj/main.o -o gui.kex -lbox_lib -limg -ldialog

gui.kex

pkill tcc
pkill shell

exit
