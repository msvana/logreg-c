#include "logreg.h"
#include "array.h"

LogRegError logreg_train(LogReg *logreg, Dataset *dataset, float learning_rate) {
  logreg->learning_rate = learning_rate;
  logreg->bias = 0;
  array_init(&logreg->weights);

  for (int i = 0; i < dataset->features.columns; i++) {
    array_push(&logreg->weights, 0);
  }

  Array prediction;
  array_init(&prediction);
  

  return LOGREG_OK;
}

LogRegError logreg_free(LogReg *logreg) {
  array_free(&logreg->weights);
  return LOGREG_OK;
}

LogRegError logreg_predict(LogReg *logreg, Array2D *features, Array *prediction) {
  for (int i = 0; i < features->rows; i++) {
}}

