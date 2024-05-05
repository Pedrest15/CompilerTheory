#ifndef __TABLES_H__
#define __TABLES_H__

#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 17

typedef struct Node {
    char token[20];
    char token_class[25];
    struct Node *next;
} Node;

// Estrutura da tabela de dispersão
typedef struct HashTable {
    Node *table[HASH_SIZE];
} HashTable;

int search_token(HashTable *hash_table, const char *token);
char* get_token_class(HashTable *hash_table, const char *token);
HashTable make_KeyWords();
HashTable make_KeySymbols();

#endif