#ifndef __TABLES_H__
#define __TABLES_H__

#include <string.h>
#include <stdlib.h>

// Uma tabela hash costuma ter um numero impar como tamanho
#define HASH_SIZE 17

// Estrutura de cada no da tabela hash
typedef struct Node {
    char token[20];
    char token_class[25];
    struct Node *next;
} Node;

// Estrutura da tabela hash
typedef struct HashTable {
    Node *table[HASH_SIZE];
} HashTable;

int search_token(HashTable *hash_table, const char *token);
char* get_token_class(HashTable *hash_table, const char *token);
HashTable make_KeyWords();
HashTable make_KeySymbols();

#endif