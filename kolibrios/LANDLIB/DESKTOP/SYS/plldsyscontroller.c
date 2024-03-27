// "Private" functions
char* getIdByMousePos(UINT mX, UINT mY) {
	UINT i, x, y, w, h;
	for (i = 0; i <= LLDO_ITERATOR; i++) {
		char* type = LLDO_TYPES[i];
		char* id = "";
		int elFound = 0;
		if (0 == strcmp("img", type)) {
			Img img = LLDO_IMG[i];
			x = img.x;
			y = img.y;
			w = img.w;
			h = img.h;
			elFound = 1;
			id = addstr(id, img.id);
		}
		if (0 == strcmp("icheckbox", type)) {
			Icheckbox cb = LLDO_CHB[i];
			//id = cb.id;
			id = addstr(id, cb.id);
			x = cb.x;
			y = cb.y;
			w = cb.w;
			h = cb.h;
			elFound = 1;
		}
		if (0 == strcmp("itext", type)) {
			Itext t = LLDO_INP_TEXT[i];
			//id = t.id;
			id = addstr(id, t.id);
			x = t.ebox.left;
			y = t.ebox.top;
			w = t.ebox.width;
			h = t.ebox.height;
			elFound = 1;
		}
		if (0 == strcmp("text", type)) {
			StaticText st = LLDO_TEXT[i];
			//id = t.id;
			id = addstr(id, st.id);
			x = st.x;
			y = st.y;
			w = st.w + (st.padding + st.borderWidth) * 2;
			h = st.h + (st.padding + st.borderWidth) * 2;
			elFound = 1;
		}

		if (elFound == 1) {
			if (mX >= x && mX <= (x + w)) {
				if (mY >= y && mY <= (y + h)) {
					return id;
				}
			}
		} // end if (elFound == 1)
	}// end for

	return "undefined";
}

void landDrawStaticText(StaticText t) {
	if (t.fontType == FONT_TYPE14 || t.fontType == FONT_TYPE14B) {

	    if (t.fontType == FONT_TYPE14) {
	    	t.h = 14;
	    	t.color = t.color | FONT_TYPE14;
	    	t.w = 8 * strlen(t.text);
	    }
	    if (t.fontType == FONT_TYPE14B) {
	    	t.h = 16;
	    	t.color = t.color | FONT_TYPE14B;
	    	t.w = 11 * strlen(t.text);
	    }

	} else {
		t.h = 10;
	    t.color = t.savedColor;
	    t.w = 6 * strlen(t.text);
	}

	//border
	if (t.borderWidth > 0) {
		_ksys_draw_bar(t.x, t.y, t.w + (t.padding * 2) + (t.borderWidth * 2), t.h + (t.padding * 2) + (t.borderWidth * 2), t.borderColor);
	}
    _ksys_draw_bar(t.x + t.borderWidth, t.y + t.borderWidth, t.w + (t.padding * 2), t.h + (t.padding * 2), t.bgColor);
	_ksys_draw_text((const char*)t.text, t.x + t.padding + t.borderWidth, t.y + t.padding + t.borderWidth, strlen(t.text), t.color);

}