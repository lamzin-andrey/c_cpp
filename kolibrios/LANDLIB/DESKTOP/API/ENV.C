#include "env.h"

int Envexec1(char* exe, char* args) {
	return _ksys_exec(exe, args);
}

void Envkill(unsigned long id) {
  _ksys_kill_by_pid(id);
}