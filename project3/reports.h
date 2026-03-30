#ifndef REPORTS_H
#define REPORTS_H

#include "student.h"

// Function prototypes for reports
void generate_class_report(const StudentList *list);
void top_n_students(const StudentList *list, int n);
Student *best_student_per_course(const StudentList *list, const char *course);
void course_average(const StudentList *list, const char *course);

#endif // REPORTS_H
