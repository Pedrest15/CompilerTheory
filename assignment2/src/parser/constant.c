#include "../../header/constant.h"

/**
 * @brief Funcao que analisa e processa mais declaracoes de constantes.
 * 
 * Esta funcao verifica se o token atual e uma virgula, indicando mais declaracoes de constantes.
 * Se for, continua analisando os tokens subsequentes para validar a sintaxe das constantes adicionais.
 * Caso haja erros, escreve mensagens de erro apropriadas no arquivo de saida.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void more_const(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é uma virgula
    if (strcmp(token->_class, "simbolo_virgula") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line); // Consome ','

        // Verifica se o próximo token é um identificador
        if (strcmp(token->_class, "ident") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um identificador na linha", line);
        }

        // Verifica se o próximo token é um símbolo de comparação
        if (strcmp(token->_class, "simbolo_comparacao") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line); // Consome '='
        } else {
            write_error(foutput, "Erro sintatico: simbolo '=' faltando na linha", line);
        }

        // Verifica se o próximo token é um número
        if (strcmp(token->_class, "numero") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um numero na linha", line);
        }
        // Recursivamente analisa mais constantes, se houver
        more_const(file, foutput, keywords, keysymbols, token, line);
    }
}

/**
 * @brief Funcao que analisa e processa declaracoes de constantes.
 * 
 * Esta funcao verifica se o token atual e a palavra-chave "CONST".
 * Se for, continua analisando os tokens subsequentes para validar a sintaxe da declaracao de constantes.
 * Caso haja erros, escreve mensagens de erro apropriadas no arquivo de saida.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void constant(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é a palavra-chave "CONST"
    if (strcmp(token->_class, "CONST") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o próximo token é um identificador
        if (strcmp(token->_class, "ident") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um identificador na linha", line);
        }

        // Verifica se o próximo token é um símbolo de comparação
        if (strcmp(token->_class, "simbolo_comparacao") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: simbolo comparacao '=' faltando na linha", line);
        }
                
        // Verifica se o próximo token é um número
        if (strcmp(token->_class, "numero") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um numero na linha", line);
        }
                    
        // Analisa mais constantes, se houver
        more_const(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o próximo token é um ponto-e-virgula
        if (strcmp(token->_class, "simbolo_ponto_virgula") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: ponto-e-virgula ';' faltando na linha", line);
        }
    }
}
