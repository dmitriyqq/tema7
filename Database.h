#include "Utils.h"

#ifndef INC_7_DATABASE_H
#define INC_7_DATABASE_H

struct Table{
    char name[MAX_TABLE_NAME];
    uint32 id, record_size, num_records;
};

struct Database{
    uint32 num_tables;
    struct Table tables[NUM_TABLES];
};

void createNewTable(uint32 id, const char *name,
                    uint32 record_size, struct Table * outTable);


FILE * openTable(const char * name, const char* opts);


int loadTableInMemory(const struct Database *db, uint32 tableId,
                      struct Array *array);


int loadDatabase(struct Database *outDB, FILE *f);


void printTableHeader(const struct Table * table);


void printDatabaseInfo(const struct Database * db);


void debugTable(const struct Database * db, uint32 tableId,
                void (*print)(void *, struct Database *));


void addRecords(const struct Database *db, uint32 tableId,
                void* record, int count);


void* getRecord(struct Database* db, uint32 tableId, int id);

void writeDatabase(const struct Database *db, FILE *f);

#endif //INC_7_DATABASE_H
