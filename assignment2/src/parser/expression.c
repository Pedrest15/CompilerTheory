#include "../../header/expression.h"

/**
 * @brief Funcao que analisa e processa mais termos em uma expressao.
 * 
 * Esta funcao verifica se o token atual e um operador de adicao ou subtracao, indicando mais termos na expressao.
 * Se for, continua analisando os tokens subsequentes para validar a sintaxe dos termos adicionais.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void more_term(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é um símbolo de subtração
    if (strcmp(token->_class, "simbolo_menos") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);

        // Analisa o próximo termo
        term(file, foutput, keywords, keysymbols, token, line);

        // Recursivamente analisa mais termos, se houver
        more_term(file, foutput, keywords, keysymbols, token, line);

        return;
    }

    // Verifica se o token atual é um símbolo de adição
    if (strcmp(token->_class, "simbolo_mais") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);

        // Analisa o próximo termo
        term(file, foutput, keywords, keysymbols, token, line);

        // Recursivamente analisa mais termos, se houver
        more_term(file, foutput, keywords, keysymbols, token, line);

        return;
    }
}

/**
 * @brief Funcao que analisa e processa um termo em uma expressao.
 * 
 * Esta funcao chama outras funcoes para analisar fatores e mais fatores dentro do termo.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void term(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Analisa o fator inicial do termo
    factor(file, foutput, keywords, keysymbols, token, line);

    // Analisa mais fatores, se houver
    more_factor(file, foutput, keywords, keysymbols, token, line);
}

/**
 * @brief Funcao que analisa e processa operadores unarios em uma expressao.
 * 
 * Esta funcao verifica se o token atual e um operador unario de adicao ou subtracao.
 * Se for, consome o token e continua analisando os tokens subsequentes.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void unary_operator(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é um símbolo de subtração
    if (strcmp(token->_class, "simbolo_menos") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um símbolo de adição
    if (strcmp(token->_class, "simbolo_mais") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }
}

/**
 * @brief Funcao que analisa e processa uma expressao.
 * 
 * Esta funcao chama outras funcoes para analisar operadores unarios, termos e mais termos na expressao.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void expression(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Analisa o operador unario, se houver
    unary_operator(file, foutput, keywords, keysymbols, token, line);

    // Analisa o termo inicial da expressao
    term(file, foutput, keywords, keysymbols, token, line);
    
    // Analisa mais termos, se houver
    more_term(file, foutput, keywords, keysymbols, token, line);
}
