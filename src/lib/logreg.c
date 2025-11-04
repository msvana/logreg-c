#include "logreg.h"
#include "array.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Error logreg_train(LogReg *logreg, Dataset *dataset, float lr, size_t n_iter) {
  Error error;

  logreg->lr = lr;
  logreg->bias = 0.0;
  error = array_init(&logreg->weights);
  RETURN_IF_ERROR(error);

  for (size_t i = 0; i < dataset->features.columns; i++) {
    error = array_push(&logreg->weights, 0);
    RETURN_IF_ERROR(error);
  }

  Array pred;
  array_init_static(&pred, dataset->labels.size, 0.0);
  float loss, y_pred, y_exp, feature;

  for (size_t i = 0; i < n_iter; i++) {
    error = logreg_predict_soft(logreg, &dataset->features, &pred);
    RETURN_IF_ERROR(error);

    for (size_t j = 0; j < dataset->labels.size; j++) {
      y_exp = dataset->labels.data[j];
      error = array_item(&pred, j, &y_pred);
      RETURN_IF_ERROR(error);

      loss = y_exp - y_pred;
      logreg->bias += loss * lr;

      for (size_t k = 0; k < dataset->features.columns; k++) {
        error = array2d_item(&dataset->features, j, k, &feature);
        RETURN_IF_ERROR(error);
        logreg->weights.data[k] += loss * feature * lr;
      }
    }
  }

  array_free(&pred);
  return E_OK;
}

void logreg_free(LogReg *logreg) { array_free(&logreg->weights); }

Error logreg_predict_soft(LogReg *logreg, Array2D *features, Array *pred) {
  Error error;
  float dot_product, feature, weight, sigmoid;

  for (size_t i = 0; i < features->rows; i++) {
    dot_product = 0.0;

    for (size_t j = 0; j < features->columns; j++) {
      error = array2d_item(features, i, j, &feature);
      RETURN_IF_ERROR(error);

      error = array_item(&logreg->weights, j, &weight);
      RETURN_IF_ERROR(error);

      dot_product += feature * weight;
    }

    dot_product += logreg->bias;
    sigmoid = 1.0 / (1.0 + expf(-dot_product) + LOGREG_SMALL_NUMBER);
    error = array_set(pred, i, sigmoid);
    RETURN_IF_ERROR(error);
  }

  return E_OK;
}

Error logreg_predict(LogReg *logreg, Array2D *features, Array *pred) {
  Error error;
  Array pred_soft;
  float y_pred;

  error = array_init_static(&pred_soft, features->rows, 0.0);
  RETURN_IF_ERROR(error);

  error = logreg_predict_soft(logreg, features, &pred_soft);
  RETURN_IF_ERROR(error);

  for (size_t i = 0; i < pred_soft.size; i++) {
    error = array_item(&pred_soft, i, &y_pred);

    if (y_pred > 0.5) {
      error = array_set(pred, i, 1);
    } else {
      error = array_set(pred, i, 0);
    }

    RETURN_IF_ERROR(error);
  }

  array_free(&pred_soft);
  return E_OK;
}

Error logreg_print(LogReg *logreg) {
  Error error;
  float weight;

  printf("Bias: %f\n", logreg->bias);
  printf("Weights: ");

  for (int i = 0; i < logreg->weights.size; i++) {
    error = array_item(&logreg->weights, i, &weight);
    RETURN_IF_ERROR(error);
    printf("%f ", weight);
  }

  printf("\n");
  return E_OK;
}
