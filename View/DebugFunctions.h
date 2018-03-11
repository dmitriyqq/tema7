#include "../Database/Database.h"

#ifndef INC_7_DEBUGFUNCTIONS_H
#define INC_7_DEBUGFUNCTIONS_H

void debugName(void *array, struct Database *db);

void debugEmployee(void *array, struct Database *db);

void debugJob(void *array, struct Database *db);

void debugDepartment(void *array, struct Database *db);

void debugQualification(void *array, struct Database *db);

void debugEducation(void *array, struct Database *db);

void debugPosition(void *array, struct Database *db);

void debugSpecialty(void *array, struct Database *db);

#endif //INC_7_DEBUGFUNCTIONS_H

extern void (*debugFunc[NUM_TABLES])(void*, struct Database*);