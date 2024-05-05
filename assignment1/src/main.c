#include <stdio.h>
#include <string.h>

#include "open_close.h"
#include "lexical_analyzer.h"

#define TRUE 1
#define FALSE 0

int main(){
    char filename[100] = "teste.txt";
    //printf("Type the filename: ");
    //scanf("%s",filename);

    FILE* file = open_file(filename,FILE_READT);
    if (file == NULL){
        return 0;
    }

    execute_lexical_analyzer(file);

    close_file(file);
    return 0;
}