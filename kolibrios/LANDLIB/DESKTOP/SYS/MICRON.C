#include "micron.h"

Element e(char* id) {
	long i;
	char* type;

	Element el;
	el.type = "undefined";

	for (i = 0; i <= LLDO_ITERATOR; i++) {
		type = LLDO_TYPES[i];
		if (0 == strcmp("itext", type)) {
			Itext* itext = &LLDO_INP_TEXT[i];
			if (0 == strcmp(id, itext->id)) {
				el.type = type;
				el.iText = itext;
				return el;
			}
		}

		if (0 == strcmp("text", type)) {
			StaticText* text = &LLDO_TEXT[i];
			if (0 == strcmp(id, text->id)) {
				el.type = type;
				el.txt = text;
				return el;
			}
		}

		if (0 == strcmp("icheckbox", type)) {
			Icheckbox* cb = &LLDO_CHB[i];
			if (0 == strcmp(id, cb->id)) {
				el.type = type;
				el.cb = cb;
				return el;
			}
		}

		if (0 == strcmp("img", type)) {
			Img* img = &LLDO_IMG[i];
			if (0 == strcmp(id, img->id)) {
				el.type = type;
				el.img = img;
				return el;
			}
		}

		if (0 == strcmp("btn", type)) {
			LLDButton* b = &LLDO_BTN[i];
			if (0 == strcmp(id, b->id)) {
				el.type = type;
				el.btn = b;
				return el;
			}
		}

		if (0 == strcmp("vscroll", type)) {
			VScroll* vsc = &LLDO_VSCROLL[i];
			if (0 == strcmp(id, vsc->id)) {
				el.type = type;
				el.vs = vsc;
				return el;
			}
		}

		if (0 == strcmp("hscroll", type)) {
			HScroll* vsc = &LLDO_HSCROLL[i];
			if (0 == strcmp(id, vsc->id)) {
				el.type = type;
				el.hs = vsc;
				return el;
			}
		}

	}

	return el;
}

char* stl(char* id, char* name, char* value)
{
	Element r = e(id);
	if (0 == strcmp("undefined", r.type)) {
		return "";
	}

	if (0 == strcmp("top", name)) {
		return _setY(r, value);

	}

	if (0 == strcmp("left", name)) {
		return _setX(r, value);
	}

	if (es("width", name)) {
		return _setW(r, value);
	}

	if (es("height", name)) {
		return _setH(r, value);

	}

	if (es("background-color", name)) {
		return _setBgColor(r, value);

	}
	if (es("color", name)) {
		return _setColor(r, value);

	}

	if (es("padding", name)) {
		return _setPadding(r, value);
	}

}

char* _setColor(Element el, char* val) {
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->color = _hexdec(val);
			el.txt->savedColor = _hexdec(val);
			free(val);
		}
		char* s =  dechex(el.txt->color); //TODO dphp
		s = addstr("#", s);
		return s;
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			el.btn->color = _hexdec(val);;
			el.btn->savedColor = _hexdec(val);;
			free(val);
		}
		return strval(el.btn->color);
	}

	/*if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			el.img->h = intval(val);
		}
		return strval(el.img->h);
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			el.iText->ebox.height = intval(val);
		}
		return strval(el.iText->ebox.height);
	}

	if (0 == strcmp("icheckbox", el.type)) {

		if (NULL != val) {
			el.cb->h = intval(val);
		}
		return strval(el.cb->h);
	}*/
	if (NULL != val) {
		free(val);
	}
	return "";
}

char* _setPadding(Element el, char* val) {
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->padding = (char)intval(val);
			free(val);
		}
	}
	return strval(el.txt->padding);
}

char* _setBgColor(Element el, char* val) {
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->bgColor = _hexdec(val);
			free(val);
		}
		char* s =  dechex(el.txt->bgColor); //TODO dphp
		s = addstr("#", s);
		return s;
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			el.btn->bgColor = _hexdec(val);;
		}
		return strval(el.btn->bgColor);
	}

	/*if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			el.img->h = intval(val);
		}
		return strval(el.img->h);
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			el.iText->ebox.height = intval(val);
		}
		return strval(el.iText->ebox.height);
	}

	if (0 == strcmp("icheckbox", el.type)) {

		if (NULL != val) {
			el.cb->h = intval(val);
		}
		return strval(el.cb->h);
	}*/
	if (NULL != val) {
		free(val);
	}
	return "";
}

UINT _hexdec(char* val) {
	val = str_replace("#", "", val);
	if (strlen(val) != 6) {
		return 0;
	}
	return hexdec(val);
}

char* _setH(Element el, char* val) {
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->h = intval(val);
		}
		return strval(el.txt->h);
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			el.btn->h = intval(val);
		}
		return strval(el.btn->h);
	}

	if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			el.img->h = intval(val);
		}
		return strval(el.img->h);
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			el.iText->ebox.height = intval(val);
		}
		return strval(el.iText->ebox.height);
	}

	if (0 == strcmp("icheckbox", el.type)) {

		if (NULL != val) {
			el.cb->h = intval(val);
		}
		return strval(el.cb->h);
	}
	return "";
}

char* _setW(Element el, char* val) {
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->w = intval(val);
		}
		return strval(el.txt->w);
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			el.btn->w = intval(val);
		}
		return strval(el.btn->w);
	}

	if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			el.img->w = intval(val);
		}
		return strval(el.img->w);
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			el.iText->ebox.width = intval(val);
		}
		return strval(el.iText->ebox.width);
	}

	if (0 == strcmp("icheckbox", el.type)) {

		if (NULL != val) {
			el.cb->w = intval(val);
		}
		return strval(el.cb->w);
	}
	return "";
}

char* _setX(Element el, char* val) {
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->x = intval(val);
		}
		return strval(el.txt->x);
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			el.btn->x = intval(val);
		}
		return strval(el.btn->x);
	}

	if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			el.img->x = intval(val);
		}
		return strval(el.img->x);
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			el.iText->ebox.left = intval(val);
		}
		return strval(el.iText->ebox.left);
	}

	if (0 == strcmp("icheckbox", el.type)) {

		if (NULL != val) {
			el.cb->x = intval(val);
		}
		return strval(el.cb->x);
	}
	return "";
}

char* _setY(Element el, char* val) {
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->y = intval(val);
			free(val);
		}
		return strval(el.txt->y);
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			el.btn->y = intval(val);
			free(val);
		}
		return strval(el.btn->y);
	}

	if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			el.img->y = intval(val);
			free(val);
		}
		return strval(el.img->y);
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			el.iText->ebox.top = intval(val);
			free(val);
		}
		return strval(el.iText->ebox.top);
	}

	if (0 == strcmp("icheckbox", el.type)) {

		if (NULL != val) {
			el.cb->y = intval(val);
			free(val);
		}
		return strval(el.cb->y);
	}
	return "";
}

Element createIfNotExists(char* type, char* id, char* path)
{
	Element r = e(id);

	if (0 != strcmp("undefined", r.type)) {
		return r;
	}

	if (0 == strcmp("btn", type)) {
		LLDButton* btn = lldButton(id, "Push Me!", 10, 40);
  		btn->intId = currentBtnId;
  		currentBtnId++;
  		r = e(id);
  		return r;
	}

	if (0 == strcmp("img", type)) {
		Img* im = lldImg(id, path, 0, 0, 32);
  		r = e(id);
  		return r;
	}

	if (0 == strcmp("itext", type)) {
		lldIText(id, 0, 0, "");
  		r = e(id);
  		return r;
	}

	if (0 == strcmp("text", type)) {
		lldText(id, "Static Text", 0, 0);
  		r = e(id);
  		return r;
	}

	if (0 == strcmp("icheckbox", type)) {
		lldICheckboxC(id, 0, 0, path, 0x000000, 0x000000);
  		r = e(id);
  		return r;
	}

	return r;
}

char* v(char* id, char* val) {
	Element el = e(id);
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			if (NULL != el.txt->text) {
				free(el.txt->text);
			}
			el.txt->text = val;
		}

		return el.txt->text;
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			if (NULL != el.btn->text) {
				free(el.btn->text);
			}
			el.btn->text = val;
		}

		return el.btn->text;
	}

	if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			if (NULL != el.img->src) {
				free(el.img->src);
			}
			el.img->src = val;
		}

		return el.img->src;
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			//edit_box ebox = el.iText->ebox;
			/*if (NULL != el.iText->text) {
				free(el.iText->text);
				el.iText->text = NULL;
			}*/
			el.iText->text = val;
			edit_box_set_text(&el.iText->ebox, val);
		}

		return el.iText->text;
	}

	if (0 == strcmp("icheckbox", el.type)) {
		if (NULL != val) {
			el.cb->state = 1;
			//el.iText->text = val;
			//checkbox_mouse2(&cb);
		} else {
			el.cb->state = 0;
		}

		if (el.cb->state == 1) {
			return "On";
		}
		return "Off";
	}

	return "";

}

BOOL isFocused(char* id) {
	Element el = e(id);

	if (0 == strcmp("img", el.type)) {

		return el.img->isInFocus;
	}

	if (0 == strcmp("btn", el.type)) {

		return el.btn->isInFocus;
	}

	if (0 == strcmp("itext", el.type)) {

		return el.iText->isInFocus;
	}

	if (0 == strcmp("icheckbox", el.type)) {

		return el.cb->isInFocus;
	}

	return false;
}

void setFocus(char* id, BOOL val) {
	Element el = e(id);


	if (0 == strcmp("btn", el.type)) { // TODO getter
		focusedLLDButton = el.btn;
		focusedTabIndex = el.btn->tabIndex;
		el.btn->isInFocus = val;

		return;
	}

	if (0 == strcmp("img", el.type)) {
		focusedImg = el.img;
		focusedTabIndex = el.img->tabIndex;
		el.img->isInFocus = val;

		return;
	}

	if (0 == strcmp("itext", el.type)) {
		focusedItext = el.iText;
		focusedTabIndex = el.iText->tabIndex;
		el.iText->isInFocus = val;
		if (val == true) {
			el.iText->ebox.flags = ed_focus;
		} else {
			el.iText->ebox.flags = 0;
		}
		edit_box_draw(&el.iText->ebox);
		draw_window();

		return;
	}

	if (0 == strcmp("icheckbox", el.type)) {
		focusedIcheckbox = el.cb;
		focusedTabIndex = el.cb->tabIndex;
		el.cb->isInFocus = val;

		return;
	}

}

Element cine(char* type, char* id, char* path)
{
	return createIfNotExists(type, id, path);
}

/*char* hide(char* id);
char* show(char* id);
char* storage(char* k, char* val);*/