#include "../../header/parser.h"

/**
 * @brief Funcao que analisa e processa a estrutura geral de um programa.
 * 
 * Esta funcao chama o analisador lexico para iniciar a leitura dos tokens, e depois chama a funcao block para analisar 
 * o bloco principal do programa. Verifica se o programa termina corretamente com um ponto '.'.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 * @param keywords Tabela hash contendo as palavras-chave da linguagem.
 * @param keysymbols Tabela hash contendo os simbolos da linguagem.
 * @param token Estrutura que armazena o token atual e sua classe.
 * @param line Ponteiro para a linha atual do arquivo de entrada.
 */
void program(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    // Inicia a analise lexica
    lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
    
    // Analisa o bloco principal do programa
    block(file, foutput, keywords, keysymbols, token, line);
    
    // Verifica se o programa termina com um ponto '.'
    if (strcmp(token->_class, "simbolo_ponto") == 0) {
        int symbol;
        while (1) {
            // Continua a analise lexica ate o final do arquivo
            symbol = lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
            if (symbol == EOF) {
                return;
            }
            // Registra erro se houver codigo apos o ponto final '.'
            write_error(foutput, "Erro sintatico: trecho de codigo apos '.' na linha", line);        
        }
    } else {
        // Registra erro se o programa nao terminar com um ponto '.'
        write_error(foutput, "Erro sintatico: faltou '.' ao final do programa na linha", line);
    }
}

/**
 * @brief Funcao de alto nivel que executa o analisador sintatico ate o final do arquivo.
 * 
 * Esta funcao inicializa as estruturas necessarias e chama a funcao program para iniciar a analise sintatica.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 */
void parser(FILE* file, FILE* foutput) {
    int line = 1; // Inicializa o contador de linhas
    HashTable keywords = make_KeyWords(); // Cria a tabela hash para palavras-chave
    HashTable keysymbols = make_KeySymbols(); // Cria a tabela hash para simbolos
    TokenClass token;
    strcpy(token.value, ""); // Inicializa o valor do token
    strcpy(token._class, ""); // Inicializa a classe do token

    // Inicia a analise do programa
    program(file, foutput, keywords, keysymbols, &token, &line);

    // Destroi as tabelas hash
    destroy_table(keywords);
    destroy_table(keysymbols);
}
