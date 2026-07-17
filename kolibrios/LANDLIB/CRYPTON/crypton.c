#include "crypton.h"
// Добился работы в браузере.
// Далее реализовать недостающие по здешнему TODO функции в C

// Кодировка, в которой приложение будет отдавать сюда данные.
// Изменить, если ваше приложение будет передавать сюда не UTF-8
// И сохранить этот файл в рабочей кодировке

// define LAND_CRYPTON_WORK_ENCODING "UTF-8";

// Не влияет на стойкость. Это просто начало строки, по которому алгоритм определяет,
//  удалось ли расшифровать строку.  CRYPTON_FW добавляется в начало шифруемой строки перед шифрованием
//   и удаляется из неё после расшифровки.

SLandEncrypt LandCrypton = {false, {0}, 1, 0};

//LandCrypton.abcIsInitalize = false;
//LandCrypton.Map = {0};
//UINT L = 0;
//LandCrypton.Map = uipush(LandCrypton.Map, 0, &L);




char*  LandCryptonCrypt(char* s, char* password) {
    char* t = "";
    char*  c = "";
    char* o = "";
    char* e = "";
    UINT f, iO, h, g, iE, d, k, n;
    int aLen = 0;
    char** a;
    SVocArg q;
    //a = {""};
    if (!password) {
		password = "";
	}
    t = addstr(LAND_CRYPTON_FW, s);
    // Это не нужно, так как работать будем с однобайтной кодировкой
    //t = mb_convert_encoding($t, CP1251, LAND_CRYPTON_WORK_ENCODING);
    c = password;

    f = 0;
    // a = [];
    //q = new StdClass();
    LandCryptonInitAbc(c, &q);
    for (h = 0; h < strlen(t); h++) {
        o = LandCryptonCharCode(t, h, q);

        if(o[0] == 'n') {
            g = 1;
            o = str_replace("n", "", o);
        } else {
			g = 0;
		}
        iO = intval(o);
        // f = f < strlen(c) ? f : 0;
        if (f >=  strlen(c)) {
        	f = 0;
    	}

        e = LandCryptonCharCode(c, f, q);
        e = str_replace("n", "", e);

        iE = intval(e);
        d = iO + iE;
        LandCryptonGetLimit(d, &q, g);
        k = q.L;
        n = q.b;
        if (d > k) {
            iO = n + d - k;
        } else {
            iO = d;
        }
        if(g) {
            o = addstr("n", strval(iO));
        } else {
			o = strval(iO);
		}
        //$a.push($o);
        if (h == 0) {
			a[0] = o;
			aLen++;
		} else {
			a = push(a, o, aLen);
			aLen++;
		}

        f++;
    }
    return implode(";", a, aLen);
}

char* LandCryptonDecrypt(char* s, char* password) {
    //password = password ? password : "";
    if (NULL == password) {
    	password = "";
	}
    s = LandCrypton_decrypt(s, password);


    if (strpos(s, LAND_CRYPTON_FW) != 0) {
        //throw new Error("Error decode!\n" + $s);
        printf("Error decode!\n%s\n", s);
        exit(0);
    }
    s = substr(s, strlen(LAND_CRYPTON_FW), NULL);
    return s;
}

void  LandCryptonInitAbc(char* password, SVocArg*f) {
    char* a = "";
    char* n = "";
    UINT sz, g, e, dI, I, l, L, oL;
    UINT* c = {0};
    int d;
    char ch;
    long di;

    a = password;
    n = addstr(n, "012 3456789\n\r?!,.абвгдеёжзийклмнопрстуфхцчшщъыьэюяЙЦУКЕНГФЫВАПРОЛДЖЭЯЧСМИТЬБЮШЩЗХЪasdfghjklzxcvbnm-+qwertyuiopZXCVBNMASDFGHJKLQWERTYUIOP():/`=*[];'\t~@#$%^&_{}|\"<>");
    if (LandCrypton.abcIsInitalize) {
		 f->abc = n;
         f->m = LandCrypton.Map;
         f->msz = LandCrypton.L;
        return;
    }
    if(false == LandCryptonValidPassword(a, n)){
        //throw new Error("Invalid password");
        printf("Invalid password");
        exit(0);
    }
    sz = strlen(n);


    c[0] = 0;
    L = 1;
    for(g = 0; g < sz; g++){
        //c[g] = g;
        if (g == 0) {
			c[g] = g;
		} else {
			c = uipush(c, g, &L);
		}
    }

    // printf("L = %d\n", (int)L);
    e = 0;
    sz = strlen(a);
    for(g = 0; g < sz; g++){
        if(e > sz - 1){
            e = 0;
        }
        ch = a[e];
        char* chs = "";
        chs = addchar(chs, ch);

        di = strpos(n, chs); //pos symbol of password in abc
        dI = c[di];			 //current code  `di` in c
        I = c[g];			// use firts `sz` codes
        l = I + dI;			// calc new code
        // l = l > strlen(n) - 1 ? l - strlen(n) : l;
        if (l > strlen(n) - 1) {
        	l = l - strlen(n);
        	// printf("new l = %u\n", l);
    	}
    	// printf("for l = %u", l);
        d = LandCryptonArrIndexOf(c, l, L);
        //printf("got code = %d\n", d);

        c[g] = l;
        if (d > -1) {
			if (d < L) {
				c[d] = I;
			} else {
				printf("LandCryptonArrIndexOf return index more then L, exit LandCryptonInitAbc second for.");
				exit(0);
			}
		} else {
			printf("LandCryptonArrIndexOf return index -1, exit");
			exit(0);
		}
        e++;
    }
    f->abc = n;

    LandCrypton.Map = c;
    LandCrypton.L = L;
    f->m = c;
    f->msz = L;

    LandCrypton.abcIsInitalize = true;
}

int LandCryptonArrIndexOf(UINT* a, UINT b, UINT L) {
    UINT sz, c;
    sz = L;
    for(c = 0; c < sz; c++){
        if (a[c] == b){
            return c;
        }
    }
    return -1;
}

BOOL  LandCryptonValidPassword(char* password, char* abc) {
    char* bs = "";
    int sz, a, n;
    char ch;

    sz = strlen(password);
    bs = addstr(bs, "0");
    for(a = 0; a < sz; a++){
        ch = password[a];
        bs[0] = ch;
        n = strpos(abc, bs);
        if(-1 == n){
            return false;
        }
    }
    return true;
}

char* LandCrypton_decrypt(char* t, char* password) {
    char* c;
    char* a = "";
    char* e = "";
    char* o = "";
    char** at;
    int len, f, h, ie, io, g, d, k, n;

   char* comment1 = "Здесь была определена переменная len; для получения длины";

   c = password;
   at = explode(";", t, &len);
   f = 0;
   SVocArg q;

   LandCryptonInitAbc(c, &q);
   for(h = 0; h < len; h++){
        //f = f < strlen(c) ? f : 0;
        if (f >= strlen(c)) {
        	f = 0;
        }
        e = LandCryptonCharCode(c, (UINT)f, q);
        e = str_replace("n", "", e);
        o = (char*)at[h];
        char tch = o[0];
        if(strlen(o) > 0 && tch == 'n') {
            g = 1;
            o = str_replace("n", "", o);
        } else {
            g = 0;
        }
        io = intval(o);
        ie = intval(e);
        d = io - ie;
        k = LandCryptonGetLimit(io, &q, g);
        n = q.b;
        if (d < n){
            d = k - abs(d - n);
            io = d;
        } else {
            io = d;
        }
        char cho = LandCryptonFromCharCode(io, g, q);
        char* tcho = "";
        tcho = addstr(tcho, "0");
        tcho[0] = cho;
        //$a += strval($o);
        a = addstr(a, tcho);
        f++;
    }
    return a;
}

char LandCryptonFromCharCode(int e, int a, SVocArg b) {
    int d;
    if(a){
        return chr(e);
    }
    d = LandCryptonArrIndexOf(b.m, e - 1, b.msz);
    return b.abc[d];
}

char*  LandCryptonCharCode(char* h, unsigned int f, SVocArg d) {
    char* buf = "";
    char* g;
    int e;
    char ch;

    g = (char*)d.abc;
    buf = addstr(buf, "0");
    buf[0] = h[f];

    e = (int)strpos(g, buf);
    if(e != -1){
        e = d.m[e];
        return strval(e + 1);
    }
    ch = h[f];
    return "n" + ord(ch);
}

unsigned int  LandCryptonGetLimit(int a, SVocArg* c, int b) {
    if(b){
        return LandCryptonGetLimitN(a, c);
    }
     c->L = strlen(c->abc);

     c->b = 1;

     return c->L;

}

int  LandCryptonGetLimitN(int d, SVocArg* f) {
    int e[] = {9,125,1025,1103};
    int c, a;



    if (d > e[0] && d < e[1]){
        c = e[1];
        a = e[0];
    } else {
        if(d >= e[2] && d <= e[3]){
            c = e[3];
            a = e[2];
        } else {
            c = PHP_INT_MAX; // TODO on C define PHP_INT_MAX = INT_MAX; #include <limits.h>
            a = 0;
        }
    }
     f->L = c;

     f->b = a;

    return c;
}

// simple test
/*$s $pass, $cr, $de;
$s = "Как делишки!";
$pass = '1Io01545';
$cr = LandCryptonCrypt($s, $pass);
console.log($cr + "\n\n");
$de = LandCryptonDecrypt($cr, $pass);
console.log($de + "\n");*/


