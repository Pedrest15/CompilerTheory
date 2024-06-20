#include "../header/block.h"

void procedure(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if(strcmp(token->_class,"PROCEDURE")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);

        if(strcmp(token->_class,"ident")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um identificador na linha",line);
        }

        if(strcmp(token->_class,"simbolo_ponto_virgula")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: ponto-e-virgula ';' faltando na linha",line);
        }

        block(file,foutput,keywords,keysymbols,token,line);
        
        if(strcmp(token->_class,"simbolo_ponto_virgula")==0){
            procedure(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: ponto-e-virgula ';' faltando na linha",line);
        }
    }
}

void declaration(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token, int* line){
    constant(file,foutput,keywords,keysymbols,token,line);
    variable(file,foutput,keywords,keysymbols,token,line);
    procedure(file,foutput,keywords,keysymbols,token,line);
}

void block(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    declaration(file,foutput,keywords,keysymbols,token,line);
    command(file,foutput,keywords,keysymbols,token,line);
}