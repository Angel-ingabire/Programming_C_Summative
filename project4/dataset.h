#ifndef DATASET_H
#define DATASET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 10
#define MAX_CAPACITY 100000
#define FILENAME "dataset.dat"
#define RESULTS_FILE "results.txt"

// Dataset element type
typedef double DataType;

// Callback function pointer types
typedef bool (*FilterFn)(DataType value, void *param); // param for threshold etc.
typedef DataType (*TransformFn)(DataType value, void *param);
typedef int (*CompareFn)(DataType a, DataType b); // -1 if a<b, 0 equal, 1 a>b

// Operation function pointer
typedef bool (*ProcessFn)(const double *data, int size, void *param, double *result);

// Dynamic dataset
typedef struct
{
    DataType *data;
    int count;
    int capacity;
} Dataset;

// Function prototypes
Dataset *dataset_create(void);
void dataset_free(Dataset *ds);
bool dataset_add(Dataset *ds, DataType value);
bool dataset_resize(Dataset *ds);
void dataset_print(const Dataset *ds);
bool dataset_filter(Dataset *ds, FilterFn filter, void *param);
bool dataset_transform(Dataset *ds, TransformFn transform, void *param);
void dataset_sort(Dataset *ds, CompareFn cmp);
int dataset_search(const Dataset *ds, DataType target, CompareFn cmp);

#endif
