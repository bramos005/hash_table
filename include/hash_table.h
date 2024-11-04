#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct Node {
  char* key;
  char* value;
  struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int size;
} HashTable;

extern HashTable *hash_table_create(int size);
extern void hash_table_insert(HashTable *table, char *key, char *value);
extern char *hash_table_get(HashTable *table, char *key);
extern void hash_table_remove(HashTable *table, char *key);
extern void hash_table_display(HashTable *table);

#endif