#include "Datatypes.h"

const char TABLE_NAMES[NUM_TABLES][MAX_TABLE_NAME] = {
    "Employee",
    "Department",
    "Qualification",
    "Job",
    "Education",
    "Position",
    "Speciality"
};

const uint32 TABLE_RECORD_SIZES[NUM_TABLES] = {
    sizeof(struct Employee),
    sizeof(struct Department),
    sizeof(struct Qualification),
    sizeof(struct Job),
    sizeof(struct Education),
    sizeof(struct Position),
    sizeof(struct Specialty)
};