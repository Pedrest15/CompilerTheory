#ifndef __STATES_H__
#define __STATES_H__

#include <stdio.h>

#include "../header/tables.h"
#include "../header/files_actions.h"

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
    DONE_KEYWORD,
    DONE_KEYSYMBOL,
    DONE_IDENTIFIER,
    DONE_NUMBER,
    DONE_COMMENT,
    ERROR_INVALID_SYMBOL,
    ERROR_INVALID_IDENTIFIER,
    ERROR_NUMBER_LETTER,
    ERROR_INVALID_NUMBER,
    ERROR_DOUBLE_DOTS
} State;

int final_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer);
int error_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer);

#endif