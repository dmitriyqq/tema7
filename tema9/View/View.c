
#include "View.h"
#include "DebugFunctions.h"
#include "Input.h"

#include "../Model/Datatypes.h"
#include "../Sort/Sort.h"
#include "../LinkedList/LinkedList.h"
#include "../BinTree/Tree.h"

#include <stdlib.h>

void checkAvailJob(struct Array *jobs, struct Array *quals, char *spec, char *ed, int exp){
    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job *jptr = jobs->memory[i];
        struct Qualification *qptr = quals->memory[i];
        if(jptr->free && (strcmp(qptr->education,ed) == 0) && (strcmp(qptr->specialty, spec) == 0) && (qptr->expirience <= exp)){
            debugFunc[JOBS_TABLE]((void*)jptr);
        }
    }
    jobsFooterWithName();
}

void checkJobSalaries(struct Array *jobs, float salary){
    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job *jptr = jobs->memory[i];
        if(jptr->free && (jptr->salary >= salary)){
            debugFunc[JOBS_TABLE]((void*)jptr);
        }
    }
    jobsFooterWithName();
}

void checkJob(struct Array *jobs, char* dep, char * pos){
    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job *jptr = jobs->memory[i];
        if(jptr->free && (strcmp(jptr->position, pos) == 0) && (strcmp(jptr->department, dep) == 0)){
            debugFunc[JOBS_TABLE]((void*)jptr);
        }
    }
    jobsFooterWithName();
}




struct ListNode* buildList(struct Array* array){
    if(array->size == 0)
        return NULL;

    sortDeps(array);

    struct NamedListNode* start = createNamedListNode(array->memory[0]);

    {
        struct NamedListNode *cl = start;
        for (int i = 1; i < array->size; i++) {
            struct Job *cj = array->memory[i];

            if (strcmp(cj->department, ((struct Job *) (cl->values->value))->department) == 0) {
                insertIntoNamedListNode(cl, cj);
            } else {
                insertNewNamedListNode(cl, cj);
                cl = cl->next;
            }
        }
    }

    struct NamedListNode* cnl = start;

    int full = promptYN("Show full information?");

    if(full){
        while(cnl!= NULL) {
            struct ListNode* cl = cnl->values;

            printf("Department %16s:\n", ((struct Job*)(cnl->values->value))->department);
            jobsHeaderWithName();
            while(cl!= NULL){
                debugFunc[JOBS_TABLE](cl->value);
                cl=cl->next;
            }
            jobsFooterWithName();

            cnl=cnl->next;
        }
    }else{
        char * dep = promptStr("Department");

        while(cnl!= NULL) {
            struct ListNode* cl = cnl->values;
            if(strcmp(dep, ((struct Job*)(cnl->values->value))->department) == 0){
                jobsHeaderWithName();
                while(cl!= NULL){
                    debugFunc[JOBS_TABLE](cl->value);
                    cl=cl->next;
                }
                jobsFooterWithName();
                break;
            }

            cnl=cnl->next;
        }

        free(dep);
    }

    destroyNamedList(start);
    //sortDeps(array);
}

void buildTree(struct Array* array){
    if(array->size == 0)
        return;

    struct Node* root = createNode(array->memory[0]);
    for(int i = 1; i < array->size; i++){
        addNode(array->memory[i], &root);
    }

    traverse(root);
    destroyTree(root);
}

void inputCycle(struct Database * db){

    char buf[BUF_SIZE];
    printDatabaseInfo(db);

    struct Array *jobs, *quals;

    jobs  = loadTableInMemory(db, JOBS_TABLE);
    quals = loadTableInMemory(db, REQUIREMENTS_TABLE);


    while(1){
        scanf("%s", buf);
        if(!strcmp(buf, "exit")){
            destroyArray(jobs);
            destroyArray(quals);
            break;
        }else if(!strcmp(buf, "help")){

            #define NUM_COMMANDS 12
            const char commands[NUM_COMMANDS][16] = {
                    "help", "exit", "add", "jobs",
                    "quals", "fquals", "fsalary",
                    "check", "employees", "sjobs",
                    "jobsinfo", "depsinfo"
            };

            const char description[NUM_COMMANDS][100] = {
                    "print this message",
                    "close program",
                    "add new data in database",
                    "print list of jobs and employees",
                    "print list of qualifications",
                    "find jobs available for your qualification",
                    "find jobs available with desired salary",
                    "check if job available in department",
                    "get list of employees in alphabetic order",
                    "get vacations order by salary",
                    "get jobs info",
                    "get department info"
            };

            for(int i = 0; i < NUM_COMMANDS; i++)
                printf("%16s - %s\n", commands[i], description[i]);
        }else if(!strcmp(buf, "add")){
            scanJob(db);
            writeDatabase(db);
            destroyArray(jobs);
            destroyArray(quals);
            jobs  = loadTableInMemory(db, JOBS_TABLE);
            quals = loadTableInMemory(db, REQUIREMENTS_TABLE);
        }else if(!strcmp(buf, "jobs")){
            jobsHeaderWithName();
            int num_records = debugArray(jobs,
                                         TABLE_RECORD_SIZES[JOBS_TABLE],
                                         debugFunc[JOBS_TABLE]);
            jobsFooterWithName();
            printf("total: %d records\n", num_records);
        }else if(!strcmp(buf, "quals")){
            qualsHeader();
            int num_records = debugArray(quals,
                                         TABLE_RECORD_SIZES[REQUIREMENTS_TABLE],
                                         debugFunc[REQUIREMENTS_TABLE]);
            qualsFooter();
            printf("total: %d records\n", num_records);
        }else if(!strcmp(buf, "dbheader")){
            printDatabaseInfo(db);
        }else if(!strcmp(buf, "fquals")){

            char *spec = promptStr("Specialty");
            char *ed   = promptStr("Education");
            int   exp  = promptInt("Experience");

            checkAvailJob (jobs, quals, spec, ed, exp);

            free(spec);
            free(ed);
        }else if(!strcmp(buf, "fsalary")){
            float desire = promptFloat("Desired salary");
            checkJobSalaries(jobs, desire);
        }else if(!strcmp(buf, "check")){
            char *dep = promptStr("Department");
            char *position = promptStr("Position");
            checkJob(jobs, dep, position);
        }else if(!strcmp(buf, "employees")){
            sortEmployees(jobs);
        }else if(!strcmp(buf, "sjobs")){
            sortJobs(jobs);
        }else if(!strcmp(buf, "jobsinfo")){
            buildTree(jobs);
        }else if(!strcmp(buf, "depsinfo")){
            buildList(jobs);
        }else{
            printf("Illegal symbol %s\n", buf);
        }
    }
}