#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <stdio.h>
#include <string.h>

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"
#include "../header/parser.h"
#include "../header/expression.h"
#include "../header/conditional.h"

void command(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line);

#endif