#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"


int main() {
    HashTable *table = hash_table_create(53);
    hash_table_insert(table, "profession", "software engineer");
    hash_table_insert(table, "name", "Brandon");
    
    hash_table_display(table);
    return 0;
}