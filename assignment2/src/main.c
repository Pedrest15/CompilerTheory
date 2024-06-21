#include <stdio.h>
#include <string.h>

#include "../header/open_close.h"
#include "../header/parser.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    char filename_output[10] = "saida.txt";

    // Verifica se o arquivo de entrada foi fornecido como argumento
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Obtém o nome do arquivo de entrada a partir dos argumentos da linha de comando
    char *filename_input = argv[1];

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
