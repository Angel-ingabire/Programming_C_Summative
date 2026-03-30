# Course Performance and Academic Records Analyzer

## Overview

A complete C implementation of a menu-driven academic records management system with dynamic memory allocation, file persistence, manual search/sorting, and comprehensive performance analytics.

## Features Implemented

✅ Dynamic structures with malloc/realloc/free  
✅ Complete CRUD operations (Create, Read, Update, Delete)  
✅ Manual search (ID, Name)  
✅ Manual bubble sort (GPA descending, Name/ID ascending)  
✅ Binary file handling with data persistence  
✅ Performance reports (average, min/max/median GPA, top N, course stats)  
✅ Robust input validation and error handling  
✅ Memory-safe operations

## Build & Run

```bash
make          # Build release
make run      # Build and run
make debug    # Debug build
make clean    # Clean build files
```

## Sample Usage

1. Add students with ID, name, course, age, grades
2. View/search/sort records
3. Generate reports (auto-saves to `academic_records.dat`)
4. Data persists across runs

## File Structure

```
project3/
├── main.c          # Menu-driven UI
├── student.h/c     # Core structures & CRUD/search/sort
├── file_handler.h/c # Binary file I/O
├── reports.h/c     # Analytics & reports
├── Makefile        # Build system
└── README.md
```

## Key Algorithms

- **Dynamic Array**: realloc on growth (>capacity)
- **Search**: Linear scan O(n)
- **Sort**: Bubble sort O(n²) manual implementation
- **Reports**: Statistical calculations, temp sorting for median/top-N

System fully validates inputs, handles memory/file errors gracefully, and provides clean modular code.
