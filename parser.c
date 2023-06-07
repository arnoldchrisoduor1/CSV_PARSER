#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include <unistd.h>

typedef struct {
    char name[100];
    int age;
    // Add more fields as required
} Record;

int main() {
    const char* filename = "data.csv";

    // Check read permission
    if (access(filename, R_OK) == 0) {
        printf("Read permission is granted for %s.\n", filename);
    } else {
        printf("Read permission is not granted for %s.\n", filename);
        // Handle the case when read permission is not available
        return 1;
    }

    // Check write permission
    if (access(filename, W_OK) == 0) {
        printf("Write permission is granted for %s.\n", filename);
    } else {
        printf("Write permission is not granted for %s.\n", filename);
        // Handle the case when write permission is not available
        return 1;
    }

    // Create a hash table
    struct _hash_table *table = hash_table_create(100, NULL);  // Set an appropriate size
    if (table == NULL) {
        printf("Failed to create the hash table.\n");
        return 1;
    } else {
        printf("Hashtable created successfully!\n");
    }

    // Open the CSV file
    FILE *file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Failed to open the CSV file.\n");
        hash_table_destroy(table);
        return 1;
    } else {
        printf("CSV file opened successfully!\n");
    }

    char line[256];
    // Skip the first line (heading)
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Failed to read the CSV file.\n");
        fclose(file);
        hash_table_destroy(table);
        return 1;
    } else {
        printf("Reading CSV file\n");
    }

    while (fgets(line, sizeof(line), file)) {
        printf("Parsing line: %s", line);

        // Parse the line and extract the fields
        char *name = strtok(line, ",");
        char *ageStr = strtok(NULL, ",");

        // Create a new record and assign the values
        Record *record = malloc(sizeof(Record));
        if (record == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            hash_table_destroy(table);
            return 1;
        } else {
            printf("Memory successfully allocated\n");
        }

        strncpy(record->name, name, sizeof(record->name));
        record->age = atoi(ageStr);
        printf("Start record insertion\n");
        // Insert the record into the hash table
        if (!hash_table_insert(table, name, record->age, record)) {
            printf("Failed to insert record into the hash table.\n");
            free(record);
            fclose(file);
            hash_table_destroy(table);
            return 1;
        } else {
            printf("Record successfully inserted into the hashtable\n");
        }
    }
    printf("Done inserting to hashtable\n");
    fclose(file);
    printf("Performing analysis\n");
    // Perform analysis: calculate average age
    int totalAge = 0;
    int count = 0;

    for (uint32_t i = 0; i < table->size; i++) {
        struct entry *tmp = table->elements[i];
        while (tmp != NULL) {
            totalAge += tmp->age;
            count++;
            tmp = tmp->next;
        }
    }

    double averageAge = (count > 0) ? (double)totalAge / count : 0.0;

    // Output average age to another file
    FILE *outputFile = fopen("average_age.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open the output file.\n");
        hash_table_destroy(table);
        return 1;
    } else {
        printf("Successfully opened the output file\n");
    }

    if (fprintf(outputFile, "Average Age: %.2f\n", averageAge) < 0) {
        printf("Failed to write to the output file.\n");
        fclose(outputFile);
        hash_table_destroy(table);
        return 1;
    } else {
        printf("Successfully wrote to the output file\n");
    }

    fclose(outputFile);

    // Clean up the hash table
    hash_table_destroy(table);

    return 0;
}
