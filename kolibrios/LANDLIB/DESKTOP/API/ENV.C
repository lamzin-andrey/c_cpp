#include "env.h"

//void fake_on_redraw(void) { }


char isInit = 0;
open_dialog* lld_dlg_open;


char* Env_openFileDialog(char* caption, char* dir, char* filter) {

	if (0 == isInit) {
		lld_dlg_open = kolibri_new_open_dialog(OPEN, 10, 10, 420, 320); // create opendialog struct
	} else {
		lld_dlg_open->mode = 0;
	}

    if (strlen(dir) > 0) {
 		lld_dlg_open->dir_default_path = dir;
 	}

 	lld_dlg_open->filter_area = Env_getODFilter(filter);

 	if (0 == isInit) {
 		isInit = 1;
 		OpenDialog_init(lld_dlg_open);                                               // Initializing an open dialog box.
	}

    OpenDialog_start(lld_dlg_open);                                              // Show open dialog box


    if (lld_dlg_open->status == SUCCESS) {
    	char* r = lld_dlg_open->openfile_path;
        return r;
    }

    return "";
}

char* Env_openDirectoryDialog(char* caption, char *dir) {

    if (0 == isInit) {
		lld_dlg_open = kolibri_new_open_dialog(SELECT, 10, 10, 420, 320); // create opendialog struct
	} else {
		lld_dlg_open->mode = 2;
	}

	//lld_dlg_open->filter_area = Env_getODFilter("*.TXT");

    if (strlen(dir) > 0) {
 		lld_dlg_open->dir_default_path = dir;
 		if (1 == isInit) {
 			lld_dlg_open->opendir_path = dir;
 		}
 	}
 	if (strlen(caption) > 0) {
 		// lld_dlg_open->com_area_name = caption;
 	}


 	if (0 == isInit) {
 		OpenDialog_init(lld_dlg_open);                   // Initializing an open dialog box.
 		lld_dlg_open->filter_area = Env_getODFilter("*.TXT");
 		isInit = 1;
 	}

    OpenDialog_start(lld_dlg_open);                  // Show open dialog box


    if (lld_dlg_open->status == SUCCESS) {
    	char* r = lld_dlg_open->openfile_path;
    	//free(dlg_open);
        return r;
    }

    //free(dlg_open);
    return "";
}

char* Env_saveFileDialog(char* caption, char* dir, char* filter) {

	if (0 == isInit) {
		lld_dlg_open = kolibri_new_open_dialog(SAVE, 10, 10, 420, 320); // create opendialog struct
	} else {
		lld_dlg_open->mode = 1;
	}

    if (strlen(dir) > 0) {
 		lld_dlg_open->dir_default_path = dir;
 		if (1 == isInit) {
 			//lld_dlg_open->opendir_path = dir;
 		}
 	}

 	lld_dlg_open->filter_area = Env_getODFilter(filter);

 	if (0 == isInit) {
 		isInit = 1;
 		OpenDialog_init(lld_dlg_open);                                               // Initializing an open dialog box.
	}

    OpenDialog_start(lld_dlg_open);                                              // Show open dialog box


    if (lld_dlg_open->status == SUCCESS) {
    	lld_dlg_open->openfile_path = addstr(lld_dlg_open->opendir_path, "/");
    	lld_dlg_open->openfile_path = addstr(lld_dlg_open->openfile_path, lld_dlg_open->filename_area);
    	char* r = lld_dlg_open->openfile_path;
        return r;
    } else {
    	return "Save error";
    }

    return "";
}

int Env_exec1(char* exe, char* args) {
	return _ksys_exec(exe, args);
}

void Env_kill(unsigned long id) {
  _ksys_kill_by_pid(id);
}

// private
od_filter* Env_getODFilter(char* filter) {
// It first work example
 	/*char cod_filter[] = "LLLLTXT\0C\0SH";
 	cod_filter[0] = 12;
 	cod_filter[1] = 0;
 	cod_filter[2] = 0;
 	cod_filter[3] = 0;
 	//cod_filter[4] = 1;
 	dlg_open->filter_area = (od_filter*)cod_filter;*/

	char* tfilter = trim(filter);
	free(filter);
	filter = tfilter;
	char* sSize = "LLLL";
	filter = str_replace("*.", "", filter);
	char L = (char)(strlen(filter) + 4);
	filter = addstr(sSize, filter);
	unsigned int i, z;
	for (i = 0; i < L; i++) {
		if (filter[i] == ' ') {
			filter[i] = '\0';
		}
	}
	filter[0] = L;
	filter[1] = 0;
	filter[2] = 0;
	filter[3] = 0;

 	//dlg_open->filter_area = (od_filter*)filter;
	return (od_filter*)filter;
}

// =================
int sEnv_openFileDialog(char* caption, char* dir, char* filter, char* result, unsigned int size) {

	if (0 == isInit) {
		lld_dlg_open = kolibri_new_open_dialog(OPEN, 10, 10, 420, 320); // create opendialog struct
	} else {
		lld_dlg_open->mode = 0;
	}

    if (strlen(dir) > 0) {
 		lld_dlg_open->dir_default_path = dir;
 	}

 	lld_dlg_open->filter_area = Env_getODFilter(filter);

 	if (0 == isInit) {
 		isInit = 1;
 		OpenDialog_init(lld_dlg_open);                                               // Initializing an open dialog box.
	}

    OpenDialog_start(lld_dlg_open);                                              // Show open dialog box


    if (lld_dlg_open->status == SUCCESS) {
    	if (strlen(lld_dlg_open->openfile_path) < size) {
    		strcpy(result, lld_dlg_open->openfile_path);
        	return 1;
    	}
    }

    return 0;
}

int sEnv_saveFileDialog(char* caption, char* dir, char* filter, char* result, unsigned int size) {

	if (0 == isInit) {
		lld_dlg_open = kolibri_new_open_dialog(SAVE, 10, 10, 420, 320); // create opendialog struct
	} else {
		lld_dlg_open->mode = 1;
	}

    if (strlen(dir) > 0) {
 		lld_dlg_open->dir_default_path = dir;
 		if (1 == isInit) {
 			//lld_dlg_open->opendir_path = dir;
 		}
 	}

 	lld_dlg_open->filter_area = Env_getODFilter(filter);

 	if (0 == isInit) {
 		isInit = 1;
 		OpenDialog_init(lld_dlg_open);                                 // Initializing an open dialog box.
	}

    OpenDialog_start(lld_dlg_open);                                    // Show open dialog box


    if (lld_dlg_open->status == SUCCESS) {
    	char* r = addstr(lld_dlg_open->opendir_path, "/");
    	r = addstr(r, lld_dlg_open->filename_area);
    	if (strlen(lld_dlg_open->openfile_path) < size) {
    		strcpy(result, r);
    		free(r);
    		return 1;
    	}

    }

    return 0;
}

int sEnv_openDirectoryDialog(char* caption, char *dir, char* result, unsigned int size) {

    if (0 == isInit) {
		lld_dlg_open = kolibri_new_open_dialog(SELECT, 10, 10, 420, 320); // create opendialog struct
	} else {
		lld_dlg_open->mode = 2;
		//lld_dlg_open->filter_area = Env_getODFilter("*.TXT");
	}


    if (strlen(dir) > 0) {
 		lld_dlg_open->dir_default_path = dir;
 		if (1 == isInit) {
 			lld_dlg_open->opendir_path = dir;
 		}
 	}
 	if (strlen(caption) > 0) {
 		// lld_dlg_open->com_area_name = caption;
 	}


 	if (0 == isInit) {
 	    lld_dlg_open->filter_area = Env_getODFilter("*.TXT");
 		OpenDialog_init(lld_dlg_open);                   // Initializing an open dialog box.
 		isInit = 1;
 	}

    OpenDialog_start(lld_dlg_open);                  // Show open dialog box


    if (lld_dlg_open->status == SUCCESS) {
    	if (strlen(lld_dlg_open->openfile_path) < size) {
    		strcpy(result, lld_dlg_open->openfile_path);
    		return 1;
    	}
    }

    return 0;
}