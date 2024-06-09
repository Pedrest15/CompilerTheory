#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>

// Estrutura de um Token e sua Classe
typedef struct TokenClass {
    char value[20];
    char _class[30];
} TokenClass;

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"

void parser(FILE* file, FILE* foutput);

#endif