#ifndef __STATES_H__
#define __STATES_H__

#include <stdio.h>
#include <string.h>

#include "../header/tables.h"
#include "../header/files_actions.h"
#include "../header/parser.h"

#define TRUE 1
#define FALSE 0

// estrura de dados contendo todos os estados da maquina de moore
typedef enum {
    START,
    KEYWORD,
    DOUBLE_DOTS_KEYSYMBOL,
    LOWER_KEYSYMBOL,
    BIGGER_KEYSYMBOL,
    IDENTIFIER,
    NUMBER,
    COMMENT,
    INVALID_SYMBOL,
    DONE_KEYWORD,
    DONE_KEYSYMBOL,
    DONE_BACK_KEYSYMBOL,
    DONE_IDENTIFIER,
    DONE_NUMBER,
    DONE_COMMENT,
    ERROR_INVALID_SYMBOL,
    ERROR_NUMBER_LETTER,
    ERROR_INVALID_NUMBER,
    ERROR_DOUBLE_DOTS,
    ERROR_COMMENT,
    ERROR_CLOSE_COMMENT
} State;

int final_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer,TokenClass *token);
int error_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer,int* line);

#endif