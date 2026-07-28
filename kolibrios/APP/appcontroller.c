#include "../landlib/desktop/api/app.h"
#include "../landlib/desktop/api/mw.h"
#include "../landlib/desktop/api/env.h"
void draw_window();




void onCreate() {
  // решил добавить фрейм.
  /*frame fr;
  //uint32_t type;
  fr.type = 0;
  //uint32_t x_w;
  fr.x_w = 0;
  //f.x_w = f.x_w << 16;
  fr.x_w += 100;
  //uint32_t y_h;
  fr.y_h = 40;
  fr.y_h = fr.x_w << 16;
  fr.y_h += 100;
  //color_t ext_col;
  //f.ext_col = 0xFF0000;
  //color_t int_col;
  //f.int_col = 0x00FF00;
  //uint32_t flags;
  fr.flags = 0;
  //char* text_pointer;
  fr.text_pointer = "Hello, frame!";
  //uint32_t text_position;
  fr.text_position = 0;
  //uint32_t font_number;
  //f.font_number = 14;
  //f.font_size_y = 14;
  //uint32_t font_size_y;
  //color_t font_color;
  fr.font_color = 0x000000;
  //color_t font_bg_color;
  fr.font_bg_color = 0xFFFFFF;

  frame_draw(&fr);*/

  // Тут было все ок.
  TabIndexDefaultMode = 1;

  VScroll* vs1 = lldVScroll("vs1", -19, 0);
  vs1->hasNormal = true;

  HScroll* hs2 = lldHScroll("hs2", -19, 100);
  hs2->hasNormal = true;
  hs2->offsetX = 100;

  /*char* _appDir;
  _appDir = malloc(4096);
  sApp_dir(_appDir, 4096);
  lldIText("inp1", 10, 180, _appDir);
  free(_appDir);*/


  char* _appDir = App_dir();
  lldIText("inp1", 10, 180, _appDir);
  free(_appDir);

  lldIText("inp2", 10, 250, "Tests two!");
  lldICheckboxC("cb1", 10, 210, "Съешь ещё этих мягких французских булок да выпей же чаю!",0x000000, 0x000000);
  Img* im = lldImgC("img1", "app/i/folder32.png", 10, 300, 24, 0XFFFFFF);
  im->tabSupport = 1;
  lldImg("img2", "app/i/browser32.png", 50, 300, 32);

  StaticText* txt = lldTextPBC("txt1", "Hello1", 90, 300, /*pad*/8, /*brdC*/0xFFFFFF, /*bw*/4, /*bg*/0x00AA00, 0x000000);
  //txt->bgColor = 0x0000FF;
  txt->color = 0xFFFFFF;
  txt->fontType = FONT_TYPE14;

  StaticText* txt2 = lldTextPBC("txt2", "Hello1", 90, 350, /*pad*/8, /*brdC*/0xFFFFFF, /*bw*/4, /*bg*/0x00AA00, 0x000000);
  //txt->bgColor = 0x0000FF;
  txt2->color = 0xFFFFFF;
  txt2->fontType = FONT_TYPE14B;


  LLDButton* btn1 = lldGreenButton("btn1", "Push Me!", 90, 400);
  btn1->intId = 1;
  LLDButton* btn2 = lldButton("btn2", "Push Me 2!", 90, 430);
  btn2->intId = 2;
  LLDButton* btn3 = lldRedButton("btn3", "Maximize", 90, 460);
  btn3->intId = 3;
  LLDButton* btn4 = lldBlueButton("btn4", "Push Me!", 90, 490);
  LLDButton* btn5 = lldPrimaryButton("btn5", "Push Me!", 190, 460);
  btn5->intId = 5;

  Element el6 = cine("text", "it8", "app/i/disk32.png");
  v("it8", "Урра!!");
  char* current = stl("it8", "left", "101px");
  free(current);
  current = stl("it8", "left", "201px");
  free(current);
  stl("it8", "top", "60px");
  stl("it8", "background-color", "#AA0000");
  stl("it8", "color", "#FFFFFF");
  stl("it8", "height", "500px");
  stl("it8", "padding", "10px");

  /*Element wideButton = cine("btn", "wb0260210", "Hello cine button");
  stl("wb0260210", "height", "350px");
  stl("wb0260210", "color", "#00FF00");
  v("wb0260210", "Wide Button");*/


  /*Element wideInp = cine("icheckbox", "win0260210", "Hello cine button");
  stl("win0260210", "background-color", "#00FF00");
  stl("win0260210", "top", "30px");
  stl("win0260210", "left", "30px");
  stl("win0260210", "width", "100px");
  v("win0260210", "Wide ci");*/

  /*Element wideImg = cine("img", "wi0260210", "app/i/disk32.png");
  //stl("wi0260210", "background-color", "#FF0000");
  stl("wi0260210", "width", "250px");*/


  /*el6.txt->bgColor = 0x00AA00;
  el6.txt->color = 0xFFFFFF;
  el6.txt->savedColor = 0xFFFFFF;*/

  // Пока ее в sys controller оставим, потом перенесем в landInputs
}

void onKeyPress(char* id, uint32_t code) {
	char* v = "Key pressed";
	v = addchar(v, ' ');
	v = addstr(v, id);
	v = addchar(v, ' ');

	//code = code >> 16;
	char* sCode[255];

	sprintf(sCode, "%ld", code);
	v = addstr(v, sCode);
	_ksys_set_window_title(v);
}

void onLeftMouseDown(char* id, UINT mX, UINT mY, UINT btnId) {
	char dbg[255];
    sprintf(dbg, "mouse LD (%d,%d) `%s`, `%d`\n", mX, mY, id, btnId);
    _ksys_set_window_title(dbg);


}

void onRightMouseDown(char* id, UINT mX, UINT mY, UINT btnId) {
}

void onClick(char* id, UINT mX, UINT mY, UINT btnId) {
	char dbg[255];
    sprintf(dbg, "mouse CLICK (%d,%d) `%s`, `%d`\n", mX, mY, id, btnId);
    _ksys_set_window_title(dbg);

    if (btnId == 2) {
    	//sprintf(dbg, "OKQ! (%d,%d) `%s`, `%d`\n", mX, mY, id, btnId);

    	Element el = e("txt1");
    	if (0 == strcmp(el.type, "undefined")) {
    		//sprintf(dbg, "IUN! (%d,%d) `%s`, `%d`\n", mX, mY, id, btnId);
    	} else {
    		el.txt->text = "New vawe";

    		//sprintf(dbg, "TCT (%d,%d) `%s`, `%s`\n", mX, mY, id, el.txt->id);
    	}

    	Element e2 = e("img1");
    	if (0 != strcmp(e2.type, "undefined")) {
    		e2.img->x += 5;
    	}

    	Element inp1 = e("inp1");
    	if (0 != strcmp(inp1.type, "undefined")) {
    		v("inp1", "Ulalal");
    	}

    	Element btn1 = e("btn1");
    	if (0 != strcmp(btn1.type, "undefined")) {
    		v("btn1", "Pushed!");
    	}

    	Element cb1 = e("cb1");
    	if (0 != strcmp(cb1.type, "undefined")) {
    		v("cb1", "1");
    	}

    	/*MWmoveTo(0, 0);
    	MWresizeTo(640, 480);
    	MWsetTitle("Привет мир!");*/

    	char* path = Env_openFileDialog("Hello", "", "*.C *.TXT");
    	/*UINT sz = 255;
    	char* path;
    	path = malloc(sz);
    	sEnv_openFileDialog("Hello", "", "*.C *.TXT", path, sz);*/
    	v("txt1", path);
    	//draw_window();
    	//free(path);

    	//el.txt->text = "New wave";
    }// /if btnId == 2
    if (btnId == 3) {
    	// test save file dialog
    	//char* path3 = Env_saveFileDialog("Hello", "", "*.C *.SH");
    	//v("txt1", path3);

    	//_ksys_change_window(0, 0, 1024, 700);
    	MW_maximize();

    }
    if (btnId == 5) {
    	char* path2 = Env_openDirectoryDialog("Hello", "/tmp0/1/");
    	/*UINT sz = 255;
    	char* path2;
    	path2 = malloc(sz);
    	sEnv_openDirectoryDialog("Hello", "/tmp0/1/", path2, sz);*/
    	v("txt1", path2);
    	//draw_window();
    	//free(path2);
    }

}

void onRightClick(char* id, UINT mX, UINT mY, UINT btnId) {
}

void onMouseMove(char* id, UINT mX, UINT mY, UINT btnId) {
	char dbg[255];
    sprintf(dbg, "mouse ev (%d,%d) `%s`, `%d`\n", mX, mY, id, btnId);
    //logStr("log.log", dbg, "");
    //title = "Lalala";
    _ksys_set_window_title(dbg);


}


void onMouseWheel(char* id, int wheel, UINT mX, UINT mY, UINT btnId, UINT wheels) {
	char dbg[255];
    sprintf(dbg, "mouse LD (%d,%d) id = `%s`, btnId = `%d`, wheels = %d\n", mX, mY, id, btnId, wheel);
    _ksys_set_window_title(dbg);

    if (mX < 100) {
    	UINT p = landDefaultVScroll("vs1", wheel, wheels);
    	UINT vp = landDefaultHScroll("hs2", wheel, wheels);
    	sprintf(dbg, "mouse LD (%d,%d) id = `%s`, btnId= `%d`, wh= %d, vsp= %ld, hsp = %ld\n", mX, mY, id, btnId, wheel, p, vp);
    	_ksys_set_window_title(dbg);
    }

}