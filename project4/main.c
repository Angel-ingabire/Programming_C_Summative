#include "dataset.h"
#include "file_io.h"
#include "operations.h"

// Callback implementations
bool filter_above(DataType value, void *param)
{
    return value > *(double *)param;
}

DataType transform_scale(DataType value, void *param)
{
    return value * *(double *)param;
}

int compare_asc(DataType a, DataType b)
{
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

int compare_desc(DataType a, DataType b)
{
    return compare_asc(b, a);
}

// Global dataset
static Dataset *g_ds = NULL;

// Operation table for dynamic dispatch
static Operation ops[] = {
    {"Sum & Average", op_sum_average},
    {"Min & Max", op_min_max},
    {"Search Value", op_search}};
static const int NUM_OPS = sizeof(ops) / sizeof(ops[0]);

static void print_menu(void)
{
    printf("\n=== DATA ANALYSIS TOOLKIT ===\n");
    printf("1. Create New Dataset\n");
    printf("2. Add Value\n");
    printf("3. Load from File\n");
    printf("4. Display Dataset\n");
    printf("5. Filter (> threshold)\n");
    printf("6. Transform (scale)\n");
    printf("7. Sort Ascending\n");
    printf("8. Sort Descending\n");
    printf("9. Search Value\n");
    printf("10. %s\n", ops[0].name);
    printf("11. %s\n", ops[1].name);
    printf("12. %s\n", ops[2].name);
    printf("13. Save Dataset\n");
    printf("14. Save Results\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

// Dispatcher
bool dispatch_operation(int op_idx)
{
    if (op_idx < 0 || op_idx >= NUM_OPS || !g_ds || g_ds->count == 0 || !ops[op_idx].func)
    {
        printf("Invalid operation or empty dataset!\n");
        return false;
    }

    double param[2] = {0}; // for avg/minmax
    double result;

    switch (op_idx)
    {
    case 0:
        param[0] = 0.0;
        break; // sum/avg
    case 1:
        break; // minmax uses param[0/1]
    case 2:
        printf("Search value: ");
        scanf("%lf", &param[0]);
        break;
    }

    return ops[op_idx].func(g_ds->data, g_ds->count, param, &result);
}

int main(void)
{
    g_ds = dataset_create();
    if (!g_ds)
    {
        printf("Failed to create dataset!\n");
        return 1;
    }

    int choice;
    do
    {
        print_menu();
        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            dataset_free(g_ds);
            g_ds = dataset_create();
            printf("New empty dataset created.\n");
            break;
        }
        case 2:
        {
            double val;
            printf("Value: ");
            if (scanf("%lf", &val) == 1)
            {
                if (dataset_add(g_ds, val))
                {
                    printf("Added %.2f\n", val);
                }
                else
                {
                    printf("Add failed (capacity max)\n");
                }
            }
            break;
        }
        case 3:
            dataset_load(g_ds, FILENAME);
            break;
        case 4:
            dataset_print(g_ds);
            break;
        case 5:
        {
            double thresh;
            printf("Threshold: ");
            scanf("%lf", &thresh);
            dataset_filter(g_ds, filter_above, &thresh);
            break;
        }
        case 6:
        {
            double scale;
            printf("Scale factor: ");
            scanf("%lf", &scale);
            dataset_transform(g_ds, transform_scale, &scale);
            break;
        }
        case 7:
            dataset_sort(g_ds, compare_asc);
            printf("Sorted ascending\n");
            break;
        case 8:
            dataset_sort(g_ds, compare_desc);
            printf("Sorted descending\n");
            break;
        case 9:
        {
            double target;
            printf("Search value: ");
            scanf("%lf", &target);
            int idx = dataset_search(g_ds, target, compare_asc);
            printf("Index: %d\n", idx);
            break;
        }
        case 10:
            dispatch_operation(0);
            break;
        case 11:
            dispatch_operation(1);
            break;
        case 12:
            dispatch_operation(2);
            break;
        case 13:
            dataset_save(g_ds, FILENAME);
            break;
        case 14:
            save_results(RESULTS_FILE, "Current Dataset:", g_ds->data, g_ds->count);
            break;
        case 0:
            break;
        default:
            printf("Invalid choice\n");
            break;
        }

        while (getchar() != '\n')
            ; // clear buffer

    } while (choice != 0);

    dataset_free(g_ds);
    printf("Exiting. Memory freed.\n");
    return 0;
}
