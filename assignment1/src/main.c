#include <stdio.h>
#include <string.h>

#include "../header/open_close.h"
#include "../header/lexical_analyzer.h"

#define TRUE 1
#define FALSE 0

int main(){
    char filename_input[100] = "program.txt";
    char filename_output[10] = "saida.txt";
    
    // recebe do usuario o nome do arquivo com os dados de entrada
    //printf("Type the filename: ");
    //scanf("%s",filename);

    FILE* file = open_file(filename_input,FILE_READT);
    FILE* foutput = open_file(filename_output,FILE_WRITET);

    // inicia o analisador lexico
    execute_lexical_analyzer(file,foutput);

    close_file(file);
    close_file(foutput);
    
    return 0;
}