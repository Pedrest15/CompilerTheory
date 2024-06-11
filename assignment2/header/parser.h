#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

// Estrutura de um Token e sua Classe
typedef struct TokenClass {
    char value[20];
    char _class[30];
} TokenClass;

#include "../header/tables.h"
#include "../header/lexical_analyzer.h"
#include "../header/files_actions.h"
#include "../header/constant.h"
#include "../header/command.h"
#include "../header/variable.h"
#include "../header/block.h"

void parser(FILE* file, FILE* foutput);

#endif