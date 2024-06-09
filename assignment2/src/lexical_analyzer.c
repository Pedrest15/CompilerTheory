#include "../header/lexical_analyzer.h"

/**
 * @brief Funcao que implementa as regras de transicao do automato finito deterministico (AFD).
 * 
 * Esta funcao recebe como entrada o arquivo de entrada, o estado atual do AFD, o simbolo atual e o buffer.
 * Baseado no estado atual e no simbolo atual, determina o proximo estado do AFD.
 * 
 * @param file Arquivo de entrada contendo o programa em processo de compilacao.
 * @param current_state Estado atual do AFD.
 * @param symbol Simbolo atual lido na fita de entrada.
 * @param buffer Cadeia lida ate o momento, entre o estado inicial ate chegar um estado final.
 * @return State Proximo estado do AFD.
 */
State transition_rules(FILE* file, State current_state, char symbol, char* buffer){
    switch(current_state){
        case START:
            // Verifica se o simbolo e uma letra para identificar palavras-chave
            if (isLetter(symbol)){
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            // Verifica se o simbolo e um sublinhado para identificar identificadores
            } else if (isUnderScore(symbol)){
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

            // Verifica se o simbolo e um simbolo chave simples
            } else if(isSimpleKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            // Verifica se o simbolo e ':', potencial inicio de ':='
            } else if(isDoubleDotsKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return DOUBLE_DOTS_KEYSYMBOL;

            // Verifica se o simbolo e '<', potencial inicio de '<=', '<>' ou '<'
            } else if(isLowerKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return LOWER_KEYSYMBOL;

            // Verifica se o simbolo e '>', potencial inicio de '>=' ou '>'
            } else if(isBiggerKeySymbol(symbol)){
                buffer[strlen(buffer)] = symbol;
                return BIGGER_KEYSYMBOL;

            // Verifica se o simbolo e um digito
            } else if(isDigit(symbol)){
                buffer[strlen(buffer)] = symbol;
                return NUMBER;

            // Verifica se o simbolo e '{', inicio de um comentario            
            } else if(BeginComment(symbol)){
                buffer[strlen(buffer)] = symbol;
                return COMMENT;

            // caso a fita do automato inicie com espaco ou quebra de linha
            } else if(isSpace(symbol) || isNewLine(symbol)){
                return START;

            // caso de EOF, ignorado pelo automato
            } else if(symbol == EOF){
                break;

            // fechar comentario sem ter aberto um
            } else if (CloseComment(symbol)){
                buffer[strlen(buffer)] = symbol;
                return ERROR_CLOSE_COMMENT;
        
            // caracteres invalidos
            } else {
                buffer[strlen(buffer)] = symbol;
                return INVALID_SYMBOL; // Volta ao estado inicial após o erro
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
            
            //caracter invalido no nome
            } else {
                buffer[strlen(buffer)] = symbol;
                return INVALID_SYMBOL;
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
                return INVALID_SYMBOL;
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

            //caracter invalido no numero
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_NUMBER;
            }
            break;

        case COMMENT:
            if (CloseComment(symbol)){
                return DONE_COMMENT;
            } else if (isNewLine(symbol)){
                return ERROR_COMMENT;
            } else {
                return COMMENT;
            }
            break;

        case INVALID_SYMBOL:
            if (isSeparator(symbol)){
                return ERROR_INVALID_SYMBOL;
            } else {
                buffer[strlen(buffer)] = symbol;
                return INVALID_SYMBOL;
            }

        default:
            break;
    }
    return START;
}

/**
 * @brief Analisa o arquivo de entrada caractere por caractere, aplicando as regras do automato finito deterministico (AFD) 
 * para identificar tokens e suas classes.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @return int Retorna o ultimo caractere lido do arquivo de entrada.
 */
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

/**
 * @brief Funcao de alto nivel que executa o analisador lexico ate o final do arquivo.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 */
void execute_lexical_analyzer(FILE* file, FILE* foutput){
    HashTable keywords = make_KeyWords();
    HashTable keysymbols = make_KeySymbols();

    while (lexical_analyzer(file,foutput,keywords,keysymbols) != EOF);

    destroy_table(keywords);
    destroy_table(keysymbols);
}
