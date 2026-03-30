#include "dataset.h"

// Create empty dataset
Dataset *dataset_create(void)
{
    Dataset *ds = malloc(sizeof(Dataset));
    if (!ds)
        return NULL;

    ds->data = malloc(INITIAL_CAPACITY * sizeof(DataType));
    if (!ds->data)
    {
        free(ds);
        return NULL;
    }

    ds->count = 0;
    ds->capacity = INITIAL_CAPACITY;
    return ds;
}

// Free dataset
void dataset_free(Dataset *ds)
{
    if (ds)
    {
        free(ds->data);
        free(ds);
    }
}

// Add value (resize if full)
bool dataset_add(Dataset *ds, DataType value)
{
    if (!ds)
        return false;

    if (ds->count >= ds->capacity)
    {
        if (!dataset_resize(ds))
            return false;
    }

    ds->data[ds->count++] = value;
    return true;
}

// Double capacity
bool dataset_resize(Dataset *ds)
{
    if (!ds || ds->capacity >= MAX_CAPACITY)
        return false;

    int new_cap = ds->capacity * 2;
    if (new_cap > MAX_CAPACITY)
        new_cap = MAX_CAPACITY;

    DataType *new_data = realloc(ds->data, new_cap * sizeof(DataType));
    if (!new_data)
        return false;

    ds->data = new_data;
    ds->capacity = new_cap;
    return true;
}

// Print dataset
void dataset_print(const Dataset *ds)
{
    if (!ds || ds->count == 0)
    {
        printf("Dataset empty\n");
        return;
    }

    printf("Dataset (%d elements): ", ds->count);
    for (int i = 0; i < ds->count; i++)
    {
        printf("%.2f ", ds->data[i]);
    }
    printf("\n");
}

// Filter: create new dataset with filtered values
bool dataset_filter(Dataset *ds, FilterFn filter, void *param)
{
    if (!ds || !filter || ds->count == 0)
        return false;

    Dataset *filtered = dataset_create();
    if (!filtered)
        return false;

    for (int i = 0; i < ds->count; i++)
    {
        if (filter(ds->data[i], param))
        {
            dataset_add(filtered, ds->data[i]);
        }
    }

    // Replace original
    free(ds->data);
    ds->data = filtered->data;
    ds->count = filtered->count;
    ds->capacity = filtered->capacity;
    free(filtered); // data transferred
    return true;
}

// Transform all elements
bool dataset_transform(Dataset *ds, TransformFn transform, void *param)
{
    if (!ds || !transform || ds->count == 0)
        return false;

    for (int i = 0; i < ds->count; i++)
    {
        ds->data[i] = transform(ds->data[i], param);
    }
    return true;
}

// Bubble sort with comparator
void dataset_sort(Dataset *ds, CompareFn cmp)
{
    if (!ds || ds->count <= 1 || !cmp)
        return;

    for (int i = 0; i < ds->count - 1; i++)
    {
        for (int j = 0; j < ds->count - i - 1; j++)
        {
            if (cmp(ds->data[j], ds->data[j + 1]) > 0)
            {
                DataType temp = ds->data[j];
                ds->data[j] = ds->data[j + 1];
                ds->data[j + 1] = temp;
            }
        }
    }
}

// Linear search return index (-1 not found)
int dataset_search(const Dataset *ds, DataType target, CompareFn cmp)
{
    if (!ds || !cmp)
        return -1;

    for (int i = 0; i < ds->count; i++)
    {
        if (cmp(ds->data[i], target) == 0)
            return i;
    }
    return -1;
}
