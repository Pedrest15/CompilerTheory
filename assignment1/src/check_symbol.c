#include "check_symbol.h"

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

int isOperator(HashTable operators,char symbol){
    char word[2];
    word[0] = symbol;
    word[1] = '\0';
    if (search_word(&operators,word)){
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
