# Programming C Summative Projects

This repository contains 5 C/Bash programming projects demonstrating various concepts.

## Project 2: System Health Monitor

**Language:** Bash  
**monitor.sh** - Real-time system monitoring (CPU/Memory/Disk usage, processes). Menu-driven with alerts (>80% default), logging to health.log, continuous mode.  
**Run:** `bash monitor.sh`

## Project 3: Course Performance Analyzer

**Language:** C  
**analyzer.exe** - Student record management (CRUD, search/sort by GPA/name/ID), GPA calc, reports (top 5, class/course stats). Persists to academic_records.dat.  
**Build:** `make`  
**Run:** `./analyzer`

## Project 4: Data Analysis Toolkit

**Language:** C  
**toolkit.exe** - Dataset operations (add/load/filter/transform/sort/search, sum/avg/min/max). File I/O (dataset.dat), dynamic dispatch.  
**Build:** `make`  
**Run:** `./toolkit.exe`

## Project 5: Multi-threaded Web Scraper

**Language:** C (libcurl, pthreads)  
**mt_scraper** - Parallel URL fetching to output_N.html. Docker support. From urls.txt.  
**Build:** `make` (needs libcurl)  
**Run:** `./mt_scraper urls.txt [outdir]`  
**Docker:** `docker build -t scraper .; docker run ...`

## Build Notes

- Windows: Use MinGW/MSYS2 or WSL for C projects.
- Linux/macOS: Standard gcc + libs.

Clean, modular projects showcasing data structures, file I/O, multithreading, systems programming.
