#ifndef LOGREG_H
#define LOGREG_H

#include "array.h"
#include "dataset.h"

typedef enum {
  LOGREG_OK,
} LogRegError;

typedef struct {
  float learning_rate;
  float bias;
  Array weights;
} LogReg;

LogRegError logreg_train(LogReg *logreg, Dataset *dataset, float learning_rate);
LogRegError logreg_free(LogReg *logreg);
LogRegError logreg_predict(LogReg *logreg, Array2D *features, Array *prediction);

#endif
