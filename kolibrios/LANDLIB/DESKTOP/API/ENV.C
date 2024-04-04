#include "env.h"

char* EnvopenFileDialog(char* caption, char *dir, char* filter) {
	open_dialog* dlg_open = kolibri_new_open_dialog(OPEN, 10, 10, 420, 320); // create opendialog struct


    if (strlen(dir) > 0) {
 		dlg_open->dir_default_path = dir;
 	}
 	if (strlen(caption) > 0) {
 		// dlg_open->com_area_name = caption;
 	}
 	OpenDialog_init(dlg_open);                                               // Initializing an open dialog box.
    OpenDialog_start(dlg_open);                                              // Show open dialog box


    if (dlg_open->status == SUCCESS) {
    	char* r = dlg_open->openfile_path;
    	free(dlg_open);
        return r;
    }

    free(dlg_open);
    return "";
}

char* EnvopenDirectoryDialog(char* caption, char *dir) {
	open_dialog* dlg_open = kolibri_new_open_dialog(SELECT, 10, 10, 420, 320); // create opendialog struct

    if (strlen(dir) > 0) {
 		dlg_open->dir_default_path = dir;
 	}
 	if (strlen(caption) > 0) {
 		// dlg_open->com_area_name = caption;
 	}
 	OpenDialog_init(dlg_open);                                               // Initializing an open dialog box.
    OpenDialog_start(dlg_open);                                              // Show open dialog box


    if (dlg_open->status == SUCCESS) {
    	char* r = dlg_open->openfile_path;
    	free(dlg_open);
        return r;
    }

    free(dlg_open);
    return "";
}

int Envexec1(char* exe, char* args) {
	return _ksys_exec(exe, args);
}

void Envkill(unsigned long id) {
  _ksys_kill_by_pid(id);
}