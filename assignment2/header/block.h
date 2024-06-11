#ifndef __PROCEDURE_H__
#define __PROCEDURE_H__

#include <stdio.h>
#include <string.h>

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"
#include "../header/parser.h"

void block(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);
void declaration(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);
void procedure(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);

#endif