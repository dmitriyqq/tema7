#ifndef INC_7_DATA_TYPES_H
#define INC_7_DATA_TYPES_H

#include "../Database/Utils.h"

#define NAME_SIZE 16
#define FIRST_NAME_SIZE         NAME_SIZE
#define LAST_NAME_SIZE          NAME_SIZE
#define MIDDLE_NAME_SIZE        NAME_SIZE
#define EDUCATION_NAME_SIZE     NAME_SIZE
#define DEPARTMENT_NAME_SIZE    NAME_SIZE
#define POSITION_NAME_SIZE      NAME_SIZE
#define SPECIALTY_NAME_SIZE     NAME_SIZE

enum TableNames{
    JOBS_TABLE = 0,
    REQUIREMENTS_TABLE = 1,
};

extern const char TABLE_NAMES[NUM_TABLES][MAX_TABLE_NAME];

struct Name{
    char middle_name[MIDDLE_NAME_SIZE],
         first_name[FIRST_NAME_SIZE],
         last_name[LAST_NAME_SIZE];
};

struct Job{
    char department [DEPARTMENT_NAME_SIZE];
    char position   [POSITION_NAME_SIZE];
    float salary;
    int free;
    struct Name name;
};

struct Qualification{
    char department [DEPARTMENT_NAME_SIZE];
    char position   [POSITION_NAME_SIZE];
    char specialty  [SPECIALTY_NAME_SIZE];
    char education  [EDUCATION_NAME_SIZE];
    int expirience;
};


extern const uint32 TABLE_RECORD_SIZES[NUM_TABLES];


#endif //INC_7_DATA_TYPES_H
