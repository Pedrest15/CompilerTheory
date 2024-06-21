#include "../../header/factor.h"

/**
 * @brief Funcao que analisa e processa mais fatores em um termo.
 * 
 * Esta funcao verifica se o token atual e um operador de multiplicacao ou divisao, indicando mais fatores no termo.
 * Se for, continua analisando os tokens subsequentes para validar a sintaxe dos fatores adicionais.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void more_factor(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é um símbolo de multiplicação
    if (strcmp(token->_class, "simbolo_multiplicacao") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Analisa o próximo fator
        factor(file, foutput, keywords, keysymbols, token, line);
        
        // Recursivamente analisa mais fatores, se houver
        more_factor(file, foutput, keywords, keysymbols, token, line);

        return;
    }

    // Verifica se o token atual é um símbolo de divisão
    if (strcmp(token->_class, "simbolo_divisao") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Analisa o próximo fator
        factor(file, foutput, keywords, keysymbols, token, line);
        
        // Recursivamente analisa mais fatores, se houver
        more_factor(file, foutput, keywords, keysymbols, token, line);

        return;
    }
}

/**
 * @brief Funcao que analisa e processa um fator em um termo.
 * 
 * Esta funcao verifica se o token atual é um identificador, número ou expressão entre parênteses.
 * Se for, continua analisando os tokens subsequentes para validar a sintaxe do fator.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void factor(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é um identificador
    if (strcmp(token->_class, "ident") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um número
    if (strcmp(token->_class, "numero") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        return;
    }

    // Verifica se o token atual é um parêntese esquerdo
    if (strcmp(token->_class, "simbolo_parentese_esquerda") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Analisa a expressão dentro dos parênteses
        expression(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o token atual é um parêntese direito
        if (strcmp(token->_class, "simbolo_parentese_direita") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: parentese direito ')' faltando na linha", line);
        }
        return;
    }

    // Se nenhum fator válido for encontrado, registra um erro
    write_error(foutput, "Erro sintatico: fator faltando na linha", line);
}
