#ifndef INC_7_FUNCTIONALITY_H
#define INC_7_FUNCTIONALITY_H

#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "../Database/Utils.h"
#include "../Model/Datatypes.h"
#include "../Database/Database.h"

#include "DebugFunctions.h"

#define BUF_SIZE 128

uint32 scanSimple(struct Database* db, enum TableNames table);

uint32 scanEmployee(struct Database* db);

uint32 scanJob(struct Database* db);

uint32 scanQualification(struct Database* db);


char* promptStr(const char * msg);

int promptInt(const char * msg);

float promptFloat(const char * msg);


#endif //INC_7_FUNCTIONALITY_H
