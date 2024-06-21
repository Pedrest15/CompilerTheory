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
 * @param line Linha atual do arquivo de entrada.
 * @return State Proximo estado do AFD.
 */
State transition_rules(FILE* file, State current_state, char symbol, char* buffer, int* line) {
    switch (current_state) {
        case START:
            // Verifica se o simbolo e uma letra para identificar palavras-chave
            if (isLetter(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            // Verifica se o simbolo e um sublinhado para identificar identificadores
            } else if (isUnderScore(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

            // Verifica se o simbolo e um simbolo chave simples
            } else if (isSimpleKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            // Verifica se o simbolo e ':', potencial inicio de ':='
            } else if (isDoubleDotsKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return DOUBLE_DOTS_KEYSYMBOL;

            // Verifica se o simbolo e '<', potencial inicio de '<=', '<>' ou '<'
            } else if (isLowerKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return LOWER_KEYSYMBOL;

            // Verifica se o simbolo e '>', potencial inicio de '>=' ou '>'
            } else if (isBiggerKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return BIGGER_KEYSYMBOL;

            // Verifica se o simbolo e um digito
            } else if (isDigit(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return NUMBER;

            // Verifica se o simbolo e '{', inicio de um comentario            
            } else if (BeginComment(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return COMMENT;

            // Caso a fita do automato inicie com espaco ou quebra de linha
            } else if (isSpace(symbol)) {
                return START;

            // Verifica se o simbolo e uma quebra de linha
            } else if (isNewLine(symbol)) {
                (*line)++;
                return START;

            // Caso de EOF, ignorado pelo automato
            } else if (symbol == EOF) {
                return START;

            // Fechar comentario sem ter aberto um
            } else if (CloseComment(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return ERROR_CLOSE_COMMENT;

            // Caracteres invalidos
            } else {
                buffer[strlen(buffer)] = symbol;
                return INVALID_SYMBOL; // Volta ao estado inicial apos o erro
            }
            break;

        case KEYWORD:
            // Enquanto forem letras, pode ser uma palavra reservada
            if (isLetter(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return KEYWORD;

            // Se houver digito ou _, entao e um identificador
            } else if (isDigit(symbol) || isUnderScore(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

            // Verifica se o simbolo e um separador
            } else if (isSeparator(symbol)) {
                return DONE_KEYWORD;

            // Verifica se o simbolo e uma quebra de linha
            } else if (isNewLine(symbol)) {
                return DONE_KEYWORD;

            // Caracter invalido no nome
            } else {
                buffer[strlen(buffer)] = symbol;
                return INVALID_SYMBOL;
            }
            break;

        case DOUBLE_DOTS_KEYSYMBOL:
            // Buffer fica com simbolo ':='
            if (isEqualKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            // Faltando '='
            } else {
                return ERROR_DOUBLE_DOTS;
            }
            break;

        case LOWER_KEYSYMBOL:
            // Buffer fica com simbolo '<='
            if (isEqualKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            // Buffer fica com simbolo '<>'
            } else if (isBiggerKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            // Simbolo menor
            } else {
                return DONE_BACK_KEYSYMBOL;
            }
            break;

        case BIGGER_KEYSYMBOL:
            // Buffer fica com simbolo '>='
            if (isEqualKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            // Buffer apenas com '>'
            } else {
                return DONE_BACK_KEYSYMBOL;
            }
            break;

        case IDENTIFIER:
            // Continua construindo o identificador se o simbolo for uma letra
            if (isLetter(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

            // Continua construindo o identificador se o simbolo for um digito ou sublinhado
            } else if (isDigit(symbol) || isUnderScore(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return IDENTIFIER;

            // Verifica se o simbolo e um separador
            } else if (isSeparator(symbol)) {
                return DONE_IDENTIFIER;

            // Verifica se o simbolo e uma quebra de linha
            } else if (isNewLine(symbol)) {
                return DONE_IDENTIFIER;

            // Caracter invalido no nome
            } else {
                buffer[strlen(buffer)] = symbol;
                return INVALID_SYMBOL;
            }
            break;

        case NUMBER:
            // Numero seguido por letra, erro
            if (isLetter(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return ERROR_NUMBER_LETTER;

            // Continua construindo o numero se o simbolo for um digito
            } else if (isDigit(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return NUMBER;

            // Verifica se o simbolo e um separador
            } else if (isSeparator(symbol)) {
                return DONE_NUMBER;

            // Verifica se o simbolo e uma quebra de linha
            } else if (isNewLine(symbol)) {
                return DONE_NUMBER;

            // Caracter invalido no numero
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_NUMBER;
            }
            break;

        case COMMENT:
            // Fecha comentario
            if (CloseComment(symbol)) {
                (*line)++;
                return DONE_COMMENT;

            // Verifica se o simbolo e uma quebra de linha dentro do comentario
            } else if (isNewLine(symbol)) {
                (*line)++;
                return ERROR_COMMENT;

            // Continua no comentario
            } else {
                return COMMENT;
            }
            break;

        case INVALID_SYMBOL:
            // Verifica se o simbolo e um separador
            if (isSeparator(symbol)) {
                return ERROR_INVALID_SYMBOL;

            // Verifica se o simbolo e uma quebra de linha
            } else if (isNewLine(symbol)) {
                return ERROR_INVALID_SYMBOL;

            // Continua com simbolo invalido
            } else {
                buffer[strlen(buffer)] = symbol;
                return INVALID_SYMBOL;
            }
            break;

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
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 * @return int Retorna o ultimo caractere lido do arquivo de entrada.
 */
int lexical_analyzer(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass *token, int* line) {
    State current_state = START;
    char symbol;
    char buffer[100] = "";
    strcpy(token->value, "");
    strcpy(token->_class, "");

    while (1) {
        symbol = fgetc(file);
        
        current_state = transition_rules(file, current_state, symbol, buffer, line);

        // Processa estados finais
        final_states(file, foutput, keywords, keysymbols, current_state, symbol, buffer, token);       
        if (strcmp(token->_class, "") != 0) {
            break;
        }

        // Processa estados de erro
        error_states(file, foutput, keywords, keysymbols, current_state, symbol, buffer, line);
    
        if (symbol == EOF) {
            break;
        }
    }
    
    return symbol;
}
