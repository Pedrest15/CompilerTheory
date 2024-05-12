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
                State current_state, char symbol, char* buffer){
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
                write_token(foutput,buffer,get_token_class(&keywords,buffer));
                printf("%s, %s\n", buffer,get_token_class(&keywords,buffer));
            } else { //caso nao seja uma palavra reservada, eh um identificador
                //escreve o token e sua classe no arquivo de saida
                write_token(foutput,buffer,"ident");
                printf("%s, id\n", buffer);
            }
            
            return TRUE;

        case DONE_KEYSYMBOL:
            // Coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            // Confere se buffer contém um símbolo reservado
            if (search_token(&keysymbols, buffer)) {
                // Escreve o token e sua classe no arquivo de saída
                write_token(foutput,buffer,get_token_class(&keysymbols,buffer));
                printf("%s, %s\n", buffer,get_token_class(&keysymbols,buffer));
            } else {
                // Erro apenas se o buffer não estiver vazio
                if (strlen(buffer) > 0) {
                    printf("%s, ERRO: Caractere Inválido!\n", buffer);
                    printf("%c, erro lexico\n", symbol);

                }
            }

            return TRUE;


        case DONE_IDENTIFIER:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }

            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //escreve o token e sua classe identificador no arquivo de saida
            write_token(foutput,buffer,"ident");
            printf("%s, id\n", buffer);
            return TRUE;

        case DONE_NUMBER:
            //retroceder um caracter
            if (symbol != EOF){
                backtrack(file);
            }

            //coloca \0 no buffer para escrever no arquivo sem problemas
            buffer[strlen(buffer)] = '\0';

            //escreve o token e sua classe numero no arquivo de saida
            write_token(foutput,buffer,"numero");
            printf("%s, num\n", buffer);

        case DONE_COMMENT:
            //comentarios sao ignorados para o arquivo de saida
            return TRUE;
        case ERROR:
            return TRUE;

        default:
            //caso o estado atual nao seja um estado final
            return FALSE;
    }
}