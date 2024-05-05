#include "tables.h"

unsigned int hash_value(const char *word){
    unsigned int hash_value = 0;
    while (*word) {
        hash_value = (hash_value * 31) + *word++;
    }
    return hash_value % HASH_SIZE;
}

void insert_word(HashTable *hash_table, const char *word){
    unsigned int index = hash_value(word);
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        //memoria insuficiente
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->word, word);
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
}

int search_word(HashTable *hash_table, const char *word){
    unsigned int index = hash_value(word);
    Node *current = hash_table->table[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

HashTable make_KeyWords(){
    HashTable hash_table;
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table.table[i] = NULL;
    }

    insert_word(&hash_table, "VAR");
    insert_word(&hash_table, "CONST");
    insert_word(&hash_table, "PROCEDURE");
    insert_word(&hash_table, "CALL");
    insert_word(&hash_table, "BEGIN");
    insert_word(&hash_table, "END");
    insert_word(&hash_table, "IF");
    insert_word(&hash_table, "THEN");
    insert_word(&hash_table, "WHILE");
    insert_word(&hash_table, "DO");

    return hash_table;
}

HashTable make_operators(){
    HashTable hash_table;
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table.table[i] = NULL;
    }

    insert_word(&hash_table, "+");
    insert_word(&hash_table, "-");
    insert_word(&hash_table, "/");
    insert_word(&hash_table, "*");
    insert_word(&hash_table, ":=");

    return hash_table;
}
