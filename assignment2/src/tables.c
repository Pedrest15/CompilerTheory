#include "../header/tables.h"

/**
 * @brief calcula o valor do indice hash para futura insercao
 * 
 * @param token recebera seu indice para a tabela
 * @return int indice do token
 */
unsigned int hash_value(const char *token){
    unsigned int hash_value = 0;
    while (*token) {
        hash_value = (hash_value * 31) + *token++;
    }
    return hash_value % HASH_SIZE;
}

/**
 * @brief Insere um token e sua classe na tabela hash
 * 
 * @param hash_table estrutura de dados usada
 * @param token serah inserido
 * @param token_class classe do token, tambem sera inserida
 * @return int retorna se a função foi concluida com sucesso ou nao 
 */
void insert_token(HashTable *hash_table, char* token, char* token_class){
    unsigned int index = hash_value(token);
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        //erro
        //lascou
    }
    strcpy(new_node->token, token);
    strcpy(new_node->token_class, token_class);
    
    //insere o novo token e sua classe na tabela, ligando esse novo no ao restante
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

/**
 * @brief Busca um token na tabela hash.
 * 
 * @param hash_table Estrutura de dados utilizada para a tabela hash.
 * @param token Token a ser buscado na tabela.
 * @return int Retorna 1 se o token for encontrado na tabela, 0 caso contrário.
 */
int search_token(HashTable *hash_table, const char *token){
    unsigned int index = hash_value(token);
    Node *current = hash_table->table[index];
    while (current != NULL) {
        if (strcmp(current->token, token) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/**
 * @brief Obtém a classe de um token na tabela hash.
 * 
 * @param hash_table Estrutura de dados utilizada para a tabela hash.
 * @param token Token do qual se deseja obter a classe.
 * @return char* Ponteiro para a classe do token, se encontrado, NULL caso contrario.
 */

char* get_token_class(HashTable *hash_table, const char *token){
    unsigned int index = hash_value(token);
    Node *current = hash_table->table[index];
    while (current != NULL) {
        if (strcmp(current->token, token) == 0) {
            return current->token_class;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Inicializa a tabela hash com as palavras-chave da linguagem.
 * 
 * @return HashTable Tabela hash inicializada com as palavras-chave da linguagem.
 */

HashTable make_KeyWords(){
    HashTable hash_table;
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table.table[i] = NULL;
    }

    //compilador nao eh case sensitive
    insert_token(&hash_table, "var", "VAR");
    insert_token(&hash_table, "const", "CONST");
    insert_token(&hash_table, "procedure", "PROCEDURE");
    insert_token(&hash_table, "call", "CALL");
    insert_token(&hash_table, "begin", "BEGIN");
    insert_token(&hash_table, "end", "END");
    insert_token(&hash_table, "if", "IF");
    insert_token(&hash_table, "then", "THEN");
    insert_token(&hash_table, "while", "WHILE");
    insert_token(&hash_table, "do", "DO");
    insert_token(&hash_table, "odd", "ODD");

    insert_token(&hash_table, "VAR", "VAR");
    insert_token(&hash_table, "CONST", "CONST");
    insert_token(&hash_table, "PROCEDURE", "PROCEDURE");
    insert_token(&hash_table, "CALL", "CALL");
    insert_token(&hash_table, "BEGIN", "BEGIN");
    insert_token(&hash_table, "END", "END");
    insert_token(&hash_table, "IF", "IF");
    insert_token(&hash_table, "THEN", "THEN");
    insert_token(&hash_table, "WHILE", "WHILE");
    insert_token(&hash_table, "DO", "DO");
    insert_token(&hash_table, "ODD", "ODD");

    return hash_table;
}

/**
 * @brief Inicializa a tabela hash com os simbolos da linguagem.
 * 
 * @return HashTable Tabela hash inicializada com os símbolos da linguagem.
 */

HashTable make_KeySymbols(){
    HashTable hash_table;
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table.table[i] = NULL;
    }

    insert_token(&hash_table, "+", "simbolo_mais");
    insert_token(&hash_table, "-", "simbolo_menos");
    insert_token(&hash_table, "/", "simbolo_divisao");
    insert_token(&hash_table, "*", "simbolo_multiplicacao");
    insert_token(&hash_table, "=", "simbolo_comparacao");
    insert_token(&hash_table, ":=", "simbolo_atribuicao");
    insert_token(&hash_table, "<>", "simbolo_diferente_de");
    insert_token(&hash_table, ">", "simbolo_maior");
    insert_token(&hash_table, "<", "simbolo_menor");
    insert_token(&hash_table, ">=", "simbolo_maior_igual");
    insert_token(&hash_table, "<=", "simbolo_menor_igual");
    insert_token(&hash_table, ",", "simbolo_virgula");
    insert_token(&hash_table, ".", "simbolo_ponto");
    insert_token(&hash_table, ";", "simbolo_ponto_virgula");
    insert_token(&hash_table, "(", "simbolo_parentese_esquerda");
    insert_token(&hash_table, ")", "simbolo_parentese_direita");

    return hash_table;
}

void destroy_table(HashTable tb){
    for (int i = 0; i < HASH_SIZE; i++) {
        free(tb.table[i]);
    }
}