//
// Created by dima on 09.03.18.
//

#ifndef INC_7_VIEW_H
#define INC_7_VIEW_H

#include "../Database/Database.h"

void inputCycle(struct Database * db);

void addJob(const char * dep,
            const char * pos,
            const char * sal,
            const char * free,
            const char * first,
            const char * middle,
            const char * last,
            const char * spec,
            const char * education,
            const char * experience,
            struct Database* db);
#endif //INC_7_VIEW_H
