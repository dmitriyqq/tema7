

#ifndef INC_7_DATABASE_H
#define INC_7_DATABASE_H

#include <stdio.h>
#include "Utils.h"

struct Table{
    char name[MAX_TABLE_NAME];
    uint32 id, record_size, num_records;
    FILE* file;
};

struct Database{
    uint32 num_tables;
    struct Table tables[NUM_TABLES];
    FILE* file;
};

struct Database* initDatabase(
        const char* filename,
        uint32 num_tables,
        const char table_names[][MAX_TABLE_NAME],
        const uint32 table_sizes[]);

void destroyTable(struct Table* table);

void destroyDatabase(struct Database* database);

void createNewTable(
        uint32 id,
        const char *name,
        uint32 record_size,
        struct Table * outTable);


FILE * openFileOrCreateNew(const char* name);


struct Array* loadTableInMemory(
        const struct Database *db,
        uint32 tableId);


void printTableHeader(const struct Table * table);

void printDatabaseInfo(const struct Database * db);

void debugTable(
        const struct Database * db,
        uint32 tableId,
        void (*print)(void *, struct Database *));


void addRecords(
        struct Database *db,
        uint32 tableId,
        void* record, int count);


void* getRecord(
        struct Database* db,
        uint32 tableId,
        int id);

void writeDatabase(const struct Database *db);

#endif //INC_7_DATABASE_H
