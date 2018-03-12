//
// Created by dima on 11.03.18.
//

#ifndef INC_7_INPUT_H
#define INC_7_INPUT_H

#include <stdio.h>
#include <string.h>
#include "../Database/Database.h"


void spacify(char * str);

char* promptStr(const char * msg);

void promptStrBuf(const char * msg, char * buf);

int promptYN(const char * msg);

int promptInt(const char *msg);

float promptFloat(const char *msg);

void scanJob(struct Database * db);

void addJob(const char * dep,
            const char * pos,
            const char * salary,
            const char * free,
            const char * first,
            const char * middle,
            const char * last,
            const char * spec,
            const char * education,
            const char * experience, struct Database* db);

#endif //INC_7_INPUT_H
