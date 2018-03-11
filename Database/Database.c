#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Database.h"

struct Database* initDatabase(const char* filename,
                              uint32 num_tables,
                              const char table_names[][MAX_TABLE_NAME],
                              const uint32 table_sizes[]){

    const size_t DB_SIZE = sizeof(struct Database);

    struct Database * newDatabase =
            (struct Database *)malloc(DB_SIZE);


    newDatabase->num_tables = num_tables;
    FILE *f = openFileOrCreateNew(filename);

    size_t read = fread(newDatabase, DB_SIZE, 1, f);

    newDatabase->file = f;

    if(read == 1){
        log("Open existing database");
        for (uint32 i = 0; i < num_tables; i++) {
            newDatabase->tables[i].file = openFileOrCreateNew(newDatabase->tables[i].name);
        }

        return newDatabase;
    }else {
        log("Create new database");

        for (uint32 i = 0; i < num_tables; i++) {
            strcpy(newDatabase->tables[i].name, table_names[i]);
            newDatabase->tables[i].id = i;
            newDatabase->tables[i].num_records = 0;
            newDatabase->tables[i].record_size = table_sizes[i];
            newDatabase->tables[i].file = openFileOrCreateNew(table_names[i]);
        }

        return newDatabase;
    }
}


void destroyTable(struct Table* table){
    fclose(table->file);
}

void destroyDatabase(struct Database* database){
    writeDatabase(database);

    if(database->file)
        fclose(database->file);

    for(int i = 0; i < database->num_tables; i++){
        destroyTable(&database->tables[i]);
    }
    free(database);
}

FILE* openFileOrCreateNew(const char * name){

    FILE *f = fopen(name, "rb+");

    if(!f){
        log("Unable to open a file");
        f = fopen(name, "wb+");
    }

    return f;
}

void createNewTable(uint32 id, const char *name,
                    uint32 record_size, struct Table * outTable){
    strcpy(outTable->name, name);
    outTable->id = id;
    outTable->record_size = record_size;
    outTable->num_records = 0;
}

void writeDatabase(const struct Database *db){
    fseek(db->file, SEEK_SET, 0);
    fwrite(db, sizeof(struct Database), 1, db->file);
}

struct Array* loadTableInMemory(
        const struct Database *db,
        uint32 tableId){

    const struct Table *table = &db->tables[tableId];
    struct Array *array = (struct Array*) malloc(sizeof(struct Array));

    array->memory = malloc(table->num_records * table->record_size);
    array->size = table->num_records;

    fseek(table->file, SEEK_SET, 0);
    size_t read = fread(array->memory,
                        table->record_size,
                        table->num_records, table->file);

    array->size = table->num_records;

    return array;
}



void printTableHeader(const struct Table * table){
    printf("%32s(%d): "
           " %d records,"
           " %d record_size\n",
           table->name, table->id, table->num_records, table->record_size);
}

void printDatabaseInfo(const struct Database * db){
    printf("num_tables: %d\n"
               "Tables: \n", db->num_tables);

    for(int i = 0; i < db->num_tables; i++){
        printTableHeader(&db->tables[i]);
    }
}

void debugTable(const struct Database * db, uint32 tableId, void (*print)(void *, struct Database* db)){
    const struct Table *table = &db->tables[tableId];
    FILE * f = table->file;

    byte buf[table->record_size];
    printf("total: %d records\n", table->num_records);
    for(int i = 0; i < table->num_records; i++){
        size_t r = fread(buf, sizeof(buf), 1, f);
        if(r != 1){
            log("Reached end of file, but not enough data have been read");
        }
        print(buf, db);
    }

    fclose(f);
}

void addRecords(struct Database *db, uint32 tableId, void* record, int count){
    struct Table *table = &db->tables[tableId];
    FILE *f = table->file;

    fwrite(record, table->record_size, count, f);

    table->num_records+=count;
}

void* getRecord(struct Database* db, uint32 tableId, int id){
    struct Table *table = &db->tables[tableId];
    FILE *f = table->file;

    fseek(f, SEEK_SET, id * table->record_size);
    void* array = malloc(table->record_size);
    fread(array, table->record_size, 1, f);
    fclose(f);

    return array;
}