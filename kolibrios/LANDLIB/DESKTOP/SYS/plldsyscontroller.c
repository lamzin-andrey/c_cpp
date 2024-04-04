// "Private" functions
char* getIdByMousePos(UINT mX, UINT mY, long* btnId, char* rType) {
	UINT i, x, y, w, h;
	long intId = -1;
	for (i = 0; i <= LLDO_ITERATOR; i++) {
		char* type = LLDO_TYPES[i];
		strcpy(rType, type);
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

		if (0 == strcmp("btn", type)) {
			LLDButton b = LLDO_BTN[i];
			id = addstr(id, b.id);
			x = b.x;
			y = b.y;
			w = b.w + 24;
			h = b.h;
			elFound = 1;
			intId = b.intId;
		}

		if (elFound == 1) {
			if (mX >= x && mX <= (x + w)) {
				if (mY >= y && mY <= (y + h)) {
					if (intId != -1) {
						*btnId = intId;
					}
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


void landDrawButton(LLDButton b) {
	b.h = 28;
	b.color = b.savedColor;
	b.w = 6 * strlen(b.text) + 24;

	char dY = 0;
	if (b.isInFocus) {
		b.h += 2;
		b.w += 2;
		dY = 1;
	}

    //_ksys_draw_button(t.x + t.borderWidth, t.y + t.borderWidth, t.w + (t.padding * 2), t.h + (t.padding * 2), t.bgColor);
    _ksys_define_button(b.x, b.y, b.w, b.h, (uint32_t)b.intId, b.bgColor);
	_ksys_draw_text((const char*)b.text, b.x + 12, b.y + 10, strlen(b.text), b.color);

}


void landDrawCheckboxP(Icheckbox* cb) {

	UINT textH = 10;
    UINT textW = 8 * strlen(cb->label);
    UINT color = 0x000000;
    char* src = "app/i/sys/cb/un.png";

    if (cb->state == 0) {
		color = 0x000000;
		src = "app/i/sys/cb/un.png";
	} else if (cb->state == 1) {
		color = 0x00AA00;
		src = "app/i/sys/cb/ch.png";
	} else if (cb->state == 5) {
		src = "app/i/sys/cb/sq.png";
		color = 0x00AA00;
	}

	landDrawImageWH(src, cb->x, cb->y, cb->wI, cb->h);
	_ksys_draw_text((const char*)cb->label, cb->x + cb->wI + cb->marginRight, cb->y, strlen(cb->label), color | FONT_TYPE14);
}

void landDrawCheckbox(Icheckbox cb) {

	landDrawCheckboxP(&cb);
}

void landCheckboxOnClickDefaultHandler(long i) {
	if (i == -1) {
		return;
	}
	Icheckbox* cb = &LLDO_CHB[i];
	if (cb->state == 1) {
		cb->state = 0;
	} else {
		cb->state = 1;
	}

	landDrawCheckboxP(cb);
}


void landDrawVScroll(scrollbar* sc, VScroll vs) {
	int x = vs.x;
	if (x < 0) {
    	sc->xpos  = proc_info.winx_size + x;
	} else {
		sc->xpos  = x;
	}
    sc->ypos  = vs.offsetY;

    if (vs.h == 0) {
    	sc->ysize = proc_info.winy_size - 3 - sc->ypos;
    } else {
    	sc->ysize = vs.h;
    }

    if (vs.hasNormal == true) {
    	sc->ysize -= LLD_SCROLL_WIDTH;
    }

    scrollbar_v_draw(sc);
}

UINT landDefaultVScroll(char* id, int wheel, UINT wheels) {
	Element el = e(id);

	if (NULL == el.vs) {
		return 0;
	}

	//scrollbar_v_mouse(&el.vs->sc);

	unsigned int scroll_strong = 10;
	if (wheels & 0xFFFF) {
	  if ((short)wheels > 0) {
	    el.vs->sc.position += scroll_strong;
	    if (el.vs->sc.position > el.vs->sc.max_area - el.vs->sc.cur_area) {
	      el.vs->sc.position = el.vs->sc.max_area - el.vs->sc.cur_area;
	    }
	  } else if ((short)wheels < 0 && el.vs->sc.position > 0) {
	    el.vs->sc.position -= scroll_strong;
	    if ((int)el.vs->sc.position < 0) {
	      el.vs->sc.position = 0;
	    }
	  }
	  scrollbar_v_draw(&el.vs->sc);
	}

	return el.vs->sc.position;
}


void landDrawHScroll(scrollbar* sc, HScroll vs) {
	int y = vs.y;
	if (y < 0) {
    	sc->ypos  = proc_info.winy_size + y;
	} else {
		sc->ypos  = y;
	}
    sc->xpos  = vs.offsetX;

    if (vs.w == 0) {
    	sc->xsize = proc_info.winx_size - 3 - sc->xpos;
    } else {
    	sc->xsize = vs.w;
    }

    if (vs.hasNormal == true) {
    	sc->xsize -= LLD_SCROLL_WIDTH;
    }

    scrollbar_h_draw(sc);
}

UINT landDefaultHScroll(char* id, int wheel, UINT wheels) {
	Element el = e(id);

	if (NULL == el.vs) {
		return 0;
	}

	//scrollbar_v_mouse(&el.vs->sc);

	unsigned int scroll_strong = 10;
	if (wheels & 0xFFFF) {
	  if ((short)wheels > 0) {
	    el.hs->sc.position += scroll_strong;
	    if (el.hs->sc.position > el.hs->sc.max_area - el.hs->sc.cur_area) {
	      el.hs->sc.position = el.hs->sc.max_area - el.hs->sc.cur_area;
	    }
	  } else if ((short)wheels < 0 && el.hs->sc.position > 0) {
	    el.hs->sc.position -= scroll_strong;
	    if ((int)el.hs->sc.position < 0) {
	      el.hs->sc.position = 0;
	    }
	  }
	  scrollbar_h_draw(&el.hs->sc);
	}

	return el.hs->sc.position;
}

BOOL landCaptureTab(uint32_t code, UINT command) {
	char* type;
	char* zeroType = "";
	char* zeroId = "";
	char* zeroIdBuf = "";
	char zeroIdIsInit = 0;
	char typeIsValidForInitZero = 0;

	char*  id;
	char* idCurr;
	char foundNext = 0, foundCurr = 0;
	char direct = 1;
	if (command == 129 || command == 132 || command == 131/*crtl*/ || command == 193/*caps*/) {
		direct = -1;
	}

	char* v = "Tab pressed";
	char sCode[255];
	v = addchar(v, ' ');

	if (985344/*1838336*/ == code && focusedTabIndex > -1) {

		for (long i = 0; i <= LLDO_ITERATOR; i++) {
			typeIsValidForInitZero = 0;

			type = LLDO_TYPES[i];
			if (0 == strcmp("itext", type)) {
				typeIsValidForInitZero = 1;
				zeroIdBuf = LLDO_INP_TEXT[i].id;
				if (LLDO_INP_TEXT[i].tabIndex - 1*direct == (int)focusedTabIndex) {
					id = LLDO_INP_TEXT[i].id;
					foundNext = 1;
				}
				if (LLDO_INP_TEXT[i].tabIndex == (int)focusedTabIndex) {
					idCurr = LLDO_INP_TEXT[i].id;
					foundCurr = 1;
				}
			}
			if (0 == strcmp("icheckbox", type)) {
				typeIsValidForInitZero = 1;
				zeroIdBuf = LLDO_INP_TEXT[i].id;
				if (LLDO_CHB[i].tabIndex - 1*direct == (int)focusedTabIndex) {
					id = LLDO_CHB[i].id;
					foundNext = 1;
				}
				if (LLDO_CHB[i].tabIndex == (int)focusedTabIndex) {
					idCurr = LLDO_CHB[i].id;
					foundCurr = 1;
				}
			}
			if (0 == strcmp("img", type)) {
				if (TabIndexDefaultMode > 0) {
					typeIsValidForInitZero = 1;
					zeroIdBuf = LLDO_INP_TEXT[i].id;
				}
				typeIsValidForInitZero = 1;
				if (LLDO_IMG[i].tabIndex - 1*direct == (int)focusedTabIndex) {
					id = LLDO_IMG[i].id;
					foundNext = 1;
				}
				if (LLDO_IMG[i].tabIndex == (int)focusedTabIndex) {
					idCurr = LLDO_IMG[i].id;
					foundCurr = 1;
				}
			}
			if (0 == strcmp("text", type)) {
				if (TabIndexDefaultMode > 2) {
					typeIsValidForInitZero = 1;
					zeroIdBuf = LLDO_INP_TEXT[i].id;
				}
				if (LLDO_TEXT[i].tabIndex - 1*direct == (int)focusedTabIndex) {
					id = LLDO_TEXT[i].id;
					foundNext = 1;
				}
				if (LLDO_TEXT[i].tabIndex == (int)focusedTabIndex) {
					idCurr = LLDO_TEXT[i].id;
					foundCurr = 1;
				}
			}
			if (0 == strcmp("btn", type)) {
				typeIsValidForInitZero = 1;
				zeroIdBuf = LLDO_INP_TEXT[i].id;
				if (LLDO_BTN[i].tabIndex - 1*direct == (int)focusedTabIndex) {
					id = LLDO_BTN[i].id;
					foundNext = 1;
				}
				if (LLDO_BTN[i].tabIndex == (int)focusedTabIndex) {
					idCurr = LLDO_BTN[i].id;
					foundCurr = 1;
				}
			}
			if (0 == strcmp("vscroll", type)) {
				if (LLDO_VSCROLL[i].tabIndex - 1*direct == (int)focusedTabIndex) {
					id = LLDO_VSCROLL[i].id;
					foundNext = 1;
				}
				if (LLDO_VSCROLL[i].tabIndex == (int)focusedTabIndex) {
					idCurr = LLDO_VSCROLL[i].id;
					foundCurr = 1;
				}
			}
			if (0 == strcmp("hscroll", type)) {
				if (LLDO_HSCROLL[i].tabIndex - 1*direct == (int)focusedTabIndex) {
					id = LLDO_HSCROLL[i].id;
					foundNext = 1;
				}
				if (LLDO_HSCROLL[i].tabIndex == (int)focusedTabIndex) {
					idCurr = LLDO_HSCROLL[i].id;
					foundCurr = 1;
				}
			}

			if (0 == zeroIdIsInit && typeIsValidForInitZero == 1) {
				zeroType = addstr(zeroType, type);
				zeroId = addstr(zeroId, zeroIdBuf);
				zeroIdIsInit = 1;
			}

			if (1 == foundNext && 1 == foundCurr) {
				break;
			}
		}// for


		if (0 == foundNext && 1 == foundCurr) {
			type = zeroType;
			id = zeroId;
			foundNext = 1;
		}

		sprintf(sCode, ", cmd = %d", command);
		v = addstr(v, sCode);
		sprintf(sCode, ", c = %d", code);
		v = addstr(v, sCode);
		if (1 == foundCurr) {
			v = addstr(v, idCurr);
			v = addstr(v, " new ");
			setFocus(idCurr, false);
		}

		if (1 == foundNext ) {
			v = addstr(v, id);
			setFocus(id, true);
			//_ksys_set_window_title(v);
		}


		if (1 == foundNext && 1 == foundCurr) {
			return true;
		}

	}// if Tab

	return false;
}