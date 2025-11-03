#ifndef ARRAY_H
#define ARRAY_H

#define ARRAY_INITIAL_CAPACITY 16

typedef enum {
  ARRAY_OK,
  ARRAY_ALLOCATION_ERROR,
  ARRAY_INDEX_OUT_OF_BOUNDS,
  ARRAY_DIMENSION_MISMATCH,
} ArrayError;

typedef struct {
  int size;
  int capacity;
  float *data;
} Array;

ArrayError array_init(Array *array);
ArrayError array_free(Array *array);
ArrayError array_item(Array *array, int index, float *item);
ArrayError array_push(Array *array, float item);

typedef struct {
  int columns;
  int rows;
  int capacity;
  float *data;
} Array2D;

ArrayError array2d_init(Array2D *array, int num_columns);
ArrayError array2d_free(Array2D *array);
ArrayError array2d_item(Array2D *array, int row, int column, float *item);
ArrayError array2d_push_row(Array2D *array, Array *row);

#endif
