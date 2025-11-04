#include "dataset.h"
#include "array.h"
#include "error.h"
#include "math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Error dataset_init(Dataset *dataset, size_t num_features) {
  Error error;
  dataset->num_features = num_features;
  dataset->num_examples = 0;

  error = array2d_init(&dataset->features, num_features);
  RETURN_IF_ERROR(error);

  error = array_init(&dataset->labels);
  RETURN_IF_ERROR(error);

  return E_OK;
}

Error dataset_load_iris(Dataset *dataset, const char *path) {
  const int NUM_FEATURES = 4;
  dataset_init(dataset, NUM_FEATURES);

  FILE *file = fopen(path, "r");

  if (file == NULL) {
    return E_FILE_READ;
  }

  Error error;
  char line[64];
  float feature_row[NUM_FEATURES];
  char *label;

  // Skip header
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    feature_row[0] = strtof(strtok(line, ","), NULL);
    feature_row[1] = strtof(strtok(NULL, ","), NULL);
    feature_row[2] = strtof(strtok(NULL, ","), NULL);
    feature_row[3] = strtof(strtok(NULL, ","), NULL);

    label = strtok(NULL, ",");

    if (strcmp(label, "setosa\n") == 0) {
      error = array_push(&dataset->labels, 0);
      RETURN_IF_ERROR(error);
    } else if (strcmp(label, "versicolor\n") == 0) {
      array_push(&dataset->labels, 1);
      RETURN_IF_ERROR(error);
    } else {
      continue;
    }

    error = array2d_push_row_raw(&dataset->features, feature_row);
    RETURN_IF_ERROR(error);
  }

  fclose(file);
  return E_OK;
}

void dataset_free(Dataset *dataset) {
  array2d_free(&dataset->features);
  array_free(&dataset->labels);
}

Error dataset_print(Dataset *dataset) {
  Error error;
  float item;

  for (size_t i = 0; i < dataset->features.rows; i++) {
    for (size_t j = 0; j < dataset->features.columns; j++) {
      error = array2d_item(&dataset->features, i, j, &item);
      RETURN_IF_ERROR(error);
      printf("%f ", item);
    }

    printf("| %f\n", dataset->labels.data[i]);
  }

  printf("Features: %zu\n", dataset->features.columns);
  printf("Rows: %zu\n", dataset->features.rows);

  return E_OK;
}

Error dataset_shuffle(Dataset *dataset) {
  Error error;

  for (size_t i = dataset->features.rows - 1; i > 0; i--) {
    size_t j = rand() % (i + 1);

    error = array2d_switch_rows(&dataset->features, i, j);
    RETURN_IF_ERROR(error);

    float tmp;
    error = array_item(&dataset->labels, i, &tmp);
    RETURN_IF_ERROR(error);

    error = array_item(&dataset->labels, j, &dataset->labels.data[i]);
    RETURN_IF_ERROR(error);

    dataset->labels.data[j] = tmp;
  }

  return E_OK;
}

Error dataset_split(Dataset *dataset, float train_ratio, Dataset *train,
                    Dataset *test) {
  Error error;

  if (train_ratio < 0.0 || train_ratio > 1.0) {
    return E_ARGUMENT;
  }

  size_t num_examples = dataset->features.rows;
  size_t train_size = floorf(num_examples * train_ratio);

  error = dataset_init(train, dataset->num_features);
  RETURN_IF_ERROR(error);

  error = dataset_init(test, dataset->num_features);
  RETURN_IF_ERROR(error);

  for (size_t i = 0; i < train_size; i++) {
    error = array2d_push_row_raw(&train->features,
                                 dataset->features.data +
                                     i * dataset->features.columns);
    RETURN_IF_ERROR(error);

    error = array_push(&train->labels, dataset->labels.data[i]);
    RETURN_IF_ERROR(error);
  }

  for (size_t i = train_size; i < num_examples; i++) {
    error = array2d_push_row_raw(&test->features,
                                 dataset->features.data +
                                     i * dataset->features.columns);
    RETURN_IF_ERROR(error);

    error = array_push(&test->labels, dataset->labels.data[i]);
    RETURN_IF_ERROR(error);
  }

  return E_OK;
}
