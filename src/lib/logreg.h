#ifndef LOGREG_H
#define LOGREG_H

#include "array.h"
#include "dataset.h"

#define LOGREG_SMALL_NUMBER 1e-8

typedef enum {
  LOGREG_OK,
} LogRegError;

typedef struct {
  float learning_rate;
  float bias;
  Array weights;
} LogReg;

LogRegError logreg_train(LogReg *logreg, Dataset *dataset, float learning_rate,
                         unsigned int max_iterations);
LogRegError logreg_free(LogReg *logreg);
LogRegError logreg_predict(LogReg *logreg, Array2D *features,
                           Array *prediction);

void logreg_print(LogReg *logreg);

#endif
