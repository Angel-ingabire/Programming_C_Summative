#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Maximum number of subjects per student
#define MAX_SUBJECTS 10
#define MAX_STUDENTS 1000
#define MAX_NAME_LEN 50
#define MAX_COURSE_LEN 50
#define FILENAME "academic_records.dat"

// Student structure
typedef struct
{
    int id;
    char name[MAX_NAME_LEN];
    char course[MAX_COURSE_LEN];
    int age;
    float grades[MAX_SUBJECTS];
    int num_subjects;
    float gpa;
} Student;

// Dynamic array of students
typedef struct
{
    Student *students;
    int count;
    int capacity;
} StudentList;

// Function prototypes
StudentList *create_student_list(void);
void free_student_list(StudentList *list);
bool add_student(StudentList *list, Student *student);
bool update_student(StudentList *list, int id, Student *updated);
bool delete_student(StudentList *list, int id);
Student *find_student_by_id(StudentList *list, int id);
Student *find_student_by_name(StudentList *list, const char *name);
void sort_students_by_gpa(StudentList *list);
void sort_students_by_name(StudentList *list);
void sort_students_by_id(StudentList *list);
void display_student(const Student *student);
void display_all_students(StudentList *list);
void calculate_gpa(Student *student);

#endif // STUDENT_H
