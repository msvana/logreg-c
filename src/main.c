#include <stdio.h>
#include "lib/dataset.h"
#include "lib/logreg.h"

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

  printf("Training logistic regression model\n");
  LogReg logreg;
  logreg_train(&logreg, &dataset, 0.01, 100);
  logreg_print(&logreg);
  
  printf("Predicting\n");
  Array predictions;
  logreg_predict(&logreg, &dataset.features, &predictions);
  
  for (int i = 0; i < dataset.labels.size; i++) {
    float prediction;
    array_item(&predictions, i, &prediction);
    printf("Pre: %f ", prediction);
    printf("Exp: %f\n", dataset.labels.data[i]);
  }


  logreg_free(&logreg);
  dataset_free(&dataset);

  return 0;
}
