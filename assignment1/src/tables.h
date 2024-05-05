#ifndef __TABLES_H__
#define __TABLES_H__

#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 11

typedef struct Node {
    char word[20];
    struct Node *next;
} Node;

// Estrutura da tabela de dispersão
typedef struct HashTable {
    Node *table[HASH_SIZE];
} HashTable;

unsigned int hash_value(const char *word);
void insert_word(HashTable *hash_table, const char *word);
int search_word(HashTable *hash_table, const char *word);
HashTable make_KeyWords();
HashTable make_operators();

#endif