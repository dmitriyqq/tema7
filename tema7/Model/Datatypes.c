#include "Datatypes.h"

const char TABLE_NAMES[NUM_TABLES][MAX_TABLE_NAME] = {
    "Jobs",
    "Qualifications",
};

const uint32 TABLE_RECORD_SIZES[NUM_TABLES] = {
    sizeof(struct Job),
    sizeof(struct Qualification),
};