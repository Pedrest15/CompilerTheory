#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include <stdio.h>

#include "tables.h"
#include "states.h"
#include "check_symbol.h"

void execute_lexical_analyzer(FILE* file);

#endif