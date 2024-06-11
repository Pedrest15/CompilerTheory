#include "../header/expression.h"

void more_term(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if(strcmp(token->_class,"simbolo_menos")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        term(file,foutput,keywords,keysymbols,token,line);
        more_term(file,foutput,keywords,keysymbols,token,line);

        return;
    }

    if(strcmp(token->_class,"simbolo_mais")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        term(file,foutput,keywords,keysymbols,token,line);
        more_term(file,foutput,keywords,keysymbols,token,line);

        return;
    }
}

void term(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    factor(file,foutput,keywords,keysymbols,token,line);
    more_factor(file,foutput,keywords,keysymbols,token,line);
}

void unary_operator(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if(strcmp(token->_class,"simbolo_menos")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    }

    if(strcmp(token->_class,"simbolo_mais")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    }
}

void expression(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    unary_operator(file,foutput,keywords,keysymbols,token,line);
    term(file,foutput,keywords,keysymbols,token,line);
    more_term(file,foutput,keywords,keysymbols,token,line);
}

