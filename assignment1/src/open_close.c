#include <stdio.h>

#include "../header/open_close.h"

//abre um arquivo no modo desejado 
FILE* open_file(char* filename, int mode){
    FILE* file;
    
    if (mode == FILE_READT) {
        file = fopen(filename, "rt");
        if (file == NULL) {
            //error_file();
            return NULL;
        }

    } else if (mode == FILE_WRITET) {
        file = fopen(filename, "wt");
        if (file == NULL) {
            //error_file();
            return NULL;
        }
    } else {
        //error_file();
        return NULL;
    }
    
    return file; // retorna o file com o ponteiro no comeco do arquivo
}

//fecha um arquivo
void close_file(FILE* file){
    fclose(file);
}