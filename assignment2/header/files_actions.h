#ifndef __FILES_ACTIONS_H__
#define __FILES_ACTIONS_H__

#include <stdio.h>

void backtrack(FILE* file);
void write_token(FILE* file, char* token, char* token_class);
void write_error(FILE* file, char* msg, int* line);

#endif