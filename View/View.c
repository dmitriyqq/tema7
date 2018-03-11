
#include "../Database/Utils.h"
#include "View.h"
#include "InputFunctions.h"

void inputCycle(struct Database * db){
    char buf[BUF_SIZE];
    printDatabaseInfo(db);
    while(1){

        scanf("%s", buf);

        if(!strcmp(buf, "exit")){
            return;
        }else if(!strcmp(buf, "addjob")){
            scanJob(db);
        }else if(!strcmp(buf, "printjobs")){
            debugTable(db, JobTable, debugFunc[JobTable]);
        }else if(!strcmp(buf, "dbheader")){
            printDatabaseInfo(db);
        }
    }
}