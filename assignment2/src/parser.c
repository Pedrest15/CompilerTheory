#include "../header/parser.h"

void block(){

}


/**
 * @brief Funcao de alto nivel que executa o analisador lexico ate o final do arquivo.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 */
void parser(FILE* file, FILE* foutput){
    HashTable keywords = make_KeyWords();
    HashTable keysymbols = make_KeySymbols();
    TokenClass token;
    strcpy(token.value, "");
    strcpy(token._class, "");

    while (lexical_analyzer(file,foutput,keywords,keysymbols,&token) != EOF){
        printf("%s,%s\n",token.value,token._class);

        strcpy(token.value, "");
        strcpy(token._class, "");
    }

    destroy_table(keywords);
    destroy_table(keysymbols);
}

