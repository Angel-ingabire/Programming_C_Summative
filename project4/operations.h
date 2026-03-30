#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "dataset.h"

// Process operation descriptors for dispatcher
typedef struct
{
    const char *name;
    ProcessFn func;
} Operation;

// Prototypes
bool op_sum_average(const double *data, int size, void *param, double *result);
bool op_min_max(const double *data, int size, void *param, double *result);
bool op_search(const double *data, int size, void *param, double *result);

#endif
