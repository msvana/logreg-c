#include "dataset.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DatasetError dataset_init(Dataset *dataset, int num_features) {
  dataset->num_features = num_features;
  dataset->num_examples = 0;
  array2d_init(&dataset->features, num_features);
  array_init(&dataset->labels);
  return DATASET_OK;
}

DatasetError dataset_load_iris(Dataset *dataset, const char *path) {
  const int NUM_FEATURES = 4;
  dataset_init(dataset, NUM_FEATURES);

  FILE *file = fopen(path, "r");

  if (file == NULL) {
    return DATASET_FILE_ERROR;
  }

  char line[1024];
  int num_examples = 0;

  char *label;

  // Skip header
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    num_examples++;

    Array feature_row;
    array_init(&feature_row);

    array_push(&feature_row, strtof(strtok(line, ","), NULL));
    array_push(&feature_row, strtof(strtok(NULL, ","), NULL));
    array_push(&feature_row, strtof(strtok(NULL, ","), NULL));
    array_push(&feature_row, strtof(strtok(NULL, ","), NULL));

    label = strtok(NULL, ",");

    if (strcmp(label, "setosa\n") == 0) {
      array_push(&dataset->labels, 0);
    } else if (strcmp(label, "versicolor\n") == 0) {
      array_push(&dataset->labels, 1);
    } else {
      array_free(&feature_row);
      continue;
    }

    array2d_push_row(&dataset->features, &feature_row);
    array_free(&feature_row);
  }

  printf("Loaded %d examples\n", num_examples);
  printf("Features: %d\n", dataset->features.columns);
  printf("Labels: %d\n", dataset->labels.size);
  printf("Rows: %d\n", dataset->features.rows);
  fclose(file);

  return DATASET_OK;
}

DatasetError dataset_free(Dataset *dataset) {
  array2d_free(&dataset->features);
  array_free(&dataset->labels);
  return DATASET_OK;
}

DatasetError dataset_print(Dataset *dataset) {
  float item;

  for (int i = 0; i < dataset->features.rows; i++) {
    for (int j = 0; j < dataset->features.columns; j++) {
      array2d_item(&dataset->features, i, j, &item);
      printf("%f ", item);
    }

    printf("| %f\n", dataset->labels.data[i]);
  }

  return DATASET_OK;
}
