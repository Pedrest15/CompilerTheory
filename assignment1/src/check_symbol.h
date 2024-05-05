#ifndef __CHECK_SYMBOLS_H__
#define __CHECK_SYMBOLS_H__

#include "tables.h"
#include "states.h"
#include "lexical_analyzer.h"

#define TRUE 1
#define FALSE 0

int isLetter(char symbol);
int isDigit(char symbol);
int isSpace(char symbol);
int isNewLine(char symbol);
int isOperator(HashTable operators,char symbol);
int isComment(State current_state,char symbol);
int isSeparator(HashTable keysymbols, State current_state, char symbol);

#endif