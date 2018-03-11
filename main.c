#include <stdlib.h>
#include <stdio.h>

#include "Model/Datatypes.h"
#include "Database/Database.h"
#include "View/InputFunctions.h"
#include "View/View.h"




const char* DATABASE_NAME = "database.db";

int main(int argc, char* argv[]) {

    struct Database *myDB = initDatabase(DATABASE_NAME,
                                         NUM_TABLES,
                                         TABLE_NAMES,
                                         TABLE_RECORD_SIZES);

    //printDatabaseInfo(myDB);
    inputCycle(myDB);
    destroyDatabase(myDB);

    return 0;
}