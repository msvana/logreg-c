#include "logreg.h"
#include "array.h"
#include <math.h>
#include <stdio.h>

LogRegError logreg_train(LogReg *logreg, Dataset *dataset, float learning_rate,
                         unsigned int max_iterations) {
  logreg->learning_rate = learning_rate;
  logreg->bias = 0.0;
  array_init(&logreg->weights);

  for (int i = 0; i < dataset->features.columns; i++) {
    array_push(&logreg->weights, 0);
  }

  Array predictions;

  for (int j = 0; j < max_iterations; j++) {
    logreg_predict(logreg, &dataset->features, &predictions);
    for (int i = 0; i < dataset->labels.size; i++) {
      float label = dataset->labels.data[i];
      float prediction;
      array_item(&predictions, i, &prediction);

      float error = label - prediction;
      logreg->bias += error * learning_rate;

      for (int j = 0; j < dataset->features.columns; j++) {
        float feature =
            dataset->features.data[i * dataset->features.columns + j];
        logreg->weights.data[j] += error * feature * learning_rate;
      }
    }
  }

  return LOGREG_OK;
}

LogRegError logreg_free(LogReg *logreg) {
  array_free(&logreg->weights);
  return LOGREG_OK;
}

LogRegError logreg_predict(LogReg *logreg, Array2D *features,
                           Array *prediction) {
  array_init(prediction);

  for (int i = 0; i < features->rows; i++) {
    float dot_product = 0;

    for (int j = 0; j < features->columns; j++) {
      float feature = features->data[i * features->columns + j];
      dot_product += feature * logreg->weights.data[j];
    }

    dot_product += logreg->bias;
    float sigmoid = 1.0 / (1.0 + expf(-dot_product) + LOGREG_SMALL_NUMBER);
    array_push(prediction, sigmoid);
  }

  return LOGREG_OK;
}

void logreg_print(LogReg *logreg) {
  printf("Bias: %f\n", logreg->bias);
  printf("Weights: ");

  for (int i = 0; i < logreg->weights.size; i++) {
    printf("%f ", logreg->weights.data[i]);
  }

  printf("\n");
}
