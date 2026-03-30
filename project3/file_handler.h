#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "student.h"

// Function prototypes for file operations
bool save_records(const StudentList *list);
bool load_records(StudentList *list);
void initialize_file(void);

#endif // FILE_HANDLER_H
