#ifndef INC_7_UTILS_H
#define INC_7_UTILS_H

#define NAME_SIZE 32
#define NUM_TABLES 7
#define MAX_TABLE_NAME 32
#define FIRST_NAME_SIZE         NAME_SIZE
#define LAST_NAME_SIZE          NAME_SIZE
#define MIDDLE_NAME_SIZE        NAME_SIZE
#define EDUCATION_NAME_SIZE     NAME_SIZE
#define DEPARTMENT_NAME_SIZE    NAME_SIZE
#define POSITION_NAME_SIZE      NAME_SIZE
#define SPECIALTY_NAME_SIZE     NAME_SIZE

typedef unsigned int uint32;
typedef unsigned char byte;

struct Array{
    uint32 size;
    void* memory;
};

void log(const char * msg);


#endif //INC_7_UTILS_H
