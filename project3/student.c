#include "student.h"

// Helper function to validate input
static bool is_valid_grade(float grade)
{
    return grade >= 0.0f && grade <= 100.0f;
}

static bool is_valid_id(StudentList *list, int id)
{
    for (int i = 0; i < list->count; i++)
    {
        if (list->students[i].id == id)
        {
            return false; // duplicate
        }
    }
    return true;
}

static bool is_valid_age(int age)
{
    return age > 0 && age < 150;
}

StudentList *create_student_list(void)
{
    StudentList *list = malloc(sizeof(StudentList));
    if (!list)
        return NULL;

    list->students = malloc(MAX_STUDENTS * sizeof(Student));
    if (!list->students)
    {
        free(list);
        return NULL;
    }

    list->count = 0;
    list->capacity = MAX_STUDENTS;
    return list;
}

void free_student_list(StudentList *list)
{
    if (list)
    {
        free(list->students);
        free(list);
    }
}

void calculate_gpa(Student *student)
{
    if (student->num_subjects == 0)
    {
        student->gpa = 0.0f;
        return;
    }

    float sum = 0.0f;
    for (int i = 0; i < student->num_subjects; i++)
    {
        sum += student->grades[i];
    }
    student->gpa = sum / student->num_subjects;
}

bool add_student(StudentList *list, Student *student)
{
    if (!list || !student)
        return false;

    // Validate inputs
    if (!is_valid_id(list, student->id) || !is_valid_age(student->age) ||
        student->num_subjects > MAX_SUBJECTS || student->num_subjects <= 0)
    {
        return false;
    }

    for (int i = 0; i < student->num_subjects; i++)
    {
        if (!is_valid_grade(student->grades[i]))
        {
            return false;
        }
    }

    // Resize if necessary
    if (list->count >= list->capacity)
    {
        int new_capacity = list->capacity * 2;
        Student *new_students = realloc(list->students, new_capacity * sizeof(Student));
        if (!new_students)
            return false;
        list->students = new_students;
        list->capacity = new_capacity;
    }

    list->students[list->count] = *student;
    calculate_gpa(&list->students[list->count]);
    list->count++;
    return true;
}

bool update_student(StudentList *list, int id, Student *updated)
{
    if (!list || !updated)
        return false;

    // Check if ID exists
    for (int i = 0; i < list->count; i++)
    {
        if (list->students[i].id == id)
        {
            // Validate new data (skip ID uniqueness check for update)
            if (!is_valid_age(updated->age) || updated->num_subjects > MAX_SUBJECTS || updated->num_subjects <= 0)
            {
                return false;
            }
            for (int j = 0; j < updated->num_subjects; j++)
            {
                if (!is_valid_grade(updated->grades[j]))
                {
                    return false;
                }
            }

            list->students[i] = *updated;
            list->students[i].id = id; // Preserve original ID
            calculate_gpa(&list->students[i]);
            return true;
        }
    }
    return false;
}

bool delete_student(StudentList *list, int id)
{
    if (!list)
        return false;

    for (int i = 0; i < list->count; i++)
    {
        if (list->students[i].id == id)
        {
            // Shift remaining students
            for (int j = i; j < list->count - 1; j++)
            {
                list->students[j] = list->students[j + 1];
            }
            list->count--;
            return true;
        }
    }
    return false;
}

Student *find_student_by_id(StudentList *list, int id)
{
    if (!list)
        return NULL;

    for (int i = 0; i < list->count; i++)
    {
        if (list->students[i].id == id)
        {
            return &list->students[i];
        }
    }
    return NULL;
}

Student *find_student_by_name(StudentList *list, const char *name)
{
    if (!list || !name)
        return NULL;

    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->students[i].name, name) == 0)
        {
            return &list->students[i];
        }
    }
    return NULL;
}

// Manual bubble sort by GPA (descending)
void sort_students_by_gpa(StudentList *list)
{
    if (!list || list->count <= 1)
        return;

    for (int i = 0; i < list->count - 1; i++)
    {
        for (int j = 0; j < list->count - i - 1; j++)
        {
            if (list->students[j].gpa < list->students[j + 1].gpa)
            {
                Student temp = list->students[j];
                list->students[j] = list->students[j + 1];
                list->students[j + 1] = temp;
            }
        }
    }
}

// Manual bubble sort by name (ascending)
void sort_students_by_name(StudentList *list)
{
    if (!list || list->count <= 1)
        return;

    for (int i = 0; i < list->count - 1; i++)
    {
        for (int j = 0; j < list->count - i - 1; j++)
        {
            if (strcmp(list->students[j].name, list->students[j + 1].name) > 0)
            {
                Student temp = list->students[j];
                list->students[j] = list->students[j + 1];
                list->students[j + 1] = temp;
            }
        }
    }
}

// Manual bubble sort by ID (ascending)
void sort_students_by_id(StudentList *list)
{
    if (!list || list->count <= 1)
        return;

    for (int i = 0; i < list->count - 1; i++)
    {
        for (int j = 0; j < list->count - i - 1; j++)
        {
            if (list->students[j].id > list->students[j + 1].id)
            {
                Student temp = list->students[j];
                list->students[j] = list->students[j + 1];
                list->students[j + 1] = temp;
            }
        }
    }
}

void display_student(const Student *student)
{
    if (!student)
        return;

    printf("\nID: %d", student->id);
    printf("\nName: %s", student->name);
    printf("\nCourse: %s", student->course);
    printf("\nAge: %d", student->age);
    printf("\nGrades: ");
    for (int i = 0; i < student->num_subjects; i++)
    {
        printf("%.1f ", student->grades[i]);
    }
    printf("\nGPA: %.2f\n", student->gpa);
    printf("------------------------\n");
}

void display_all_students(StudentList *list)
{
    if (!list || list->count == 0)
    {
        printf("\nNo students found.\n");
        return;
    }

    printf("\n=== All Students (%d total) ===\n", list->count);
    for (int i = 0; i < list->count; i++)
    {
        display_student(&list->students[i]);
    }
}
