#include "../../header/parser.h"

void program(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
    block(file,foutput,keywords,keysymbols,token,line);
    
    // o '.' demarca o fim do codigo do programa
    if (strcmp(token->_class,"simbolo_ponto")==0) {
        int symbol;
        while(1){
            symbol = lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
            if (symbol == EOF){
                return;
            }
            write_error(foutput,"Erro sintatico: trecho de codigo apos '.' na linha",line);        
        }
    } else {
        write_error(foutput,"Erro sintatico: faltou '.' ao final do programa na linha",line);
    }
}

/**
 * @brief Funcao de alto nivel que executa o analisador lexico ate o final do arquivo.
 * 
 * @param file Arquivo de entrada contendo o codigo fonte a ser analisado.
 * @param foutput Arquivo de saida onde os tokens e suas classes serao registrados.
 */
void parser(FILE* file, FILE* foutput){
    int line = 1;
    HashTable keywords = make_KeyWords();
    HashTable keysymbols = make_KeySymbols();
    TokenClass token;
    strcpy(token.value, "");
    strcpy(token._class, "");

    program(file,foutput,keywords,keysymbols,&token,&line);

    destroy_table(keywords);
    destroy_table(keysymbols);
}

