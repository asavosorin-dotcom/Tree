#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "akinator.h"
#include "colors.h"
#include "work_with_text.h"

int user_end_programm(const char* string);

enum user_command_t {END = 0, CONTINUE = 1};

#endif