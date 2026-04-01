#include "reports.h"
#include <math.h>
#include <string.h>

void generate_class_report(const StudentList *list)
{
    if (!list || list->count == 0)
    {
        printf("\nNo students to analyze.\n");
        return;
    }

    float sum_gpa = 0.0f;
    float min_gpa = list->students[0].gpa;
    float max_gpa = list->students[0].gpa;

    for (int i = 0; i < list->count; i++)
    {
        sum_gpa += list->students[i].gpa;
        if (list->students[i].gpa < min_gpa)
            min_gpa = list->students[i].gpa;
        if (list->students[i].gpa > max_gpa)
            max_gpa = list->students[i].gpa;
    }

    float avg_gpa = sum_gpa / list->count;

    // Simple median (for even count, average of middle two)
    Student temp_list[MAX_STUDENTS];
    memcpy(temp_list, list->students, list->count * sizeof(Student));
    StudentList temp = {temp_list, list->count, list->capacity};
    sort_students_by_gpa(&temp); // sort the temp copy

    float median;
    if (list->count % 2 == 0)
    {
        median = (temp_list[list->count / 2 - 1].gpa + temp_list[list->count / 2].gpa) / 2.0f;
    }
    else
    {
        median = temp_list[list->count / 2].gpa;
    }

    printf("\n=== CLASS PERFORMANCE REPORT ===\n");
    printf("Total Students: %d\n", list->count);
    printf("Average GPA: %.2f\n", avg_gpa);
    printf("Highest GPA: %.2f\n", max_gpa);
    printf("Lowest GPA: %.2f\n", min_gpa);
    printf("Median GPA: %.2f\n", median);
    printf("===============================\n");
}

void top_n_students(const StudentList *list, int n)
{
    if (!list || list->count == 0 || n <= 0)
    {
        printf("\nNo data for top students.\n");
        return;
    }

    int display_n = (n > list->count) ? list->count : n;

    // Create temp copy and sort
    Student temp_students[MAX_STUDENTS];
    memcpy(temp_students, list->students, list->count * sizeof(Student));
    StudentList temp = {temp_students, list->count, list->capacity};
    sort_students_by_gpa(&temp);

    printf("\n=== TOP %d PERFORMING STUDENTS ===\n", display_n);
    for (int i = 0; i < display_n; i++)
    {
        printf("%d. %s (GPA: %.2f)\n", i + 1, temp_students[i].name, temp_students[i].gpa);
    }
    printf("============================\n");
}

Student *best_student_per_course(const StudentList *list, const char *course)
{
    if (!list || !course)
        return NULL;

    Student *best = NULL;
    float best_gpa = -1.0f;

    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->students[i].course, course) == 0)
        {
            if (list->students[i].gpa > best_gpa)
            {
                best_gpa = list->students[i].gpa;
                best = (Student *)&list->students[i];
            }
        }
    }

    if (best)
    {
        printf("\nBest student in %s: %s (GPA: %.2f)\n", course, best->name, best->gpa);
    }
    else
    {
        printf("\nNo students found in course: %s\n", course);
    }
    return best;
}

void course_average(const StudentList *list, const char *course)
{
    if (!list || !course)
        return;

    float sum_gpa = 0.0f;
    int course_count = 0;

    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->students[i].course, course) == 0)
        {
            sum_gpa += list->students[i].gpa;
            course_count++;
        }
    }

    if (course_count > 0)
    {
        printf("\n%s Course Average GPA: %.2f (%d students)\n", course, sum_gpa / course_count, course_count);
    }
    else
    {
        printf("\nNo students in %s course.\n", course);
    }
}
