#include "../header/check_symbol.h"

/**
 * @brief Verifica se um caracter eh uma letra, seja maiuscula ou minuscula
 * 
 * @param symbol caracter a ser analisado
 * @return int retorna se a função foi concluida com sucesso ou nao
 */
int isLetter(char symbol){
    if ((symbol >= 'A' && symbol <= 'Z') ||
        (symbol >= 'a' && symbol <= 'z')){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se um caracter eh um digito
 * 
 * @param symbol caracter a ser analisado
 * @return int retorna se a função foi concluida com sucesso ou nao
 */
int isDigit(char symbol){
    if (symbol >= '0' && symbol <= '9'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se um caracter eh um espaco em branco
 * 
 * @param symbol caracter a ser analisado
 * @return int retorna se a função foi concluida com sucesso ou nao
 */
int isSpace(char symbol){
    if (symbol == ' ' || symbol == '\t'){
        return TRUE;
    }
    return FALSE;
} 

/**
 * @brief Verifica se um caracter eh uma quebra de linha
 * 
 * @param symbol caracter a ser analisado
 * @return int retorna se a função foi concluida com sucesso ou nao
 */
int isNewLine(char symbol){
    if (symbol == '\n'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se um caracter eh uma chave de abrir comentario
 *
 * @param symbol caracter a ser analisado
 * @return int retorna se a funcao foi concluida com sucesso ou nao
 */
int BeginComment(char symbol){
    if (symbol == '{'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se um caracter eh uma chave de fechar comentario
 *
 * @param symbol caracter a ser analisado
 * @return int retorna se a funcao foi concluida com sucesso ou nao
 */
int CloseComment(char symbol){
    if (symbol == '}'){
        return TRUE;
    }
    return FALSE;
}


/**
 * @brief Verifica se um caracter eh um simbolo reservado
 * 
 * @param symbol caracter a ser analisado
 * @return int retorna se a funcao foi concluida com sucesso ou nao
 */
int isSimpleKeySymbol(char symbol){
    if (symbol == '=' ||
        symbol == '+' ||
        symbol == '-' ||
        symbol == '/' ||
        symbol == '*' ||
        symbol == ',' ||
        symbol == ';' ||
        symbol == '.' ||
        symbol == '(' ||
        symbol == ')'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se o caractere e \':\'.
 * 
 * @param symbol O caractere a ser verificado.
 * @return int Retorna TRUE se o caractere for \':\', senao retorna FALSE.
 */

int isDoubleDotsKeySymbol(char symbol){
    if (symbol == ':'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se o caractere e \'=\'.
 * 
 * @param symbol O caractere a ser verificado.
 * @return int Retorna TRUE se o caractere for \'=\', senao retorna FALSE.
 */
int isEqualKeySymbol(char symbol){
    if (symbol == '='){
        return TRUE;
    }
    return FALSE;
}


/**
 * @brief Verifica se o caractere e \'>\'.
 * 
 * @param symbol O caractere a ser verificado.
 * @return int Retorna TRUE se o caractere for \'>\', senao retorna FALSE.
 */

int isBiggerKeySymbol(char symbol){
    if (symbol == '>'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se o caractere e \'<\'.
 * 
 * @param symbol O caractere a ser verificado.
 * @return int Retorna TRUE se o caractere for \'<\', senao retorna FALSE.
 */
int isLowerKeySymbol(char symbol){
    if (symbol == '<'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se o caractere e \'_\'.
 * 
 * @param symbol O caractere a ser verificado.
 * @return int Retorna TRUE se o caractere for \'_\', senao retorna FALSE.
 */
int isUnderScore(char symbol){
    if (symbol == '_'){
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Verifica se um caracter eh algum que separa um identificador ou
 *palavra/simbolo reservado 
 *
 * @param symbol caracter a ser analisado
 * @return int retorna se a função foi concluida com sucesso ou nao
 */
int isSeparator(char symbol){
    if( isSpace(symbol) ||
        isNewLine(symbol) ||
        isSimpleKeySymbol(symbol) ||
        isDoubleDotsKeySymbol(symbol) ||
        isLowerKeySymbol(symbol) ||
        isBiggerKeySymbol(symbol) ||
        BeginComment(symbol) ||
        isEqualKeySymbol(symbol) ||
        symbol == EOF){
        return TRUE;
    }
    return FALSE;
}

