#ifndef __CONDITIONAL_H__
#define __CONDITIONAL_H__

#include <stdio.h>
#include <string.h>

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"
#include "../header/parser.h"
#include "../header/expression.h"

void conditional(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);

#endif