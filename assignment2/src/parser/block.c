#include "../../header/block.h"

/**
 * @brief Funcao que analisa e processa uma declaracao de procedimento.
 * 
 * Esta funcao verifica se o token atual e uma palavra-chave "PROCEDURE". Se for, continua analisando os tokens subsequentes para
 * validar a sintaxe do procedimento. Caso haja erros, escreve mensagens de erro apropriadas no arquivo de saida.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void procedure(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    
    // Verifica se o token atual é "PROCEDURE"
    if (strcmp(token->_class, "PROCEDURE") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);

        // Verifica se o token é um identificador
        if (strcmp(token->_class, "ident") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um identificador na linha", line);
        }

        // Verifica se o token é um ponto-e-virgula
        if (strcmp(token->_class, "simbolo_ponto_virgula") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: ponto-e-virgula ';' faltando na linha", line);
        }

        // Chama a função block para analisar o bloco de comandos do procedimento
        block(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o token é um ponto-e-virgula após o bloco
        if (strcmp(token->_class, "simbolo_ponto_virgula") == 0) {
            // Recursivamente analisa o próximo procedimento, se houver
            procedure(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: ponto-e-virgula ';' faltando na linha", line);
        }
    }
}

/**
 * @brief Funcao que analisa e processa declaracoes de constantes, variaveis e procedimentos.
 * 
 * Esta funcao chama as funcoes apropriadas para analisar constantes, variaveis e procedimentos na sequencia esperada.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void declaration(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Analisa declaracao de constantes
    constant(file, foutput, keywords, keysymbols, token, line);

    // Analisa declaracao de variaveis
    variable(file, foutput, keywords, keysymbols, token, line);
    
    // Analisa declaracao de procedimentos
    procedure(file, foutput, keywords, keysymbols, token, line);
}

/**
 * @brief Funcao que analisa e processa um bloco de comandos.
 * 
 * Esta funcao chama as funcoes apropriadas para analisar declaracoes e comandos dentro de um bloco.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void block(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Analisa declaracoes (constantes, variaveis e procedimentos)
    declaration(file, foutput, keywords, keysymbols, token, line);

    // Analisa comandos
    command(file, foutput, keywords, keysymbols, token, line);
}
