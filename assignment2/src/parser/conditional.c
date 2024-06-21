#include "../../header/conditional.h"

/**
 * @brief Funcao que analisa e processa operadores relacionais.
 * 
 * Esta funcao verifica se o token atual e um operador relacional (atribuição, comparação, diferente, menor, maior, menor ou igual, maior ou igual).
 * Se for, continua analisando os tokens subsequentes. Caso não encontre um operador relacional, escreve uma mensagem de erro apropriada no arquivo de saída.
 * 
 * @param file Arquivo de entrada contendo o código fonte a ser analisado.
 * @param foutput Arquivo de saída onde os tokens e suas classes serão registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os símbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void relational(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é um símbolo de atribuição
    if (strcmp(token->_class, "simbolo_atribuicao") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um símbolo de comparação
    if (strcmp(token->_class, "simbolo_comparacao") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um símbolo de diferente
    if (strcmp(token->_class, "simbolo_diferente") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um símbolo de menor
    if (strcmp(token->_class, "simbolo_menor") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um símbolo de maior
    if (strcmp(token->_class, "simbolo_maior") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um símbolo de menor ou igual
    if (strcmp(token->_class, "simbolo_menor_igual") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um símbolo de maior ou igual
    if (strcmp(token->_class, "simbolo_maior_igual") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Se nenhum operador relacional for encontrado, registra um erro
    write_error(foutput, "Erro sintatico: simbolo de relacional faltando na linha", line);
}

/**
 * @brief Funcao que analisa e processa condições (expressões condicionais).
 * 
 * Esta funcao verifica se o token atual representa uma condição (ODD ou uma expressão seguida de um operador relacional).
 * Continua analisando os tokens subsequentes para validar a sintaxe da condição.
 * 
 * @param file Arquivo de entrada contendo o código fonte a ser analisado.
 * @param foutput Arquivo de saída onde os tokens e suas classes serão registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os símbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void conditional(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é a palavra-chave "ODD"
    if (strcmp(token->_class, "ODD") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);

        // Analisa a expressão após "ODD"
        expression(file, foutput, keywords, keysymbols, token, line);
        
        return;
    }

    // Analisa a expressão antes do operador relacional
    expression(file, foutput, keywords, keysymbols, token, line);

    // Analisa o operador relacional
    relational(file, foutput, keywords, keysymbols, token, line);

    // Analisa a expressão após o operador relacional
    expression(file, foutput, keywords, keysymbols, token, line);
}
