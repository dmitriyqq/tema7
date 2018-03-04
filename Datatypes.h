#ifndef INC_7_DATATYPES_H
#define INC_7_DATATYPES_H

#include "Utils.h"

enum TableNames{
    EmployeeTable = 0,
    DepartmentTable = 1,
    QualificationTable = 2,
    JobTable = 3,
    EducationTable = 4,
    PositionTable = 5,
    SpecialtyTable = 6
};

extern const char TABLE_NAMES[NUM_TABLES][MAX_TABLE_NAME];

struct Name{
    char middle_name[MIDDLE_NAME_SIZE],
         first_name[FIRST_NAME_SIZE],
         last_name[LAST_NAME_SIZE];
};

struct Employee{
    uint32 id, job;
    struct Name name;
};

struct Job{
    uint32 id, qualification, free, department;
    float salary;
};

struct Department{
    uint32 id;
    char name[DEPARTMENT_NAME_SIZE];
};

struct Qualification{
    uint32 id,
           education,
           position,
           specialty;
};

struct Education{
    uint32 id;
    const char education[EDUCATION_NAME_SIZE];

};

struct Position{
    uint32 id;
    const char position[POSITION_NAME_SIZE];
};

struct Specialty{
    uint32 id;
    const char specialty[SPECIALTY_NAME_SIZE];
};

extern const uint32 TABLE_RECORD_SIZES[NUM_TABLES];


#endif //INC_7_DATATYPES_H
