#include "../header/variable.h"

void more_var(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if (strcmp(token->_class,"simbolo_virgula")==0) {
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        
        if (strcmp(token->_class,"ident")==0) {
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um identificador na linha",line);
        }
        
        more_var(file,foutput,keywords,keysymbols,token,line);
    }
}

void variable(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if (strcmp(token->_class,"VAR")==0) {
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        
        if (strcmp(token->_class,"ident")==0) {
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um identificador na linha",line);
        }
        
        more_var(file,foutput,keywords,keysymbols,token,line);
        
        if (strcmp(token->_class,"simbolo_ponto_virgula")==0) {
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: ponto-e-virgula ';' faltando na linha",line);
        }
        
    }
}