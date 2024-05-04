#include <stdio.h>
#include <string.h>

#include "open_close.h"

void execute_lexical_analyzer(FILE* file){
    char letter;
    while ((letter = fgetc(file)) != EOF) {
        // Exibe a letra lida
        printf("Letra lida: %c\n", letter);
    }
}

int main(){
    char filename[100];
    printf("Type the filename: ");
    scanf("%s",filename);

    FILE* file = open_file(filename,FILE_READT);
    if (file == NULL){
        return 0;
    }

    execute_lexical_analyzer(file);


    close_file(file);
    return 0;
}