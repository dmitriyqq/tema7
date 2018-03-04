#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Database.h"

FILE * openTable(const char * name, const char* opts){
    size_t sz = strlen(name) + strlen(".table") + 1;
    char filename[sz];
    filename[sz - 1] = '\0';
    log(filename);
    strcpy(filename, name);
    FILE *f = fopen(strcat(filename, ".table"), opts);

    if(!f){
        log(strcat("Couldn't open table name = ", name));
        exit(-1);
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

void writeDatabase(const struct Database *db, FILE *f){
    fwrite(db, sizeof(struct Database), 1, f);
}

int loadTableInMemory(const struct Database *db,
                      uint32 tableId,
                      struct Array *array){

    struct Table * table = &db->tables[tableId];
    FILE * f = openTable(table->name, "rb");

    array->memory = malloc(table->record_size * table->record_size);

    size_t readed = fread(array->memory,
                          table->record_size,
                          table->num_records, f);

    array->size = table->num_records;

    fclose(f);

    if(readed != table->record_size * table->num_records)
        return -1;
    else
        return 1;

}

int loadDatabase(struct Database *outDB, FILE *f){

    size_t readed = fread(outDB, sizeof(struct Database), 1, f);

    if(readed != sizeof(struct Database)){
        return -1;
    } else{
        return  1;
    }

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
    struct Table *table = &db->tables[tableId];
    FILE * f = openTable(table->name, "rb");

    byte buf[table->record_size];
    printf("total: %d records\n", table->num_records);
    for(int i = 0; i < table->num_records; i++){
        size_t r = fread(buf, sizeof(buf), 1, f);
        if(r != sizeof(buf)){
            log("Reached end of file, but not enough data have been read");
        }

        print(buf, db);
    }

    fclose(f);
}

void addRecords(const struct Database *db, uint32 tableId, void* record, int count){
    struct Table *table = &db->tables[tableId];
    FILE *f = openTable(table->name, "ab");

    fwrite(record, table->record_size, count, f);

    table->num_records+=count;

    fclose(f);
}

void* getRecord(struct Database* db, uint32 tableId, int id){
    struct Table *table = &db->tables[tableId];
    FILE *f = openTable(table->name, "rb");

    fseek(f, SEEK_SET, id * table->record_size);
    void* array = malloc(table->record_size);
    fread(array, table->record_size, 1, f);
    fclose(f);

    return array;
}