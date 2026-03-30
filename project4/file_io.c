#include "file_io.h"
#include <string.h>

bool dataset_load(Dataset *ds, const char *filename)
{
    if (!ds || !filename)
        return false;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("File '%s' not found\n", filename);
        return false;
    }

    DataType value;
    while (fscanf(file, "%lf", &value) == 1)
    {
        dataset_add(ds, value);
    }

    fclose(file);
    printf("Loaded %d values from '%s'\n", ds->count, filename);
    return true;
}

bool dataset_save(const Dataset *ds, const char *filename)
{
    if (!ds || !filename || ds->count == 0)
        return false;

    FILE *file = fopen(filename, "w");
    if (!file)
        return false;

    for (int i = 0; i < ds->count; i++)
    {
        fprintf(file, "%.2f\n", ds->data[i]);
    }

    fclose(file);
    printf("Saved %d values to '%s'\n", ds->count, filename);
    return true;
}

bool save_results(const char *filename, const char *message, const double *data, int size)
{
    if (!filename || !message || !data || size == 0)
        return false;

    FILE *file = fopen(filename, "w");
    if (!file)
        return false;

    fprintf(file, "%s\n", message);
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%.2f\n", data[i]);
    }

    fclose(file);
    return true;
}
