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

char* v(char* id, char* val) {
	Element el = e(id);
	if (0 == strcmp("text", el.type)) {
		if (NULL != val) {
			el.txt->text = val;
		}

		return el.txt->text;
	}

	if (0 == strcmp("btn", el.type)) {
		if (NULL != val) {
			el.btn->text = val;
		}

		return el.btn->text;
	}

	if (0 == strcmp("img", el.type)) {
		if (NULL != val) {
			el.img->src = val;
		}

		return el.img->src;
	}

	if (0 == strcmp("itext", el.type)) {
		if (NULL != val) {
			edit_box ebox = el.iText->ebox;
			el.iText->text = val;
			edit_box_set_text(&ebox, val);
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
			return "1";
		}
		return "0";
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

/*char* hide(char* id);
char* show(char* id);
char* storage(char* k, char* val);*/