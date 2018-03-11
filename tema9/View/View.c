
#include "../Database/Utils.h"
#include "View.h"
#include "../Model/Datatypes.h"
#include "DebugFunctions.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int BUF_SIZE = 32;

void spacify(char * str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i]== '_') str[i] = ' ';
    }
}

char* promptStr(const char * msg){
    printf(msg);
    char *str = (char*) malloc(sizeof(char) * BUF_SIZE);
    printf(": ");
    scanf("%s", str);
    spacify(str);

    return str;
}

void promptStrBuf(const char * msg, char * buf){
    printf(msg);
    printf(": ");
    scanf("%s", buf);
    spacify(buf);
}

int promptYN(const char * msg){
    printf(msg);
    printf("(Y/n):");
    char c;
    fflush(stdin);
    scanf("%c", &c);

    switch (tolower(c)){
        case 't':
            return 1;
        default:
            return 0;
    }

}

int promptInt(const char *msg){
    do{
        char* str =  promptStr(msg);
        char* end;
        long a = strtol(str, &end, 10);
        free(str);
        if(a > 0){
            return (int) a;
        }else{
            log("Error parsing Int");
        }

    }while(1);
}

float promptFloat(const char *msg){
    do{
        char* str =  promptStr(msg);
        char* end;
        float a = strtof(str, &end);
        free(str);
        if(a > 0){
            return a;
        }else{
            log("Error parsing Int");
        }

    }while(1);
}


void scanJob(struct Database * db){
    printf("Enter Job!\n");

    struct Job * j = (struct Job*) malloc(sizeof(struct Job));

    promptStrBuf("Department", j->department);
    promptStrBuf("Position", j->position);
    j->salary = promptFloat("Salary");
    j->free = promptYN("Free");

    if(j->free){
        promptStrBuf("First Name", j->name.first_name);
        promptStrBuf("Middle Name", j->name.middle_name);
        promptStrBuf("Last Name", j->name.last_name);
    }else{
        memset(j->name.first_name, 0, FIRST_NAME_SIZE);
        memset(j->name.middle_name, 0, MIDDLE_NAME_SIZE);
        memset(j->name.last_name, 0, LAST_NAME_SIZE);
    }

    printf("Enter Qualification!\n");

    struct Qualification * q = (struct Qualification*) malloc(sizeof(struct Qualification));

    strcpy(q->department, j->department);
    strcpy(q->position, j->position);

    promptStrBuf("Specialty",  q->specialty);
    promptStrBuf("Education",  q->education);
    q->expirience = promptInt("Experience");

    addRecords(db, JOBS_TABLE, (void*) j ,1);
    addRecords(db, REQUIREMENTS_TABLE, (void*) q ,1);

}

void jobsFooter(){
    printf("%s\n", "*----------------*----------------*----------------*-----*");
}

void jobsHeader(){
    jobsFooter();
    printf("|%16s|%16s|%16s|%5s|\n", "Department", "Position", "Salary", "Free");
    jobsFooter();
}

void jobsFooterWithName(){
    printf("%s\n", "*----------------*----------------*----------------*-----*----------------*----------------*----------------*");
}

void jobsHeaderWithName(){
    jobsFooterWithName();
    printf("|%16s|%16s|%16s|%5s|%16s|%16s|%16s|\n", "Department", "Position", "Salary", "Free", "Las Name", "First Name", "Middle Name");
    jobsFooterWithName();
}



void qualsFooter(){
    printf("%s\n", "*----------------*----------------*----------------*----------------*-----*");
}

void qualsHeader() {
    qualsFooter();
    printf("|%16s|%16s|%16s|%16s|%5s|\n", "Department", "Position", "Specialty", "Education", "exp.");
    qualsFooter();
}


void addJob(const char * dep,
            const char * pos,
            const char * salary,
            const char * free,
            const char * first,
            const char * middle,
            const char * last,
            const char * spec,
            const char * education,
            const char * experience, struct Database* db){

    struct Job * j = (struct Job*) malloc(sizeof(struct Job));
    struct Qualification * q = (struct Qualification*) malloc(sizeof(struct Qualification));

    char * e;
    strcpy(j->department, dep);
    strcpy(j->position, pos);
    j->salary = strtof(salary, &e);
    j->free = (*free == '1') ? 1 : 0;

    if(j->free){
        strcpy(j->name.first_name, first);
        strcpy(j->name.middle_name, middle);
        strcpy(j->name.last_name, last);
    }else{
        memset(j->name.first_name, 0, FIRST_NAME_SIZE);
        memset(j->name.middle_name, 0, MIDDLE_NAME_SIZE);
        memset(j->name.last_name, 0, LAST_NAME_SIZE);
    }

    strcpy(q->department, dep);
    strcpy(q->position, pos);
    strcpy(q->specialty, spec);
    strcpy(q->education, education);
    q->expirience = (int) strtol(experience, &e, 10);

    addRecords(db, JOBS_TABLE, (void*) j ,1);
    addRecords(db, REQUIREMENTS_TABLE, (void*) q ,1);

}

checkAvailJob(struct Array *jobs, struct Array *quals, char *spec, char *ed, int exp){
    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){

        struct Job *jptr = jobs->memory[i];
        struct Qualification *qptr = quals->memory[i];
        if(!jptr->free && (strcmp(qptr->education,ed) == 0) && (strcmp(qptr->specialty, spec) == 0) && (qptr->expirience <= exp)){
            debugFunc[JOBS_TABLE]((void*)jptr);
        }
    }
    jobsFooterWithName();
}

checkJobSalaries(struct Array *jobs, int salary){
    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job *jptr = jobs->memory[i];
        if(!jptr->free && (jptr->salary >= salary)){
            debugFunc[JOBS_TABLE]((void*)jptr);
        }
    }
    jobsFooterWithName();
}

checkJob(struct Array *jobs, char* dep, char * pos){
    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job *jptr = jobs->memory[i];
        if(!jptr->free && (strcmp(jptr->position, pos) == 0) && (strcmp(jptr->department, dep) == 0)){
            debugFunc[JOBS_TABLE]((void*)jptr);
        }
    }
    jobsFooterWithName();
}


int cmpNames(struct Job* a, struct Job* b){
    struct Name *an = &a->name;
    struct Name *bn = &b->name;

    //printf("cmp %s %s\n", an->last_name, bn->last_name);


    int ls = strcmp(an->last_name, bn->last_name);
    if(ls <= -1){
        //printf("1\n");
        return 0;
    }else if(ls >= 1){
        //printf("0\n");
        return 1;
    }else{
        int fs = strcmp(an->first_name, bn->first_name);
        if(fs <= -1){
            return 0;
        }else if(fs >= 1){
            return 1;
        }else{
            int ms = strcmp(an->middle_name, bn->middle_name);
            if(ms <= -1){
                return 0;
            }else if(ms >= 1){
                return 1;
            }else{
                return  1;
            }
        }
    }

}

void swap( void **a, void **b){
    void* t = *a;
    *a = *b;
    *b = t;
}

int binary_search(void** a, size_t size, struct Job* value) {
    int l = 0, r = (int)size, m;

    while(r-l > 1){
        m = (r+l)/2;

        if(cmpNames(a[m],value))
            r = m;
        else
            l = m;
    }

    if(cmpNames(value,a[l]))
        return r;
    else
        return l;
}

void getEmployees(struct Array *jobs){
    void** a = jobs->memory;
    int size = jobs->size;


    for(int k = 1; k < size; k++){
            struct Job* c = a[k];
            int i = binary_search(a, (size_t) k, c);
            for(int j = k; j > i; j--){
                a[j] = a[j-1];
            }
            a[i] = c;
    }

    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job* cj = jobs->memory[i];
        if(cj->free){
            debugFunc[JOBS_TABLE]((void*)cj);
        }
    }
    jobsFooterWithName();

}

int cmpSalary(struct Job* a, struct Job* b){
    struct Name *an = &a->name;
    struct Name *bn = &b->name;
    //printf("cmp %s %s\n", an->last_name, bn->last_name);
    return a->salary < b->salary;

}

void getJobs(struct Array *jobs){
    void** a = jobs->memory;
    int size = jobs->size;
    int is_swapped = 1;
    int begini = 0;
    int endi = size-1;
    while (is_swapped){
        is_swapped = 0;
        for(int i = begini; i < endi; i++){
            if(cmpSalary(a[i], a[i+1])){
                is_swapped = 1;
                void *t = a[i];
                a[i] = a[i+1];
                a[i+1] = t;
            }
        }
        endi--;
        if(!is_swapped)
            break;
        is_swapped = 0;

        for(int i = endi; i >= begini; i--){
            if(cmpSalary(a[i], a[i+1])){
                is_swapped = 1;
                void *t = a[i];
                a[i] = a[i+1];
                a[i+1] = t;
            }
        }
        begini++;
    }

    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job* cj = jobs->memory[i];
        if(!cj->free){
            debugFunc[JOBS_TABLE]((void*)cj);
        }
    }
    jobsFooterWithName();

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
            break;
        }else if(!strcmp(buf, "help")){
            char commands[8][16] = {
                    "help",
                    "exit",
                    "add",
                    "jobs",
                    "quals",
                    "fquals",
                    "fsalary",
                    "check"
            };

            char description[8][100] = {
                    "print this message",
                    "close program",
                    "add new data in database",
                    "print list of jobs and employees",
                    "print list of qualifications",
                    "find jobs available for your qualification",
                    "find jobs available with desired salary",
                    "check if job available in department",


            };

            for(int i = 0; i < 8; i++)
                printf("%16s - %s\n", commands[i], description[i]);
        }else if(!strcmp(buf, "add")){
            scanJob(db);
            writeDatabase(db);
            free(jobs);
            free(quals);
            jobs  = loadTableInMemory(db, JOBS_TABLE);
            quals = loadTableInMemory(db, REQUIREMENTS_TABLE);
        }else if(!strcmp(buf, "jobs")){
            jobsHeaderWithName();
            int num_records = debugArray(jobs, TABLE_RECORD_SIZES[JOBS_TABLE], debugFunc[JOBS_TABLE]);
            jobsFooterWithName();
            printf("total: %d records\n", num_records);
        }else if(!strcmp(buf, "quals")){
            qualsHeader();
            int num_records = debugArray(quals, TABLE_RECORD_SIZES[REQUIREMENTS_TABLE], debugFunc[REQUIREMENTS_TABLE]);
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
            getEmployees(jobs);
        }else if(!strcmp(buf, "sjobs")){
            getJobs(jobs);
        }else{
            printf("Illegal symbol %s\n", buf);
        }
    }
}