#include "../header/states.h"

/**
 * @brief Caso o estado atual seja um estado final, realiza as operacoes adequadas
 * 
 * @param file arquivo de entrada, contendo o programa em processo de compilacao
 * @param foutput arquivo de saida do analisado lexico, contem os tokens e suas classes
 * @param keywords tabela com as palavras reservadas pela linguagem
 * @param keysymbols tabela com os simbolos reservados pela linguagem
 * @param current_state estado atual da maquina de moore
 * @param symbol ultimo caracter lido na fita
 * @param buffer cadeia lida ate o momento, entre o estado inicial ate chegar um estado final
 *@return int retorna se o estado atual eh um final ou nao
 */
int final_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer,TokenClass *token){
    switch (current_state){
        case DONE_KEYWORD:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }

            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //confere se buffer contem uma palavra reservada
            if (search_token(&keywords,buffer)){
                //escreve o token e sua classe no arquivo de saida
                //write_token(foutput,buffer,get_token_class(&keywords,buffer));
                strcpy(token->value,buffer);
                strcpy(token->_class,get_token_class(&keywords,buffer));
                
            } else { //caso nao seja uma palavra reservada, eh um identificador
                //escreve o token e sua classe no arquivo de saida
                //write_token(foutput,buffer,"ident");
                strcpy(token->value,buffer);
                strcpy(token->_class,"ident");
            }

            return TRUE;

        case DONE_KEYSYMBOL:
            // Coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            // Escreve o token e sua classe no arquivo de saida
            //write_token(foutput,buffer,get_token_class(&keysymbols,buffer));
            strcpy(token->value,buffer);
            strcpy(token->_class,get_token_class(&keysymbols,buffer));

            return TRUE;

        case DONE_BACK_KEYSYMBOL:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }
            
            // Coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            // Escreve o token e sua classe no arquivo de saida
            //write_token(foutput,buffer,get_token_class(&keysymbols,buffer));
            strcpy(token->value,buffer);
            strcpy(token->_class,get_token_class(&keysymbols,buffer));

            return TRUE;

        case DONE_IDENTIFIER:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }

            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //escreve o token e sua classe identificador no arquivo de saida
            //write_token(foutput,buffer,"ident");
            strcpy(token->value,buffer);
            strcpy(token->_class,"ident");

            return TRUE;

        case DONE_NUMBER:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }

            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //escreve o token e sua classe numero no arquivo de saida
            //write_token(foutput,buffer,"numero");
            strcpy(token->value,buffer);
            strcpy(token->_class,"numero");

            return TRUE;

        case DONE_COMMENT:
            //comentarios sao ignorados para o arquivo de saida
            buffer[strlen(buffer)] = '\0';
            
            //comentario nao eh relevante ao parser
            return FALSE;

        default:
            //caso o estado atual nao seja um estado final
            return FALSE;
    }
}

/**
 * Funcao que lida com os estados de erro do automato finito deterministico (AFD).
 * Esta funcao executa as operacoes apropriadas quando o analisador lexico
 * encontra um estado de erro.
 *
 * @param file Arquivo de entrada contendo o programa em processo de compilacao.
 * @param foutput Arquivo de saida do analisador lexico, contendo os tokens e suas classes.
 * @param keywords Tabela com as palavras reservadas da linguagem.
 * @param keysymbols Tabela com os simbolos reservados da linguagem.
 * @param current_state Estado atual da maquina de Moore.
 * @param symbol Ultimo caractere lido na fita.
 * @param buffer Cadeia lida ate o momento, do estado inicial ate chegar a um estado final.
 * @return Retorna verdadeiro se o estado atual for um estado de erro, caso contrario, retorna falso.
 */

int error_states(FILE* file, FILE* foutput, HashTable keywords, HashTable keysymbols,
                State current_state, char symbol, char* buffer,int* line){
    switch (current_state){
        case ERROR_INVALID_SYMBOL:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }

            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';
            
            //escreve no arquivo de saida
            write_error(foutput,"Erro lexico: caracter invalido na linha ",line);
            //write_token(foutput,buffer,"ERRO LEXICO => caracter invalido");

            return TRUE;
        
        case ERROR_NUMBER_LETTER:
            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //escreve no arquivo de saida
            //write_token(foutput,buffer,"ERRO LEXICO => numero seguido por letra");
            write_error(foutput,"Erro lexico: numero seguido por letra na linha",line);

            return TRUE;
        
        case ERROR_INVALID_NUMBER:
            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';
            
            //escreve no arquivo de saida
            //write_token(foutput,buffer,"ERRO LEXICO => numero com caracter invalido");
            write_error(foutput,"Erro lexico: numero com caracter invalido na linha",line);

            return TRUE;
        
        case ERROR_DOUBLE_DOTS:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }

            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //write_token(foutput,buffer,"ERRO LEXICO => faltando '=' a direita");
            write_error(foutput,"Erro lexico: simbolo '=' faltando a direita de ':' na linha",line);
            
            return TRUE;

        case ERROR_COMMENT:
            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //write_token(foutput,buffer,"ERRO LEXICO => comentario nao fechado na linha");
            write_error(foutput,"Erro lexico: comentario nao fechado na linha",line);

            return TRUE;

        case ERROR_CLOSE_COMMENT:
            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //write_token(foutput,buffer,"ERRO LEXICO => fechar comentario sem ter aberto na linha");
            write_error(foutput,"Erro lexico: fechar comentario sem ter aberto na linha",line);

            return TRUE;

        default:
            //caso o estado atual nao seja um estado de erro
            return FALSE;
    }
}