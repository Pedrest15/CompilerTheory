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
State transition_rules(FILE* file, State current_state, char symbol, char* buffer) {
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
            } else if (isSpace(symbol) || isNewLine(symbol)) {
                return START;

            // Caso de EOF, ignorado pelo automato
            } else if (symbol == EOF) {
                break;

            // Caracteres invalidos
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_SYMBOL; // Volta ao estado inicial apos o erro
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

            // Caracter invalido no nome
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_IDENTIFIER;
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
                return DONE_KEYSYMBOL;
            }
            break;

        case BIGGER_KEYSYMBOL:
            // Buffer fica com simbolo '>='
            if (isEqualKeySymbol(symbol)) {
                buffer[strlen(buffer)] = symbol;
                return DONE_KEYSYMBOL;

            // Buffer apenas com '>'
            } else {
                return DONE_KEYSYMBOL;
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

            // Caracter invalido no nome
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_IDENTIFIER;
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

            // Caracter invalido no numero
            } else {
                buffer[strlen(buffer)] = symbol;
                return ERROR_INVALID_NUMBER;
            }
            break;

        case COMMENT:
            // Fecha comentario
            if (CloseComment(symbol)) {
                return DONE_COMMENT;

            // Continua no comentario
            } else {
                return COMMENT;
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
 * @return int Retorna o ultimo caractere lido do arquivo de entrada.
 */
int lexical_analyzer(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols) {
    State current_state = START;
    char symbol;
    char buffer[100] = "";

    while (1) {
        // Le o proximo caractere do arquivo
        symbol = fgetc(file);
        
        // Determina o proximo estado com base no estado atual e no simbolo lido
        current_state = transition_rules(file, current_state, symbol, buffer);

        // Verifica se o estado atual e um estado final
        if (final_states(file, foutput, keywords, keysymbols, current_state, symbol, buffer)) {
            break;

        // Verifica se o estado atual e um estado de erro
        } else if (error_states(file, foutput, keywords, keysymbols, current_state, symbol, buffer)) {
            break;
        }

        // Verifica se chegou ao fim do arquivo
        if (symbol == EOF) {
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
void execute_lexical_analyzer(FILE* file, FILE* foutput) {
    // Cria as tabelas hash para palavras-chave e simbolos
    HashTable keywords = make_KeyWords();
    HashTable keysymbols = make_KeySymbols();

    // Executa o analisador lexico ate o final do arquivo
    while (lexical_analyzer(file, foutput, keywords, keysymbols) != EOF);

    // Destroi as tabelas hash
    destroy_table(keywords);
    destroy_table(keysymbols);
}
