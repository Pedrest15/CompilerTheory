#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include <stdio.h>

#include "../header/tables.h"
#include "../header/states.h"
#include "../header/check_symbol.h"
#include "../header/files_actions.h"

void backtrack(FILE* file);
void execute_lexical_analyzer(FILE* file, FILE* foutput);

#endif