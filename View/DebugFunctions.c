#include <stdio.h>

#include "DebugFunctions.h"
#include "../Model/Datatypes.h"


void debugName(void *array, struct Database *db) {
    struct Name *e = (struct Name*) array;
    printf("%s %s %s \n", e->first_name, e->middle_name, e->last_name);
}

void debugEmployee(void *array, struct Database *db) {
    struct Employee *e = (struct Employee*) array;
    printf("Employee(%d): ", e->id);
    debugName((void *) &e->name, NULL);
    printf("\n");
}

void debugJob(void *array, struct Database *db) {
    struct Job *e = (struct Job*) array;
    printf("%4d: salary: %8.2f", e->id, e->salary);

    void *dt = getRecord(db, DepartmentTable, e->department),
         *qt = getRecord(db, QualificationTable, e->qualification);

    debugDepartment(dt, db);
    debugQualification(qt, db);

    if(e->employee > 0){
        void *et = getRecord(db, EmployeeTable, e->qualification);
        debugEmployee(et, db);
    }else{
        printf("Employee: free");
    }
}

void debugDepartment(void *array, struct Database *db) {
    struct Department *e = (struct Department*) array;
    printf("Department: %s(%d)\n", e->name, e->id);
}

void debugQualification(void *array, struct Database *db) {
    struct Qualification *e = (struct Qualification*) array;
    printf("Qualification(%d): \n", e->id);

    void *ed = getRecord(db, EducationTable, e->education),
         *sp = getRecord(db, SpecialtyTable, e->specialty),
        *pos = getRecord(db, PositionTable, e->position);

    debugEducation(ed, db);
    debugPosition (pos, db);
    debugSpecialty(sp, db);
}

void debugEducation(void *array, struct Database *db) {
    struct Education *e = (struct Education*) array;
    printf("Education: %s(%d)\n", e->education, e->id);
}

void debugPosition(void *array, struct Database *db) {
    struct Position *e = (struct Position*) array;
    printf("Position: %s(%d)\n", e->position, e->id);
}

void debugSpecialty(void *array, struct Database *db) {
    struct Specialty *e = (struct Specialty*) array;
    printf("Specialty: %s(%d)\n", e->specialty, e->id);
}

void (*debugFunc[NUM_TABLES])(void* array, struct Database *db) = {
    debugEmployee,
    debugDepartment,
    debugQualification,
    debugJob,
    debugEducation,
    debugPosition,
    debugSpecialty
};