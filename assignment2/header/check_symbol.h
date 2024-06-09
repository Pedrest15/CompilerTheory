#ifndef __CHECK_SYMBOLS_H__
#define __CHECK_SYMBOLS_H__

#include "../header/tables.h"
#include "../header/states.h"
#include "../header/lexical_analyzer.h"

#define TRUE 1
#define FALSE 0

int isLetter(char symbol);
int isDigit(char symbol);
int isSpace(char symbol);
int isNewLine(char symbol);
int isSimpleKeySymbol(char symbol);
int isLowerKeySymbol(char symbol);
int isBiggerKeySymbol(char symbol);
int isEqualKeySymbol(char symbol);
int isDoubleDotsKeySymbol(char symbol);
int isUnderScore(char symbol);
int BeginComment(char symbol);
int CloseComment(char symbol);
int isSeparator(char symbol);

#endif