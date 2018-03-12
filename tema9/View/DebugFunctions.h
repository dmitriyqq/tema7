#include "../Database/Database.h"

#ifndef INC_7_DEBUGFUNCTIONS_H
#define INC_7_DEBUGFUNCTIONS_H

void debugJob(void *array);

void coutQualification(void *array);

void coutJob(void *array);

extern void (*debugFunc[NUM_TABLES])(void*);

void jobsFooter();

void jobsHeader();

void jobsFooterWithName();

void jobsHeaderWithName();

void qualsFooter();

void qualsHeader();

#endif //INC_7_DEBUGFUNCTIONS_H
