#include "../header/lexical_analyzer.h"

State transition_rules(FILE* file, State current_state, char symbol, char* buffer){
    switch(current_state){
        case START:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            } else if (isUnderScore(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

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
            
            } else if(BeginComment(symbol)){
                buffer[strlen(buffer)] = symbol;
                return COMMENT;

            // caso a fita do automato inicie com espaco ou quebra de linha
            } else if(isSpace(symbol) || isNewLine(symbol)){
                return START;

            // caso de EOF, ignorado pelo automato
            } else if(symbol == EOF){
                break;

            // caracteres invalidos
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_SYMBOL; // Volta ao estado inicial após o erro
            }
            break;

        case KEYWORD:
            // enquanto forem letras, pode ser uma palavra reservada
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            // se houver digito ou _, entao eh um identificador
            } else if (isDigit(symbol) || isUnderScore(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;
            
            } else if (isSeparator(symbol)){
                return DONE_KEYWORD;
            
            //carcter invalido no nome
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_IDENTIFIER;
            }
            break;

        case DOUBLE_DOTS_KEYSYMBOL:
            // buffer fica com simbolo ':='
            if (isEqualKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;
                
            // faltando '='
            } else {
                return ERROR_DOUBLE_DOTS;
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

            } else if (isDigit(symbol) || isUnderScore(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;
            
            } else if (isSeparator(symbol)){
                return DONE_IDENTIFIER;

            //carcter invalido no nome
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_IDENTIFIER;
            }
            break;

        case NUMBER:
            //numero seguido por letra
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return ERROR_NUMBER_LETTER;

            } else if (isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return NUMBER;
            
            } else if (isSeparator(symbol)){
                return DONE_NUMBER;

            //carcter invalido no numero
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_NUMBER;
            }
            break;

        case COMMENT:
            if (CloseComment(symbol)){
                return DONE_COMMENT;
            } else {
                return COMMENT;
            }
            break;

        default:
            break;
    }
    return START;
}

int lexical_analyzer(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols){
    State current_state = START;
    char symbol;
    char buffer[100] = "";
    
    while (1) {
        symbol = fgetc(file);
        
        current_state = transition_rules(file, current_state,symbol,buffer);
        if(final_states(file,foutput,keywords,keysymbols,current_state,symbol,buffer)){
            break;
        } else if(error_states(file,foutput,keywords,keysymbols,current_state,symbol,buffer)){
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
