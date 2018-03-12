//
// Created by dima on 11.03.18.
//

#ifndef INC_7_SORT_H
#define INC_7_SORT_H

#include "../Database/Database.h"
#include "../Model/Datatypes.h"

int cmpNames(struct Job* a, struct Job* b);

void swap( void **a, void **b);

int binary_search(void** a, size_t size, struct Job* value);

void getEmployees(struct Array *jobs);

int cmpSalary(struct Job* a, struct Job* b);

void getJobs(struct Array *jobs);


#endif //INC_7_SORT_H
