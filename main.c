#include <stdlib.h>
#include <stdio.h>

#include "Datatypes.h"
#include "Database.h"
#include "Functionality.h"

#define _DEBUG 1

const char* DATABASE_NAME = "database.db";

void createDefaultDatabase(struct Database *db){
    db->num_tables = NUM_TABLES;
    for(uint32 i = 0; i < NUM_TABLES; i++){
        createNewTable(i, TABLE_NAMES[i], TABLE_RECORD_SIZES[i], &db->tables[i]);
        openTable(db->tables[i].name, "wb");
    }
}

int main(int argc, char* argv[]) {

    FILE *f = fopen(DATABASE_NAME, "rb");
    struct Database myDB;

    if(f){
        loadDatabase(&myDB, f);
        fclose(f);
    }else{
        createDefaultDatabase(&myDB);
    }


    printDatabaseInfo(&myDB);
    loop(&myDB);

    struct Array ed_options;
    enum TableNames table = EducationTable;

    int success = loadTableInMemory(&myDB, table, &ed_options);

    if(!success){
        log("Error loading Education options");
    }else{
        free(ed_options.memory);
    }

    // debugTable(&myDB, EducationTable, debugFuncs[table]);

    struct Education myEd = {1, 15,"Middle School"};

    addRecords(&myDB, EducationTable, &myEd, 1);

    writeDatabase(&myDB, fopen(DATABASE_NAME, "wb"));

    return 0;
}