#include "../Database/Database.h"

#ifndef INC_7_DEBUGFUNCTIONS_H
#define INC_7_DEBUGFUNCTIONS_H

void debugJob(void *array);

void debugQualification(void *array);

void debugJobWithName(void *array);

extern void (*debugFunc[NUM_TABLES])(void*);

#endif //INC_7_DEBUGFUNCTIONS_H
