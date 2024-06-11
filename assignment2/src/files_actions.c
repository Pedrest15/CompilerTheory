#include "../header/files_actions.h"

/**
 * @brief Retrocede um char no ponteiro de arquivo
 * 
 * @param file arquivo alvo
 */
void backtrack(FILE* file){
    fseek(file, -1, SEEK_CUR);
}

/**
 * @brief Escreve em um arquivo texto um token e sua classe
 * 
 * @param file arquivo alvo
 * @param token token a ser escrito
 * @param token_classe classe do token, tambem eh escrita
 */
void write_token(FILE* file, char* token, char* token_class){
    fprintf(file, "%s,%s\n", token, token_class);

}

void write_error(FILE* file, char* msg, int* line){
    fprintf(file, "%s %d\n", msg,(*line)-3);

}

