#include "../../header/variable.h"

/**
 * @brief Funcao que analisa e processa mais declaracoes de variaveis.
 * 
 * Esta funcao verifica se o token atual e uma virgula, indicando mais declaracoes de variaveis.
 * Se for, continua analisando os tokens subsequentes para validar a sintaxe das variaveis adicionais.
 * Caso haja erros, escreve mensagens de erro apropriadas no arquivo de saida.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void more_var(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é uma virgula
    if (strcmp(token->_class, "simbolo_virgula") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o próximo token é um identificador
        if (strcmp(token->_class, "ident") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um identificador na linha", line);
        }
        
        // Recursivamente analisa mais variaveis, se houver
        more_var(file, foutput, keywords, keysymbols, token, line);
    }
}

/**
 * @brief Funcao que analisa e processa declaracoes de variaveis.
 * 
 * Esta funcao verifica se o token atual e a palavra-chave "VAR".
 * Se for, continua analisando os tokens subsequentes para validar a sintaxe da declaracao de variaveis.
 * Caso haja erros, escreve mensagens de erro apropriadas no arquivo de saida.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void variable(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é a palavra-chave "VAR"
    if (strcmp(token->_class, "VAR") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o próximo token é um identificador
        if (strcmp(token->_class, "ident") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um identificador na linha", line);
        }
        
        // Analisa mais variaveis, se houver
        more_var(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o próximo token é um ponto-e-virgula
        if (strcmp(token->_class, "simbolo_ponto_virgula") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: ponto-e-virgula ';' faltando na linha", line);
        }
    }
}
