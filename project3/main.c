#include "student.h"
#include "file_handler.h"
#include "reports.h"

// Helper function to input student data
static bool input_student(Student *student)
{
    printf("\nEnter Student ID: ");
    if (scanf("%d", &student->id) != 1)
        return false;

    getchar(); // consume newline

    printf("Enter Student Name: ");
    if (fgets(student->name, MAX_NAME_LEN, stdin) == NULL ||
        student->name[strlen(student->name) - 1] == '\n')
    {
        student->name[strlen(student->name) - 1] = '\0';
    }

    printf("Enter Course Name: ");
    if (fgets(student->course, MAX_COURSE_LEN, stdin) == NULL ||
        student->course[strlen(student->course) - 1] == '\n')
    {
        student->course[strlen(student->course) - 1] = '\0';
    }

    printf("Enter Age: ");
    if (scanf("%d", &student->age) != 1)
        return false;

    printf("Enter number of subjects (1-%d): ", MAX_SUBJECTS);
    if (scanf("%d", &student->num_subjects) != 1 || student->num_subjects < 1 || student->num_subjects > MAX_SUBJECTS)
    {
        return false;
    }

    printf("Enter %d grades: ", student->num_subjects);
    for (int i = 0; i < student->num_subjects; i++)
    {
        if (scanf("%f", &student->grades[i]) != 1)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    StudentList *students = create_student_list();
    if (!students)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    initialize_file();
    load_records(students);

    int choice;
    do
    {
        printf("\n=== COURSE PERFORMANCE ANALYZER ===\n");
        printf("1.  Add Student\n");
        printf("2.  Update Student\n");
        printf("3.  Delete Student\n");
        printf("4.  Search by ID\n");
        printf("5.  Search by Name\n");
        printf("6.  Display All Students\n");
        printf("7.  Sort by GPA\n");
        printf("8.  Sort by Name\n");
        printf("9.  Sort by ID\n");
        printf("10. Class Performance Report\n");
        printf("11. Top 5 Students\n");
        printf("12. Best Student in Course\n");
        printf("13. Course Average\n");
        printf("14. Save Records\n");
        printf("15. Load Records\n");
        printf("0.  Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ; // clear input
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            Student new_student;
            if (input_student(&new_student))
            {
                if (add_student(students, &new_student))
                {
                    printf("\nStudent added successfully!\n");
                }
                else
                {
                    printf("\nFailed to add student. Check validation.\n");
                }
            }
            else
            {
                printf("\nInvalid input!\n");
            }
            break;
        }
        case 2:
        {
            int id;
            printf("Enter Student ID to update: ");
            if (scanf("%d", &id) == 1)
            {
                Student *existing = find_student_by_id(students, id);
                if (existing)
                {
                    printf("Updating student: ");
                    display_student(existing);
                    Student updated;
                    updated = *existing; // copy current
                    if (input_student(&updated))
                    {
                        if (update_student(students, id, &updated))
                        {
                            printf("\nStudent updated successfully!\n");
                        }
                        else
                        {
                            printf("\nUpdate failed. Check validation.\n");
                        }
                    }
                }
                else
                {
                    printf("\nStudent not found.\n");
                }
            }
            break;
        }
        case 3:
        {
            int id;
            printf("Enter Student ID to delete: ");
            if (scanf("%d", &id) == 1)
            {
                if (delete_student(students, id))
                {
                    printf("\nStudent deleted successfully!\n");
                }
                else
                {
                    printf("\nStudent not found.\n");
                }
            }
            break;
        }
        case 4:
        {
            int id;
            printf("Enter Student ID: ");
            if (scanf("%d", &id) == 1)
            {
                Student *found = find_student_by_id(students, id);
                if (found)
                {
                    printf("\nStudent found:\n");
                    display_student(found);
                }
                else
                {
                    printf("\nStudent not found.\n");
                }
            }
            break;
        }
        case 5:
        {
            char name[MAX_NAME_LEN];
            getchar(); // consume newline
            printf("Enter Student Name: ");
            fgets(name, MAX_NAME_LEN, stdin);
            name[strlen(name) - 1] = '\0';

            Student *found = find_student_by_name(students, name);
            if (found)
            {
                printf("\nStudent found:\n");
                display_student(found);
            }
            else
            {
                printf("\nStudent not found.\n");
            }
            break;
        }
        case 6:
            display_all_students(students);
            break;
        case 7:
            sort_students_by_gpa(students);
            printf("\nSorted by GPA (descending).\n");
            display_all_students(students);
            break;
        case 8:
            sort_students_by_name(students);
            printf("\nSorted by Name (ascending).\n");
            display_all_students(students);
            break;
        case 9:
            sort_students_by_id(students);
            printf("\nSorted by ID (ascending).\n");
            display_all_students(students);
            break;
        case 10:
            generate_class_report(students);
            break;
        case 11:
            top_n_students(students, 5);
            break;
        case 12:
        {
            char course[MAX_COURSE_LEN];
            getchar();
            printf("Enter Course Name: ");
            fgets(course, MAX_COURSE_LEN, stdin);
            course[strlen(course) - 1] = '\0';
            best_student_per_course(students, course);
            break;
        }
        case 13:
        {
            char course[MAX_COURSE_LEN];
            getchar();
            printf("Enter Course Name: ");
            fgets(course, MAX_COURSE_LEN, stdin);
            course[strlen(course) - 1] = '\0';
            course_average(students, course);
            break;
        }
        case 14:
            save_records(students);
            break;
        case 15:
            load_records(students);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("\nInvalid choice!\n");
        }

        // Clear input buffer
        while (getchar() != '\n')
            ;

    } while (choice != 0);

    save_records(students); // auto-save on exit
    free_student_list(students);
    printf("Thank you for using Course Performance Analyzer!\n");
    return 0;
}
