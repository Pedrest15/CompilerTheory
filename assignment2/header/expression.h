#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include <stdio.h>
#include <string.h>

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"
#include "../header/parser.h"
#include "../header/factor.h"

void term(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);
void expression(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);

#endif