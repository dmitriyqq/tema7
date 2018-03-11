#include <stdio.h>

#include "DebugFunctions.h"
#include "../Model/Datatypes.h"

void debugJob(void *array) {
    struct Job *e = (struct Job*) array;
        printf("|%16.16s|%16.16s|%16.2f|%5d|\n", e->department, e->position, e->salary, e->free);
}

void debugJobWithName(void *array) {
    struct Job *e = (struct Job*) array;
    printf("|%16.16s|%16.16s|%16.2f|%5d|%16.16s|%16.16s|%16.16s|\n", e->department, e->position, e->salary, e->free,
           (e->free) ? e->name.last_name : "", (e->free) ? e->name.first_name : "",(e->free) ? e->name.middle_name : "");
}

void debugQualification(void *array) {
    struct Qualification *q = (struct Qualification*) array;
    printf("|%16.16s|%16.16s|%16.16s|%16.16s|%5d|\n", q->department, q->position, q->specialty, q->education, q->expirience);
}

void (*debugFunc[NUM_TABLES])(void*) = {
        debugJobWithName,
        debugQualification,
};