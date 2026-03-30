#ifndef FILE_IO_H
#define FILE_IO_H

#include "dataset.h"

// Prototypes
bool dataset_load(Dataset *ds, const char *filename);
bool dataset_save(const Dataset *ds, const char *filename);
bool save_results(const char *filename, const char *message, const double *data, int size);

#endif
