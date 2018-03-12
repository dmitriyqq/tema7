#include <stdlib.h>
#include <stdio.h>

#include "Model/Datatypes.h"
#include "Database/Database.h"
#include "View/View.h"
#include "View/Input.h"

const char* DATABASE_NAME = "database.db";

int main(int argc, char* argv[]) {

    struct Database *myDB = initDatabase(DATABASE_NAME,
                                         NUM_TABLES,
                                         TABLE_NAMES,
                                         TABLE_RECORD_SIZES);

    if(argc < 2) {
        // Main program
        inputCycle(myDB);
    }else if(argc == 11){

        for(int i = 1; i< argc; i++){
            printf("%d: %s\n", i, argv[i]);
        }
        addJob(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], myDB);
    }

    destroyDatabase(myDB);
    return 0;
}