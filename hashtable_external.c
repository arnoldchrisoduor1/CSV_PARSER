#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person
{
    char name[MAX_NAME];
    int age;
    /* data */
    struct person *next;
} person;

person * hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table()
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    // table is empty
}

void print_table()
{
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash_table[i] == NULL)
        {
            printf("\t%i\t---\n",i);
        }
        else{
            printf("\t%i\t",i);
            person *tmp = hash_table[i];
            while(tmp != NULL){
                printf("%s - ", tmp->name);
                tmp = tmp -> next;
            }
            printf("\n");
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *p)
{
    if(p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup(char* name)
{
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0){
        tmp = tmp->next;
    }
    return tmp;
}

person *hash_table_delete(char *name)
{
   int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0){
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    if (prev == NULL){
        //deleting the head
        hash_table[index] = tmp->next;
    } else{
        prev->next = tmp->next;
    }
    return tmp;
    
}

int main()
{
    init_hash_table();
    print_table();

    person arnold = {.name = "Arnold", .age = 26};
    person jane = {.name = "Jane", .age = 25};
    person chris = {.name = "Chris", .age = 28};
    person don = {.name = "don", .age = 26};
    person esther = {.name = "esther", .age = 26};
    person purity = {.name = "purity", .age = 34};
    person garfield = {.name = "garfield", .age = 26};
    person holmer = {.name = "holmer", .age = 75};
    person sam = {.name = "sam", .age = 26};
    person geraldine = {.name = "geraldine", .age = 84};


    hash_table_insert(&arnold);
    hash_table_insert(&jane);
    hash_table_insert(&chris);
    hash_table_insert(&don);
    hash_table_insert(&esther);
    hash_table_insert(&purity);
    hash_table_insert(&garfield);
    hash_table_insert(&holmer);
    hash_table_insert(&sam);
    hash_table_insert(&geraldine);

    person *tmp = hash_table_lookup("Arnold");
    if(tmp == NULL){
        printf("Not found\n");
    } else {
        printf("Found! %s.\n", tmp->name);
    }

    tmp = hash_table_lookup("Jane");
    if(tmp == NULL){
        printf("Not found\n");
    } else {
        printf("Found! %s.\n", tmp->name);
    }

    print_table();


    return 0;
}