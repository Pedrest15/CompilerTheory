#include "../header/lexical_analyzer.h"

int final_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer){
    switch (current_state){
        case DONE_KEYWORD:
            if (symbol != EOF){
                backtrack(file);
            }
            buffer[strlen(buffer)] = '\0';
            if (search_token(&keywords,buffer)){
                write_token(foutput,buffer,get_token_class(&keywords,buffer));
                printf("%s, %s\n", buffer,get_token_class(&keywords,buffer));
            } else {
                write_token(foutput,buffer,"ident");
                printf("%s, id\n", buffer);
            }
            
            return TRUE;

        case DONE_KEYSYMBOL:
            if (symbol != EOF){
                backtrack(file);
            }
            buffer[strlen(buffer)] = '\0';
            if (search_token(&keysymbols,buffer)){
                write_token(foutput,buffer,get_token_class(&keysymbols,buffer));
                printf("%s, %s\n", buffer,get_token_class(&keysymbols,buffer));
            } else {
                printf("lascou\n");
            }
            
            return TRUE;

        case DONE_IDENTIFIER:
            if (symbol != EOF){
                backtrack(file);
            }
            buffer[strlen(buffer)] = '\0';
            write_token(foutput,buffer,"ident");
            printf("%s, id\n", buffer);
            return TRUE;

        case DONE_NUMBER:
            if (symbol != EOF){
                backtrack(file);
            }
            buffer[strlen(buffer)] = '\0';
            write_token(foutput,buffer,"numero");
            printf("%s, num\n", buffer);

        case DONE_COMMENT:
            return TRUE;
        
        default:
            return FALSE;
    }
}

State transition_rules(FILE* file, HashTable keywords, HashTable keysymbols,State current_state, char symbol, char* buffer){
    switch(current_state){
        case START:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            } else if(isKeySymbol(keysymbols,symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYSYMBOL;

            } else if(isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return NUMBER;
            
            } else if(isComment(current_state,symbol)){
                buffer[strlen(buffer)] = symbol;
                return COMMENT;
            }
            break;

        case KEYWORD:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            } else if (isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;
            
            } else if (isSeparator(keysymbols,current_state,symbol)){
                return DONE_KEYWORD;
            }
            break;

        case KEYSYMBOL:
            if (isKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYSYMBOL;
            } else {
                return DONE_KEYSYMBOL;
            }

        case IDENTIFIER:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

            } else if (isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;
            
            } else if (isSeparator(keysymbols,current_state,symbol)){
                return DONE_IDENTIFIER;
            }
            break;

        case NUMBER:
            if (isLetter(symbol)){
                //erro

            } else if (isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return NUMBER;
            
            } else if (isSeparator(keysymbols,current_state,symbol)){
                return DONE_NUMBER;
            }

        case COMMENT:
            if (isComment(current_state,symbol)){
                return DONE_COMMENT;
            } else {
                return COMMENT;
            }
    }
}

int lexical_analyzer(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols){
    State current_state = START;
    char symbol;
    char buffer[100] = "";
    
    while (1) {
        symbol = fgetc(file);
        
        current_state = transition_rules(file,keywords,keysymbols,current_state,symbol,buffer);
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
