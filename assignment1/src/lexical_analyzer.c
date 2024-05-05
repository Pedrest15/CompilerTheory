#include "lexical_analyzer.h"

void backtrack(FILE* file){
    fseek(file, -1, SEEK_CUR);
}

State transition_rules(FILE* file, HashTable keywords, HashTable operators,State current_state, char symbol, char* buffer){
    switch(current_state){
        case START:
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;
            } else if(isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;
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
            
            } else if (isSpace(symbol) || isNewLine(symbol) || isOperator(operators,symbol) || 
                        isComment(current_state, symbol) || symbol == EOF){
                return DONE_KEYWORD;
            }
            break;

        case IDENTIFIER:
            break;

        case COMMENT:
            if (isComment(current_state,symbol)){
                return DONE_COMMENT;
            } else {
                return COMMENT;
            }


    }
}

int final_states(FILE* file,HashTable keywords,State current_state,char symbol,char* buffer){
    switch (current_state){
        case DONE_KEYWORD:
            if (symbol == EOF){
                backtrack(file);
            }
            buffer[strlen(buffer)] = '\0';
            if (search_word(&keywords,buffer)){
                printf("%s\n", buffer);
            } else {
                //identificador
                printf("aqui");
            }
            
            return TRUE;

        case DONE_IDENTIFIER:
            return TRUE;

        case DONE_COMMENT:
            return TRUE;
        
        default:
            return FALSE;
    }
}

int lexical_analyzer(FILE* file, HashTable keywords, HashTable operators){
    State current_state = START;
    char symbol;
    char buffer[100] = "";
    
    while (1) {
        symbol = fgetc(file);
        
        current_state = transition_rules(file,keywords,operators,current_state,symbol,buffer);
        if(final_states(file,keywords,current_state,symbol,buffer)){
            break;
        }
    
        if (symbol == EOF){
            break;
        }
    }
    return symbol;
}

void execute_lexical_analyzer(FILE* file){
    HashTable keywords = make_KeyWords();
    HashTable operators = make_operators();
    while (lexical_analyzer(file,keywords,operators) != EOF);
}
