//
// Created by dima on 11.03.18.
//
#include <stdlib.h>
#include "Input.h"
#include "../Model/Datatypes.h"
#include "../Database/Database.h"

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
    char s[2];
    fflush(stdin);
    scanf("%s", s);
    return  (!strcmp(s, "Y") || !strcmp(s, "y"));
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

    if(!j->free){
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

    if(!j->free){
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