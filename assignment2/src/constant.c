#include "../header/constant.h"

void more_const(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if (strcmp(token->_class,"simbolo_virgula")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line); // Consume ','
        
        if (strcmp(token->_class,"ident")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um identificador na linha",line);
        }
            
        if (strcmp(token->_class,"simbolo_comparacao")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line); // Consume '='
        } else {
            write_error(foutput,"Erro sintatico: simbolo '=' faltando na linha",line);
        }

        if (strcmp(token->_class,"numero")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um numero na linha",line);
        }
        more_const(file,foutput,keywords,keysymbols,token,line);
    }
}

void constant(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if (strcmp(token->_class,"CONST")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        
        if (strcmp(token->_class,"ident")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um identificador na linha",line);
        }

        if (strcmp(token->_class,"simbolo_comparacao")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: simbolo comparacao '=' faltando na linha",line);
        }
                
        if (strcmp(token->_class,"numero")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um numero na linha",line);
        }        
                    
        more_const(file,foutput,keywords,keysymbols,token,line);
        
        if (strcmp(token->_class,"simbolo_ponto_virgula")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: ponto-e-virgula ';' faltando na linha",line);
        }
    }
}


