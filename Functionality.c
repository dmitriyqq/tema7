#include "Functionality.h"

void* (*scanRecord[NUM_TABLES])(int t) = {
    scanEmployee,
    scanSimple,
    scanQualification,
    scanJob,
    scanSimple,
    scanSimple,
    scanSimple
};


void* scanSimple(int id){
    // !TODO FIX IT
    void* mem = malloc(sizeof(struct Department));

    struct Department* dep = (struct Department*) mem;

    dep->id = id;
    scanf("%s", dep->name);

    return (void*) dep;
}

void* scanEmployee(int t){
    struct Employee* e = malloc(sizeof(struct Employee));
    e->id = t;
    scanf("%s %s %s %d",
          e->name.first_name,
          e->name.middle_name,
          e->name.last_name,
          &e->job);
    return (void*) e;
}

void* scanJob(int t){
    struct Job* e = malloc(sizeof(struct Job));
    e->id = t;
    scanf("%d %d %d %f",
          &e->department,
          &e->free,
          &e->qualification,
          &e->salary);
    return (void*) e;
}

void* scanQualification(int t){
    struct Qualification* e = malloc(sizeof(struct Qualification));
    e->id = t;
    scanf("%d %d %d",
          &e->education,
          &e->position,
          &e->specialty
    );
    return (void*) e;
}

void loop(struct Database* db){

    enum TableNames table = EmployeeTable;

    char buf[BUF_SIZE];

    while(true){

        scanf("%s", buf);

        if(!strcmp(buf, "exit")){
            return;
        }else if(!strcmp(buf, "add")){
            int next_id = db->tables[table].num_records + 1;
            void * new_record = scanRecord[table](next_id);

            addRecords(db, table, new_record, 1);
        }else if(!strcmp(buf, "select")){
            scanf("%d", &table);
            if(table >= db->num_tables){
                printf("Input Error");
                exit(23);
            }

        }else if(!strcmp(buf, "help")){

        }else if(!strcmp(buf, "debug")){
            debugTable(db, table, debugFunc[table]);
        }else if(!strcmp(buf, "dbheader")){
            printDatabaseInfo(db);
        }
    }
}