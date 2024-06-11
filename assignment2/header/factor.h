#ifndef __FACTOR_H__
#define __FACTOR_H__

#include <stdio.h>
#include <string.h>

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"
#include "../header/parser.h"
#include "../header/expression.h"

void factor(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);
void more_factor(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);

#endif