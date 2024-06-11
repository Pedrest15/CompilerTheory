#include "../header/factor.h"

void more_factor(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if(strcmp(token->_class,"simbolo_multiplicacao")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        factor(file,foutput,keywords,keysymbols,token,line);
        more_factor(file,foutput,keywords,keysymbols,token,line);

        return;
    }

    if(strcmp(token->_class,"simbolo_divisao")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        factor(file,foutput,keywords,keysymbols,token,line);
        more_factor(file,foutput,keywords,keysymbols,token,line);

        return;
    }
}

void factor(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if(strcmp(token->_class,"ident")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);

        return;
    }

    if(strcmp(token->_class,"numero")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);

        return;
    }

    if(strcmp(token->_class,"simbolo_parentese_esquerda")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        expression(file,foutput,keywords,keysymbols,token,line);
        if(strcmp(token->_class,"simbolo_parentese_direita")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: parentese direito ')' faltando na linha",line);
        }
        return;
    } else {
        write_error(foutput,"Erro sintatico: parentese esquerdo '()' faltando na linha",line);
    }
}
