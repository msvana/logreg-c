#include "lib/dataset.h"
#include "lib/error.h"
#include "lib/logreg.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  Error error;

  char *path = argv[1];
  printf("Loading dataset from %s\n", path);

  Dataset dataset;
  error = dataset_load_iris(&dataset, path);
  PRINT_AND_RETURN_IF_ERROR(error);

  printf("Shuffling dataset\n");
  error = dataset_shuffle(&dataset);
  PRINT_AND_RETURN_IF_ERROR(error);

  printf("Splitting dataset\n");
  Dataset train, test;
  error = dataset_split(&dataset, 0.8, &train, &test);
  PRINT_AND_RETURN_IF_ERROR(error);

  printf("Printing TRAIN dataset\n");
  error = dataset_print(&train);
  PRINT_AND_RETURN_IF_ERROR(error);

  printf("Printing TEST dataset\n");
  error = dataset_print(&test);
  PRINT_AND_RETURN_IF_ERROR(error);

  printf("Training logistic regression model\n");
  LogReg logreg;
  error = logreg_train(&logreg, &train, 0.01, 10);
  PRINT_AND_RETURN_IF_ERROR(error);

  error = logreg_print(&logreg);
  PRINT_AND_RETURN_IF_ERROR(error);

  printf("Predicting\n");
  Array pred;
  array_init_static(&pred, test.labels.size, 0.0);
  float y_exp, y_pred;

  error = logreg_predict(&logreg, &test.features, &pred);
  PRINT_AND_RETURN_IF_ERROR(error);

  for (size_t i = 0; i < test.labels.size; i++) {
    error = array_item(&pred, i, &y_pred);
    PRINT_AND_RETURN_IF_ERROR(error);

    error = array_item(&test.labels, i, &y_exp);
    PRINT_AND_RETURN_IF_ERROR(error);

    printf("Pre: %f ", y_pred);
    printf("Exp: %f\n", y_exp);
  }

  array_free(&pred);
  logreg_free(&logreg);
  dataset_free(&dataset);

  return 0;
}
