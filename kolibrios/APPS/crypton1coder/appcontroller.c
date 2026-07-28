#include "../../landlib/desktop/api/app.h"
#include "../../landlib/desktop/api/mw.h"
#include "../../landlib/desktop/api/env.h"
//#include "../../landlib/crypton/crypton.h"
void draw_window();

int inProc = 0;


void onCreate() {

  TabIndexDefaultMode = 0;

  StaticText* label = lldTextPBC("label", "Введите пароль", 2, 10, /*pad*/8, /*brdC*/0x000000, /*bw*/0, /*bg*/0xEFE9D6, 0x000000);
  lldIText("iPassword", 10, 36, "");
  LLDButton* bOk = lldPrimaryButton("bOk", "OK", 50, 80);
  bOk->intId = 2;
  LLDButton* bCancel = lldRedButton("bCancel", "Отмена", 100, 80);
  bCancel->intId = 1;
  stl("iPassword", "width", "190px");


  lldTextPBC("hErr", "", 12, 60, /*pad*/4, /*brdC*/0x000000, /*bw*/0, /*bg*/0xEFE9D6, 0xAA0000);

  MWsetTitle("Land Crypt0n 1 decoder");
  MWresizeTo(220, 150);


  //lldTextPBC("dbg", "Debug", 10, 110, /*pad*/8, /*brdC*/0x000000, /*bw*/0, /*bg*/0xEFE9D6, 0x000000);
  //MWresizeTo(600, 320);

}

void onKeyPress(char* id, uint32_t code) {

}

void onLeftMouseDown(char* id, UINT mX, UINT mY, UINT btnId) {

}

void onRightMouseDown(char* id, UINT mX, UINT mY, UINT btnId) {
}

void onClick(char* id, UINT mX, UINT mY, UINT btnId) {
	//char dbg[255];
    //sprintf(dbg, "mouse CLICK (%d,%d) `%s`, `%d`\n", mX, mY, id, btnId);
    //_ksys_set_window_title(dbg);

    if (es(id, "bOk") && btnId != 1) {
    	if (inProc) {
    		return;
    	}
    	inProc = 1;

    	char* path = "";
    	for (UINT i = 1; i < LLD_APP_ARGC; i++) {
    		path = addstr(path, LLD_APP_ARGS[i]);
    	}
    	v("hErr", "");
    	draw_window();

    	if (strlen(path) > 0 && file_exists(path)) {
    		Element el = e("iPassword");
    		if (es(trim(el.iText->ebox.text), "")) {
    			v("hErr", "Пароль не может быть пустым");
    			draw_window();
    			inProc = 0;
    			return;
    		}

    		char* data = file_get_contents(path);
    		//data = addstr("lopata", data);

    		char* newFile = str_replace(".dec", ".enc", trim(path));
    		newFile = trim(newFile);

    		char* passFile = App_dir();
    		passFile = addstr(passFile, "/lua/crypton/pass.txt");
    		file_put_contents(passFile, el.iText->ebox.text);
    		free(passFile);

    		char* cFile = App_dir();
    		cFile = addstr(cFile, "/lua/crypton/input.txt");
    		file_put_contents(cFile, data);
    		free(data);

    		char* oFile = str_replace("input.txt", "output.txt", cFile);
    		free(cFile);

    		if (file_exists(oFile)) {
    			unlink(oFile);
    		}

    		char* luaFile = App_dir();
    		luaFile = addstr(luaFile, "/lua/crypton/crypton1decoder.lua");

    		char* luaTpl = addstr(luaFile, ".tpl");
    		if (!file_exists(luaTpl)) {
    			v("hErr", "Не found template");
    			stl("hErr", "color", "#AA0000");
    			draw_window();
    			inProc = 0;
    			return;
    		}
    		char* luaCode = file_get_contents(luaTpl);
    		luaCode = str_replace("{{appdir}}", App_dir(), luaCode);
    		if (file_exists(luaFile)) {
    			unlink(luaFile);
    		}
    		_ksys_file_create(luaFile);
    		file_put_contents(luaFile, luaCode);
    		free(luaTpl);
    		free(luaCode);

    		Env_exec1("/kolibrios/develop/lua/lua", luaFile);
    		//free(luaFile);

    		for (int i = 0; i < 5; i++) {
    			if (file_exists(oFile)) {
    				break;
    			}
    			v("hErr", "Расшифровываем...");
	    		stl("hErr", "color", "#0000AA");
	    		draw_window();
    			sleep(1);
    		}

    		if (!file_exists(oFile)) {
    			v("hErr", "Неверный пароль");
    			stl("hErr", "color", "#AA0000");
    			draw_window();
    			inProc = 0;
    			return;
    		}

    		char* cdata = file_get_contents(oFile);

    		int offset = 6;
    		char* start = substr(cdata, 0, &offset);
    		if (!es(start, "lopata")) {
    			v("hErr", "Неверный пароль");
    			stl("hErr", "color", "#AA0000");
    			draw_window();
    			return;
    		}
    		cdata = substr(cdata, offset, NULL);

    		file_put_contents(newFile, cdata);
    		free(cdata);
    		free(newFile);
    		free(path);

    		v("hErr", "Готово. Выход через три секунды.");
    		stl("hErr", "color", "#00AA00");
    		draw_window();
    		sleep(3);
			App_quit();
			inProc = 0;
			return;
    		//v("dbg", el.iText->ebox.text);
    		//v("dbg", oFile);
    		//draw_window();

    	} else {
    		v("hErr", "Не найден файл.");
    		draw_window();
    		inProc = 0;
    	}

		inProc = 0;
    	return;
    }

    if (es(id, "bCancel")) {
    	App_quit();
    	return;
    }

}

void onRightClick(char* id, UINT mX, UINT mY, UINT btnId) {
}

void onMouseMove(char* id, UINT mX, UINT mY, UINT btnId) {

}


void onMouseWheel(char* id, int wheel, UINT mX, UINT mY, UINT btnId, UINT wheels) {


}