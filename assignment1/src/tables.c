#include "tables.h"

unsigned int hash_value(const char *token){
    unsigned int hash_value = 0;
    while (*token) {
        hash_value = (hash_value * 31) + *token++;
    }
    return hash_value % HASH_SIZE;
}

void insert_token(HashTable *hash_table, char* token, char* token_class){
    unsigned int index = hash_value(token);
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        //erro
        //lascou
    }
    strcpy(new_node->token, token);
    strcpy(new_node->token_class, token_class);
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

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

HashTable make_KeyWords(){
    HashTable hash_table;
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table.table[i] = NULL;
    }

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

    return hash_table;
}

HashTable make_KeySymbols(){
    HashTable hash_table;
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table.table[i] = NULL;
    }

    insert_token(&hash_table, "+", "simbolo_mais");
    insert_token(&hash_table, "-", "simbolo_menos");
    insert_token(&hash_table, "/", "simbolo_divisao");
    insert_token(&hash_table, "*", "simbolo_multiplicacao");
    insert_token(&hash_table, ":=", "simbolo_atribuicao");
    insert_token(&hash_table, "<>", "simbolo_diferente");
    insert_token(&hash_table, ">", "simbolo_maior");
    insert_token(&hash_table, "<", "simbolo_menor");
    insert_token(&hash_table, ">=", "simbolo_maior_igual");
    insert_token(&hash_table, "<=", "simbolo_menor_igual");
    insert_token(&hash_table, ",", "simbolo_virgula");
    insert_token(&hash_table, ".", "simbolo_ponto");
    insert_token(&hash_table, ";", "simbolo_ponto_virgula");

    return hash_table;
}
