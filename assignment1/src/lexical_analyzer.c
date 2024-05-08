#include "../header/lexical_analyzer.h"

State transition_rules(FILE* file,State current_state, char symbol, char* buffer){
    switch(current_state){
        case START:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            } else if(isSimpleKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            } else if(isDoubleDotsKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DOUBLE_DOTS_KEYSYMBOL;

            } else if(isLowerKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return LOWER_KEYSYMBOL;

            } else if(isBiggerKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return BIGGER_KEYSYMBOL;

            } else if(isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return NUMBER;
            
            } else if(isComment(current_state,symbol)){
                buffer[strlen(buffer)] = symbol;
                return COMMENT;

            // caso o automato inicie com espaco ou quebra de linha
            } else if(isSpace(symbol) || isNewLine(symbol)){
                return START;

            // caracteres invalidos
            } else {
                //caracter invalido
                //ERRO
            }
            break;

        case KEYWORD:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            } else if (isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;
            
            } else if (isSeparator(current_state,symbol)){
                return DONE_KEYWORD;
            } else {
                //caracter invalido
                //ERRO
            }
            break;

        case DOUBLE_DOTS_KEYSYMBOL:
            // buffer fica com simbolo ':='
            if (isEqualKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;
                
            } else {
                return DONE_KEYSYMBOL;
            }
            break;

        case LOWER_KEYSYMBOL:
            // buffer fica com simbolo '<='
            if (isEqualKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;
            
            // buffer fica com simbolo '<>'
            } else if (isBiggerKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;    
            
            } else {
                return DONE_KEYSYMBOL;
            }
            break;

        case BIGGER_KEYSYMBOL:
            // buffer fica com simbolo '>='
            if (isEqualKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;
                
            //buffer apenas com '>'
            } else {
                return DONE_KEYSYMBOL;
            }
            break;

        case IDENTIFIER:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

            } else if (isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;
            
            } else if (isSeparator(current_state,symbol)){
                return DONE_IDENTIFIER;

            } else {
                //caracter invalido
                //ERRO
            }
            break;

        case NUMBER:
            if (isLetter(symbol)){
                //erro

            } else if (isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return NUMBER;
            
            } else if (isSeparator(current_state,symbol)){
                return DONE_NUMBER;

            } else {
                //caracter invalido
                //ERRO
            }
            break;

        case COMMENT:
            if (isComment(current_state,symbol)){
                return DONE_COMMENT;
            } else {
                return COMMENT;
            }
            break;
    }
}

int lexical_analyzer(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols){
    State current_state = START;
    char symbol;
    char buffer[100] = "";
    
    while (1) {
        symbol = fgetc(file);
        
        current_state = transition_rules(file,current_state,symbol,buffer);
        if(final_states(file,foutput,keywords,keysymbols,current_state,symbol,buffer)){
            break;
        }
    
        if (symbol == EOF){
            break;
        }
    }
    
    return symbol;
}

void execute_lexical_analyzer(FILE* file, FILE* foutput){
    HashTable keywords = make_KeyWords();
    HashTable keysymbols = make_KeySymbols();
    while (lexical_analyzer(file,foutput,keywords,keysymbols) != EOF);
}
