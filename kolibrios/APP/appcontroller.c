#include "../landlib/desktop/api/mw.h"
#include "../landlib/desktop/api/env.h"
void draw_window();

void onCreate() {
  TabIndexDefaultMode = 1;

  VScroll* vs1 = lldVScroll("vs1", -19, 0);
  vs1->hasNormal = true;

  HScroll* hs2 = lldHScroll("hs2", -19, 100);
  hs2->hasNormal = true;
  hs2->offsetX = 100;

  lldIText("inp1", 10, 180, "Tests!");

  lldIText("inp2", 10, 250, "Tests two!");
  lldICheckboxC("cb1", 10, 210, "���� ��� ��� ��� �࠭��᪨� �㫮� �� �믥� �� ��!",0x000000, 0x000000);
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
  LLDButton* btn2 = lldButton("btn2", "Push Me!", 90, 430);
  btn2->intId = 2;
  LLDButton* btn3 = lldRedButton("btn3", "Push Me!", 90, 460);
  LLDButton* btn4 = lldBlueButton("btn4", "Push Me!", 90, 490);
  LLDButton* btn5 = lldPrimaryButton("btn5", "Push Me!", 190, 460);


  // ���� �� � sys controller ��⠢��, ��⮬ ��७�ᥬ � landInputs
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

    	MWmoveTo(0, 0);
    	MWresizeTo(640, 480);
    	MWsetTitle("�ਢ�� ���!");
    	char* path = EnvopenDirectoryDialog("Hello", "/sd0/1");
    	v("txt1", path);

    	draw_window();
    	//el.txt->text = "New wave";
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