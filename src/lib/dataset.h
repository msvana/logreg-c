#ifndef DATASET_H
#define DATASET_H

#include "array.h"
#include <stdlib.h>

typedef struct {
  int num_features;
  int num_examples;
  Array2D features;
  Array labels;
} Dataset;

Error dataset_init(Dataset *dataset, size_t num_features);
Error dataset_load_iris(Dataset *dataset, const char *path);
void dataset_free(Dataset *dataset);
Error dataset_print(Dataset *dataset);
Error dataset_shuffle(Dataset *dataset);
Error dataset_split(Dataset *dataset, float train_ratio, Dataset *train, Dataset *test);

#endif
