
#include "Utils.h"

void log(const char * msg){
#ifdef _DEBUG
    printf("[LOG:] %s", msg);
#endif
}