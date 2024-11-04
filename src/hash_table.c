#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_table.h"
#define HASH_SEED 5381

static unsigned hash(char *key, int table_size){
    unsigned long current_hash = HASH_SEED;
    int key_size = strlen(key);
    
    for (int i = 0; i < key_size; i++)  {
        char c = key[i];
        current_hash = (current_hash * 33) + c;
    };
    return current_hash % table_size;
}

static Node *create_node(char *key, char *value, Node *next) {
    Node *new_node = malloc(sizeof(Node));

    new_node->key = malloc(strlen(key) + 1);
    new_node->value = malloc(strlen(value) + 1);
    if (new_node->key == NULL || new_node->value == NULL) {
        free(new_node->key);
        free(new_node->value);  
        free(new_node);
        return NULL;
    }

    strcpy(new_node->key, key);
    strcpy(new_node->value, value);
    new_node->next = next;
    return new_node;
}

HashTable *hash_table_create(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    if (!table) {
        return NULL;
    }

    table->size = size;
    table->buckets = malloc(size * sizeof(Node*));
    if (!table->buckets) {
        free(table);
        return NULL;
    };

    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

void hash_table_insert(HashTable *table, char *key, char *value) {
    int index = hash(key, table->size);
    
    if (table->buckets[index] == NULL) {
        Node *new_node = create_node(key, value, NULL);
        if (new_node == NULL) {
            return;
        }

         table->buckets[index] = new_node;
         printf("inserted [key: %s, value: %s]\n", key, value);

    } else {
       Node *curr = table->buckets[index];
       Node *new_node = create_node(key, value, NULL); 
       if (new_node == NULL) {
           printf("insertion of [key: %s, value: %s] failed\n", key, value);
           return;
       }

       while (curr->next != NULL) {
        curr = curr->next;
       }
       curr->next = new_node;
       printf("Inserted [key: %s, value: %s] at index %d with collision\n", key, value, index);
    }
}  

char *hash_table_get(HashTable *table, char *key) {
    int index = hash(key, table->size);

    if (table->buckets[index] == NULL) {
        return NULL;
    } else if (table->buckets[index]->next == NULL) {
        return table->buckets[index]->value;
    } else {
        Node *curr = table->buckets[index];
        while (curr != NULL) {
            if (strcmp(curr->key, key) == 0) {
                return curr->value;
            } else {
                curr = curr->next;
            }
        }
        return NULL;
    }
}

void hash_table_remove(HashTable *table, char *key) {
    int index = hash(key, table->size);

    if (table->buckets[index] == NULL) {
        return;
    } 
    Node *curr = table->buckets[index];
    Node *prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            if (prev == NULL) {
                table->buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr->key);
            free(curr->value);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void hash_table_display(HashTable *table) {
    printf("Hash Table: {\n");
    for (int i = 0; i < table->size; i++) {
        Node *curr = table->buckets[i];
        while (curr != NULL) {
            printf("[key: %s, value: %s]\n", curr->key, curr->value);
            curr = curr->next;
        }
    }
    printf("}\n");
}