#ifndef DATASET_H
#define DATASET_H

#include "array.h"

typedef enum {
  DATASET_OK,
  DATASET_ALLOCATION_ERROR,
  DATASET_FILE_ERROR,
} DatasetError;

typedef struct {
  int num_features;
  int num_examples;
  Array2D features;
  Array labels;
} Dataset;

DatasetError dataset_init(Dataset *dataset, int num_features);
DatasetError dataset_load_iris(Dataset *dataset, const char *path);
DatasetError dataset_free(Dataset *dataset);
DatasetError dataset_print(Dataset *dataset);

#endif
