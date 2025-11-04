#ifndef ARRAY_H
#define ARRAY_H

#define ARRAY_INITIAL_CAPACITY 16

#include "error.h"
#include <stdlib.h>

typedef struct {
  size_t size;
  size_t capacity;
  float *data;
} Array;

Error array_init(Array *array);
Error array_init_static(Array *array, size_t size, float default_value);
void array_free(Array *array);
Error array_item(Array *array, size_t index, float *item);
Error array_set(Array *array, size_t index, float item);
Error array_push(Array *array, float item);

typedef struct {
  size_t columns;
  size_t rows;
  size_t capacity;
  float *data;
} Array2D;

Error array2d_init(Array2D *array, size_t num_columns);
void array2d_free(Array2D *array);
Error array2d_item(Array2D *array, size_t row, size_t column, float *item);
Error array2d_push_row(Array2D *array, Array *row);
Error array2d_push_row_raw(Array2D *array, float *data);
Error array2d_switch_rows(Array2D *array, size_t r1, size_t r2);

#endif
