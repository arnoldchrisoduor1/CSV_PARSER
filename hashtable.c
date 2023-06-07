#include "hashtable.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static size_t hash_table_index(struct _hash_table *ht, const char *name) {
    if (name == NULL) {
        // Handle NULL input (e.g., return a default value or error)
        printf("Error: NULL name.\n");
        return 0;
    }

    size_t result = (ht->hash(name, strlen(name)) % ht->size);
    return result;
}


struct _hash_table *hash_table_create(uint32_t size, hashfunction *hf){
    struct _hash_table *ht = malloc(sizeof(*ht));
    ht->size = size;
    ht->hash = hf;
    ht->elements = calloc(ht->size, sizeof(struct entry*));
    return ht;
}

void hash_table_destroy(struct _hash_table *ht){
    free(ht->elements);
    free(ht);
}

void hash_table_print(struct _hash_table *ht){
    printf("Start Table\n");
    for(uint32_t i =0; i < ht->size; i++){
        if(ht->elements[i] == NULL){
            //do we want to print all NULL entries?
            //printf("\t%i\t---\n",i);
        } else {
            printf("\t%i\t\n",i);
            struct entry *tmp = ht->elements[i];
            while(tmp != NULL){
                printf("\"%s\"(%d)(%p) - ", tmp->name, tmp->age, tmp->object);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End Table\n");
}

bool hash_table_insert(struct _hash_table *ht, const char *name, int age, void *obj) {
    if (name == NULL || obj == NULL) {
        printf("Error: Invalid input.\n");
        return false;
    }

    size_t index = hash_table_index(ht, name);
    printf("Inserting record with name: %s, age: %d, at index: %zu\n", name, age, index);

    if (hash_table_lookup(ht, name) != NULL) {
        printf("Error: Entry with the same name already exists.\n");
        return false;
    }

    struct entry *new_entry = malloc(sizeof(struct entry));
    if (new_entry == NULL) {
        printf("Error: Memory allocation failed.\n");
        return false;
    }

    new_entry->name = malloc(strlen(name) + 1);
    if (new_entry->name == NULL) {
        printf("Error: Memory allocation failed.\n");
        free(new_entry);
        return false;
    }
    strcpy(new_entry->name, name);

    new_entry->age = age;
    new_entry->object = obj;
    new_entry->next = NULL;

    if (ht->elements[index] == NULL) {
        ht->elements[index] = new_entry;
        printf("Inserted at index %zu\n", index);
    } else {
        struct entry *tmp = ht->elements[index];
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_entry;
        printf("Appended at index %zu\n", index);
    }

    return true;
}

void *hash_table_lookup(struct _hash_table *ht, const char *name) {
    size_t index = hash_table_index(ht, name);

    struct entry *tmp = ht->elements[index];
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            return tmp->object;
        }
        tmp = tmp->next;
    }

    return NULL;
}

void *hash_table_delete(struct _hash_table *ht, const char *name) {
    size_t index = hash_table_index(ht, name);

    struct entry *prev = NULL;
    struct entry *curr = ht->elements[index];

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            if (prev == NULL) {
                ht->elements[index] = curr->next;
            } else {
                prev->next = curr->next;
            }

            void *obj = curr->object;
            free(curr->name);
            free(curr);

            return obj;
        }

        prev = curr;
        curr = curr->next;
    }

    return NULL;
}
