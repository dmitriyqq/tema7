
#include "Utils.h"
#include <stdio.h>

void log(const char * msg){
#ifdef _DEBUG
    printf("[LOG:] %s\n", msg);
#endif
}

const int BUF_SIZE = 32;