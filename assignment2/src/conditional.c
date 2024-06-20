#include "../header/conditional.h"

void relational(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if (strcmp(token->_class,"simbolo_atribuicao")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
        return;
    }

    if (strcmp(token->_class,"simbolo_comparacao")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
        return;
    }

    if (strcmp(token->_class,"simbolo_diferente")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
        return;
    }

    if (strcmp(token->_class,"simbolo_menor")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
        return;
    }

    if (strcmp(token->_class,"simbolo_maior")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
        return;
    }

    if (strcmp(token->_class,"simbolo_menor_igual")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
        return;
    }

    if (strcmp(token->_class,"simbolo_maior_igual")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
    
        return;
    }

    write_error(foutput,"Erro sintatico: simbolo de relacional faltando na linha",line);
}

void conditional(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if (strcmp(token->_class,"ODD")==0) {
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);

        expression(file,foutput,keywords,keysymbols,token,line);
        
        return;
    }

    expression(file,foutput,keywords,keysymbols,token,line);

    relational(file,foutput,keywords,keysymbols,token,line);

    expression(file,foutput,keywords,keysymbols,token,line);
}




