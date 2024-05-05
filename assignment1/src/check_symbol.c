#include "../header/check_symbol.h"

int isLetter(char symbol){
    if ((symbol >= 'A' && symbol <= 'Z') ||
        (symbol >= 'a' && symbol <= 'z')){
        return TRUE;
    }
    return FALSE;
}

int isDigit(char symbol){
    if (symbol >= '0' && symbol <= '9'){
        return TRUE;
    }
    return FALSE;
}

int isSpace(char symbol){
    if (symbol == ' '){
        return TRUE;
    }
    return FALSE;
} 

int isNewLine(char symbol){
    if (symbol == '\n'){
        return TRUE;
    }
    return FALSE;
}

int isComment(State current_state, char symbol){
    if (current_state == START && symbol == '{'){
        return TRUE;
    } else if ((current_state != START && symbol == '}')){
        return TRUE;
    }
    return FALSE;
}

int isKeySymbol(char symbol){
    if (symbol == '+' ||
        symbol == '-' ||
        symbol == '/' ||
        symbol == '*' ||
        symbol == ':' ||
        symbol == '=' ||
        symbol == '>' ||
        symbol == '<' ||
        symbol == ',' ||
        symbol == ';' ||
        symbol == '.'){
        return TRUE;
    }
    return FALSE;
}

int isSeparator(HashTable keysymbols, State current_state, char symbol){
    if(isSpace(symbol) || isNewLine(symbol) || isKeySymbol(symbol) || 
                        isComment(current_state, symbol) || symbol == EOF){
        return TRUE;
    }
    return FALSE;
}

