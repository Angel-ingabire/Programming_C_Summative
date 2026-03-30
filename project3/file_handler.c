#include "file_handler.h"

bool save_records(const StudentList *list)
{
    if (!list)
        return false;

    FILE *file = fopen(FILENAME, "wb");
    if (!file)
    {
        perror("Error opening file for writing");
        return false;
    }

    // Write count first
    if (fwrite(&list->count, sizeof(int), 1, file) != 1)
    {
        fclose(file);
        return false;
    }

    // Write all students
    for (int i = 0; i < list->count; i++)
    {
        if (fwrite(&list->students[i], sizeof(Student), 1, file) != 1)
        {
            fclose(file);
            return false;
        }
    }

    fclose(file);
    printf("\nRecords saved successfully to %s\n", FILENAME);
    return true;
}

bool load_records(StudentList *list)
{
    if (!list)
        return false;

    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        printf("\nNo existing records file found. Starting fresh.\n");
        return true;
    }

    // Read count
    int count;
    if (fread(&count, sizeof(int), 1, file) != 1)
    {
        fclose(file);
        printf("\nError reading records file. Starting fresh.\n");
        return true;
    }

    // Resize list if necessary
    if (count > list->capacity)
    {
        Student *new_students = realloc(list->students, count * sizeof(Student));
        if (!new_students)
        {
            fclose(file);
            return false;
        }
        list->students = new_students;
        list->capacity = count;
    }

    // Read students
    for (int i = 0; i < count; i++)
    {
        if (fread(&list->students[i], sizeof(Student), 1, file) != 1)
        {
            fclose(file);
            printf("\nError reading student %d from file.\n", i);
            list->count = i; // partial load
            return i > 0;    // partial success if any loaded
        }
        calculate_gpa(&list->students[i]);
    }

    list->count = count;
    fclose(file);
    printf("\nLoaded %d records successfully from %s\n", count, FILENAME);
    return true;
}

void initialize_file(void)
{
    FILE *file = fopen(FILENAME, "wb");
    if (file)
    {
        int zero = 0;
        fwrite(&zero, sizeof(int), 1, file);
        fclose(file);
        printf("Initialized empty records file.\n");
    }
}
