#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef uint64_t (hashfunction)(const char*, size_t);

struct entry {
    char *name;
    int age;
    void *object;
    struct entry *next;
};

struct _hash_table {
    uint32_t size;
    hashfunction *hash;
    struct entry **elements;
};

struct _hash_table *hash_table_create(uint32_t size, hashfunction *hf);
void hash_table_destroy(struct _hash_table *ht);
void hash_table_print(struct _hash_table *ht);
bool hash_table_insert(struct _hash_table *ht, const char *name, int age, void *obj);
void *hash_table_lookup(struct _hash_table *ht, const char *name);
void *hash_table_delete(struct _hash_table *ht, const char *name);

#endif
