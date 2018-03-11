#include "InputFunctions.h"


uint32 scanSimple(struct Database* db, enum TableNames table){
    printf("Create new record. \n");
    struct Department* e = (struct Department*) malloc(sizeof(struct Department));

    e->id = db->tables[table].num_records;

    char *str = promptStr("Enter name");
    strcpy(e->name, str);
    free(str);
    debugSpecialty(e, db);
    addRecords(db, table, e, 1);
    return e->id;
}

uint32 scanEmployee(struct Database* db){
    printf("Create new employee. \n");
    struct Employee* e = (struct Employee*) malloc(sizeof(struct Employee));

    e->id = db->tables[EmployeeTable].num_records;

    char *fn, *ln, *mn;

    fn = promptStr("Enter first name");
    ln = promptStr("Enter last name");
    mn = promptStr("Enter middle name");

    strcpy(e->name.first_name,  fn);
    strcpy(e->name.last_name,   ln);
    strcpy(e->name.middle_name, mn);

    free(fn);
    free(ln);
    free(mn);

    addRecords(db, EmployeeTable, e, 1);
    return e->id;
}

uint32 scanJob(struct Database* db){
    printf("Welcome! I'm Wizard, that help you to create new Job!\n");

    struct Job* e = malloc(sizeof(struct Job));

    e->id = db->tables[JobTable].num_records;

    int department = promptInt("Enter department");
    if(department <= -1)
        e->department = scanSimple(db, DepartmentTable);
    else e->department = (uint32)department;

    int employee      = promptInt("Enter employee");
    if(employee <= -1)
        e->employee = scanEmployee(db);
    else e->employee = (uint32)employee;

    int qualification = promptInt("Enter qualification");
    if(qualification <= -1)
        e->qualification = scanQualification(db);
    else e->qualification = (uint32)qualification;

    e->salary        = promptFloat("Enter salary");

    addRecords(db, JobTable, e, 1);

    return e->id;
}

uint32 scanQualification(struct Database* db){
    printf("Create new qualification. \n");
    struct Qualification* e = malloc(sizeof(struct Qualification));

    e->id = db->tables[QualificationTable].num_records;

    int education     = promptInt("Enter education");
    if(education <= -1)
        e->education = scanSimple(db, EducationTable);
    else e->education = (uint32) education;

    int specialty     = promptInt("Enter specialty");
    if(specialty <= -1)
        e->specialty = scanSimple(db, SpecialtyTable);
    else e->specialty = (uint32) specialty;

    int position     = promptInt("Enter position");
    if(position <= -1)
        e->position = scanSimple(db, PositionTable);
    else e->position = (uint32) position;

    addRecords(db, QualificationTable, e, 1);

    return e->id;
}

char* promptStr(const char * msg){
    printf(msg);
    char *str = (char*) malloc(sizeof(char) * BUF_SIZE);
    printf(": ");
    scanf("%s", str);
    return str;
}

int promptInt(const char *msg){
    do{
        char* str =  promptStr(msg);
        char* end;
        long a = strtol(str, &end, 10);
        free(str);
        if(a != 0){
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