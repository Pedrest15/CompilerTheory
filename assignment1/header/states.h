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
    KEYSYMBOL,
    IDENTIFIER,
    NUMBER,
    COMMENT,
    DONE_KEYWORD,
    DONE_KEYSYMBOL,
    DONE_IDENTIFIER,
    DONE_NUMBER,
    DONE_COMMENT
} State;

int final_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer);

#endif