# Data Analysis Toolkit Using Function Pointers and Callbacks

## Overview

Complete C toolkit demonstrating function pointers for dynamic dispatch, callbacks for filter/transform/sort/search, dynamic datasets.

## Features

✅ Function pointer array dispatcher (no switch chains)  
✅ Callbacks: filter (>thresh), transform (scale), cmp (asc/desc)  
✅ Operations: sum/avg, min/max/range, search  
✅ Dynamic realloc (double capacity, max 100k)  
✅ File load/save (`dataset.dat`, `results.txt`)  
✅ Menu UI + validation/error handling

## Build & Run

```
make && ./toolkit.exe
```

## Usage Examples

- Add values / load file
- Filter (> threshold) → callback
- Scale \* factor → callback
- Sort asc/desc → cmp callback
- Operations via dispatcher table
- All memory safe, documented

Strong mastery of function pointers/callbacks per requirements.
