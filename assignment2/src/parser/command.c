#include "../../header/command.h"

void more_cmd(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols, TokenClass* token, int* line) {
    if (strcmp(token->_class, "simbolo_ponto_virgula") == 0) {
        lexical_analyzer(file, foutput, keywords, keysymbols, token, line);
        
        command(file, foutput, keywords, keysymbols, token, line);
        
        more_cmd(file, foutput, keywords, keysymbols, token, line);
    
    }
}

void command(FILE* file,FILE* foutput,HashTable keywords,HashTable keysymbols,TokenClass* token,int* line){
    if(strcmp(token->_class,"ident")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        if(strcmp(token->_class,"simbolo_atribuicao")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: simbolo atribuicao ':=' faltando na linha",line);
        }
        
        expression(file,foutput,keywords,keysymbols,token,line);
        
        return;
    }

    if(strcmp(token->_class,"CALL")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        if(strcmp(token->_class,"ident")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: esperava-se um identificador na linha",line);
        }
        return;
    }

    if(strcmp(token->_class,"BEGIN")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);

        command(file,foutput,keywords,keysymbols,token,line);
        
        more_cmd(file,foutput,keywords,keysymbols,token,line);
        
        if(strcmp(token->_class,"END")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: 'END' faltando na linha",line);
        }
        return;
    }

    if(strcmp(token->_class,"IF")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        
        conditional(file,foutput,keywords,keysymbols,token,line);
        
        if(strcmp(token->_class,"THEN")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: 'THEN' faltando na linha",line);
        }

        command(file,foutput,keywords,keysymbols,token,line);

        return;
    }

    if(strcmp(token->_class,"WHILE")==0){
        lexical_analyzer(file,foutput,keywords,keysymbols,token,line);

        conditional(file,foutput,keywords,keysymbols,token,line);

        if(strcmp(token->_class,"DO")==0){
            lexical_analyzer(file,foutput,keywords,keysymbols,token,line);
        } else {
            write_error(foutput,"Erro sintatico: 'DO' faltando na linha",line);
        }

        command(file,foutput,keywords,keysymbols,token,line);
        
        return;
    }
}