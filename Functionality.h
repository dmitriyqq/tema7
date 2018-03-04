//
// Created by dima on 04.03.18.
//

#ifndef INC_7_FUNCTIONALITY_H
#define INC_7_FUNCTIONALITY_H

#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "Utils.h"
#include "Datatypes.h"
#include "Database.h"
#include "DebugFunctions.h"

#define BUF_SIZE 128

void* scanSimple(int t);

void* scanEmployee(int t);

void* scanJob(int t);

void* scanQualification(int t);


extern void* (*scanRecord[NUM_TABLES])(int t);


void loop(struct Database* db);


#endif //INC_7_FUNCTIONALITY_H
