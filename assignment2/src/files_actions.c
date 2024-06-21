#include "../header/files_actions.h"

/**
 * @brief Retrocede um char no ponteiro de arquivo.
 * 
 * Esta funcao move o ponteiro de leitura/escrita do arquivo uma posicao para tras.
 * 
 * @param file Arquivo alvo.
 */
void backtrack(FILE* file){
    fseek(file, -1, SEEK_CUR);
}

/**
 * @brief Escreve em um arquivo texto um token e sua classe.
 * 
 * Esta funcao escreve o token e sua classe no arquivo especificado no formato "token,classe".
 * 
 * @param file Arquivo alvo.
 * @param token Token a ser escrito.
 * @param token_class Classe do token, tambem escrita.
 */
void write_token(FILE* file, char* token, char* token_class){
    fprintf(file, "%s,%s\n", token, token_class);
}

/**
 * @brief Escreve uma mensagem de erro em um arquivo texto.
 * 
 * Esta funcao escreve uma mensagem de erro e a linha correspondente no arquivo especificado.
 * 
 * @param file Arquivo alvo.
 * @param msg Mensagem de erro a ser escrita.
 * @param line Linha onde o erro ocorreu.
 */
void write_error(FILE* file, char* msg, int* line){
    fprintf(file, "%s %d\n", msg, (*line));
}
