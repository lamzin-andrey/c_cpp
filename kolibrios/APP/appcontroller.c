
void onCreate() {
  // Здесь добавим наш текстовый инпут
  // Хочется


  lldIText("inp1", 10, 180, "Tests!");
  lldIText("inp2", 10, 250, "Tests two!");
  lldICheckboxC("cb1", 10, 210, "Съешь же ещё этих мягкий французских булок да выпей чаю!",0x000000, 0x000000);
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
  //lldTextPB("txt1", "Hello", 90, 300, /*pad*/8, /*brdC*/0xFFFFFF, /*bw*/4);
  //lldLabel("txt1", "Hello", 90, 300, 0x00AA00, 0xFFFFFF);


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

void onLeftMouseDown(char* id, UINT mX, UINT mY) {
}

void onRightMouseDown(char* id, UINT mX, UINT mY) {
}

void onClick(char* id, UINT mX, UINT mY) {
}

void onRightClick(char* id, UINT mX, UINT mY) {
}

void onMouseMove(char* id, UINT mX, UINT mY) {
	char dbg[255];
    sprintf(dbg, "mouse ev (%d,%d) `%s`\n", mX, mY, id);
    //logStr("log.log", dbg, "");
    //title = "Lalala";
    _ksys_set_window_title(dbg);
}
