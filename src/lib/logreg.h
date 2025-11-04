#ifndef LOGREG_H
#define LOGREG_H

#include "array.h"
#include "dataset.h"
#include "error.h"
#include <stdlib.h>

#define LOGREG_SMALL_NUMBER 1e-8

typedef struct {
  float lr;
  float bias;
  Array weights;
} LogReg;

Error logreg_train(LogReg *logreg, Dataset *dataset, float lr, size_t n_iter);
void logreg_free(LogReg *logreg);
Error logreg_predict_soft(LogReg *logreg, Array2D *features, Array *pred);
Error logreg_predict(LogReg *logreg, Array2D *features, Array *pred);
Error logreg_print(LogReg *logreg);
Error logreg_accuracy(LogReg *logreg, Dataset *dataset, float *accuracy);

#endif
