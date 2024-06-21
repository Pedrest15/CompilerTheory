#include "../../header/command.h"

/**
 * @brief Funcao que analisa e processa comandos adicionais apos um ponto-e-virgula.
 * 
 * Esta funcao verifica se o token atual e um ponto-e-virgula. Se for, continua analisando os comandos subsequentes.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void more_cmd(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é um ponto-e-virgula
    if (strcmp(token->_class, "simbolo_ponto_virgula") == 0) {
        // Analisa o próximo token
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Analisa o próximo comando
        command(file, foutput, keywords, keysymbols, token, line);
        
        // Recursivamente analisa mais comandos, se houver
        more_cmd(file, foutput, keywords, keysymbols, token, line);
    }
}

/**
 * @brief Funcao que analisa e processa comandos.
 * 
 * Esta funcao verifica o tipo de comando com base no token atual e continua analisando a sintaxe do comando.
 * Caso haja erros, escreve mensagens de erro apropriadas no arquivo de saida.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void command(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Verifica se o token atual é um identificador
    if (strcmp(token->_class, "ident") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        // Verifica se o próximo token é um símbolo de atribuição
        if (strcmp(token->_class, "simbolo_atribuicao") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: simbolo atribuicao ':=' faltando na linha", line);
        }
        
        // Analisa a expressão após o símbolo de atribuição
        expression(file, foutput, keywords, keysymbols, token, line);
        
        return;
    }

    // Verifica se o token atual é a palavra-chave "CALL"
    if (strcmp(token->_class, "CALL") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        // Verifica se o próximo token é um identificador
        if (strcmp(token->_class, "ident") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: esperava-se um identificador na linha", line);
        }
        return;
    }

    // Verifica se o token atual é a palavra-chave "BEGIN"
    if (strcmp(token->_class, "BEGIN") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);

        // Analisa o comando dentro do bloco BEGIN-END
        command(file, foutput, keywords, keysymbols, token, line);
        
        // Analisa comandos adicionais, se houver
        more_cmd(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o bloco é fechado com a palavra-chave "END"
        if (strcmp(token->_class, "END") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: 'END' faltando na linha", line);
        }
        return;
    }

    // Verifica se o token atual é a palavra-chave "IF"
    if (strcmp(token->_class, "IF") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        // Analisa a condição do IF
        conditional(file, foutput, keywords, keysymbols, token, line);
        
        // Verifica se o próximo token é a palavra-chave "THEN"
        if (strcmp(token->_class, "THEN") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: 'THEN' faltando na linha", line);
        }

        // Analisa o comando após o THEN
        command(file, foutput, keywords, keysymbols, token, line);

        return;
    }

    // Verifica se o token atual é a palavra-chave "WHILE"
    if (strcmp(token->_class, "WHILE") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);

        // Analisa a condição do WHILE
        conditional(file, foutput, keywords, keysymbols, token, line);

        // Verifica se o próximo token é a palavra-chave "DO"
        if (strcmp(token->_class, "DO") == 0) {
            lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        } else {
            write_error(foutput, "Erro sintatico: 'DO' faltando na linha", line);
        }

        // Analisa o comando após o DO
        command(file, foutput, keywords, keysymbols, token, line);
        
        return;
    }
}
