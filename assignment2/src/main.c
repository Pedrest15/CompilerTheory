#include <stdio.h>
#include <string.h>

#include "../header/open_close.h"
#include "../header/parser.h"

// O programa deve ser executado da forma ./compilet file_output.txt file_input.txt
int main(int argc, char *argv[]) {
    // Verifica se o arquivo de entrada foi fornecido como argumento
    if (argc < 3) {
        printf("compiler: fatal error: no input files\ncompilation terminated.\n");
        return 1;
    }

    // Obtem o nome do arquivo de entrada e saída a partir dos argumentos da linha de comando
    char *filename_output = argv[1];
    char *filename_input = argv[2];

    // Abre o arquivo de entrada para leitura
    FILE* file = open_file(filename_input, FILE_READT);
    if (file == NULL) {
        printf("Error: Could not open input file %s\n", filename_input);
        return 1;
    }

    // Abre o arquivo de saída para escrita
    FILE* foutput = open_file(filename_output, FILE_WRITET);
    if (foutput == NULL) {
        printf("Error: Could not open output file %s\n", filename_output);
        close_file(file);
        return 1;
    }

    // Inicia o analisador sintatico
    parser(file, foutput);

    // Fecha os arquivos usados
    close_file(file);
    close_file(foutput);

    return 0;
}
