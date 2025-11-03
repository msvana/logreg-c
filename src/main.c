#include <stdio.h>
#include "lib/dataset.h"

int main(int argc, char *argv[]) {
  char *path = argv[1];
  printf("Loading dataset from %s\n", path);

  Dataset dataset;
  DatasetError error = dataset_load_iris(&dataset, path);

  if (error != DATASET_OK) {
    printf("Error loading dataset: %d\n", error);
    return 1;
  }

  dataset_print(&dataset);
  dataset_free(&dataset);

  return 0;
}
