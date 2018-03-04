#include <stdio.h>

#include "DebugFunctions.h"
#include "Datatypes.h"


void debugName(void *array, struct Database *db) {
    struct Name *e = (struct Name*) array;
    printf("%s %s %s \n", e->first_name, e->middle_name, e->last_name);
}

void debugEmployee(void *array, struct Database *db) {
    struct Employee *e = (struct Employee*) array;
    printf("Employee, id = %d, job = %d, name = ", e->id, e->job);
    debugName((void *) &e->name, NULL);

    enum TableNames jobTable = JobTable;
    void * job = getRecord(db, jobTable, e->job);

    debugJob(job, db);
}

void debugJob(void *array, struct Database *db) {
    struct Job *e = (struct Job*) array;
    printf("Job: id = %d, free = %d, salary = %f\n", e->id, e->free, e->salary);

    enum TableNames dtTable = DepartmentTable,
        qtTable = QualificationTable;

    void *dt = getRecord(db, dtTable, e->department),
         *qt = getRecord(db, qtTable, e->qualification);

    debugDepartment(dt, db);
    debugQualification(qt, db);
}

void debugDepartment(void *array, struct Database *db) {
    struct Department *e = (struct Department*) array;
    printf("Department: %s(%d)\n", e->name, e->id);
}

void debugQualification(void *array, struct Database *db) {
    struct Qualification *e = (struct Qualification*) array;
    printf("Qualification(%d): \n", e->id);

    enum TableNames edTable = EducationTable,
        spTable = SpecialtyTable,
        posTable = PositionTable;

    void *ed = getRecord(db, edTable, e->education),
        *sp = getRecord(db, spTable, e->specialty),
        *pos = getRecord(db, posTable, e->position);

    debugEducation(ed, db);
    debugPosition(pos, db);
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