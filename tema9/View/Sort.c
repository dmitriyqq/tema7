//
// Created by dima on 11.03.18.
//

#include "Sort.h"
#include <string.h>
#include "DebugFunctions.h"

int cmpNames(struct Job* a, struct Job* b){
    struct Name *an = &a->name;
    struct Name *bn = &b->name;
    int ls = strcmp(an->last_name, bn->last_name);
    if(ls <= -1){
        return 0;
    }else if(ls >= 1){
        return 1;
    }else{
        int fs = strcmp(an->first_name, bn->first_name);
        if(fs <= -1){
            return 0;
        }else if(fs >= 1){
            return 1;
        }else{
            int ms = strcmp(an->middle_name, bn->middle_name);
            if(ms <= -1){
                return 0;
            }else if(ms >= 1){
                return 1;
            }else{
                return  1;
            }
        }
    }
}

void swap( void **a, void **b){
    void* t = *a;
    *a = *b;
    *b = t;
}

int binary_search(void** a, size_t size, struct Job* value) {
    int l = 0, r = (int)size, m;

    while(r-l > 1){
        m = (r+l)/2;

        if(cmpNames(a[m],value))
            r = m;
        else
            l = m;
    }

    if(cmpNames(value,a[l]))
        return r;
    else
        return l;
}

void getEmployees(struct Array *jobs){
    void** a = jobs->memory;
    int size = jobs->size;


    for(int k = 1; k < size; k++){
        struct Job* c = a[k];
        int i = binary_search(a, (size_t) k, c);
        for(int j = k; j > i; j--){
            a[j] = a[j-1];
        }
        a[i] = c;
    }

    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job* cj = jobs->memory[i];
        if(cj->free){
            debugFunc[JOBS_TABLE]((void*)cj);
        }
    }
    jobsFooterWithName();

}

int cmpSalary(struct Job* a, struct Job* b){
    struct Name *an = &a->name;
    struct Name *bn = &b->name;
    //printf("cmp %s %s\n", an->last_name, bn->last_name);
    return a->salary < b->salary;

}

void getJobs(struct Array *jobs){
    void** a = jobs->memory;
    int size = jobs->size;
    int is_swapped = 1;
    int begini = 0;
    int endi = size-1;
    while (is_swapped){
        is_swapped = 0;
        for(int i = begini; i < endi; i++){
            if(cmpSalary(a[i], a[i+1])){
                is_swapped = 1;
                swap(a[i], a[i+1]);
            }
        }
        endi--;
        if(!is_swapped)
            break;
        is_swapped = 0;

        for(int i = endi; i >= begini; i--){
            if(cmpSalary(a[i], a[i+1])){
                is_swapped = 1;
                swap(a[i], a[i+1]);
            }
        }
        begini++;
    }

    jobsHeaderWithName();
    for(int i = 0; i < jobs->size; i++){
        struct Job* cj = jobs->memory[i];
        if(!cj->free){
            debugFunc[JOBS_TABLE]((void*)cj);
        }
    }
    jobsFooterWithName();

}
