#include "operations.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

bool op_sum_average(const double *data, int size, void *param, double *result)
{
    if (!data || size == 0 || !result)
        return false;

    double sum = 0.0;
    for (int i = 0; i < size; i++)
        sum += data[i];

    double *avg = (double *)param;
    *avg = sum / size;
    *result = sum;
    printf("Sum: %.2f, Average: %.2f\n", *result, *avg);
    return true;
}

bool op_min_max(const double *data, int size, void *param, double *result)
{
    if (!data || size == 0 || !result || !param)
        return false;

    double *min = ((double *)param) + 0;
    double *max = ((double *)param) + 1;

    *min = data[0];
    *max = data[0];

    for (int i = 0; i < size; i++)
    {
        if (data[i] < *min)
            *min = data[i];
        if (data[i] > *max)
            *max = data[i];
    }

    *result = *max - *min;
    printf("Min: %.2f, Max: %.2f, Range: %.2f\n", *min, *max, *result);
    return true;
}

bool op_search(const double *data, int size, void *param, double *result)
{
    if (!data || size == 0 || !param || !result)
        return false;

    double target = *(double *)param;
    int index = -1;
    for (int i = 0; i < size; i++)
    {
        if (fabs(data[i] - target) < 1e-6)
        {
            index = i;
            break;
        }
    }

    *result = index;
    if (index >= 0)
    {
        printf("Found %.2f at index %d\n", target, index);
    }
    else
    {
        printf("Value %.2f not found\n", target);
    }
    return true;
}
