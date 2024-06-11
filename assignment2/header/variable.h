#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <stdio.h>
#include <string.h>

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"
#include "../header/parser.h"

void variable(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);

#endif