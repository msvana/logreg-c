#include "array.h"
#include <stdlib.h>
#include <string.h>

ArrayError array_init(Array *array) {
  array->size = 0;
  array->capacity = ARRAY_INITIAL_CAPACITY;
  array->data = malloc(sizeof(float) * array->capacity);

  if (array->data == NULL) {
    return ARRAY_ALLOCATION_ERROR;
  }

  return ARRAY_OK;
}

ArrayError array_free(Array *array) {
  free(array->data);
  return ARRAY_OK;
}

ArrayError array_item(Array *array, int index, float *item) {
  if (index < 0 || index >= array->size) {
    return ARRAY_INDEX_OUT_OF_BOUNDS;
  }

  *item = array->data[index];
  return ARRAY_OK;
}

ArrayError array_push(Array *array, float item) {
  if (array->size == array->capacity) {
    array->capacity += ARRAY_INITIAL_CAPACITY;
    array->data = realloc(array->data, sizeof(float) * array->capacity);

    if (array->data == NULL) {
      return ARRAY_ALLOCATION_ERROR;
    }
  }

  array->data[array->size] = item;
  array->size++;
  return ARRAY_OK;
}

ArrayError array2d_init(Array2D *array, int num_columns) {
  array->columns = num_columns;
  array->rows = 0;
  array->capacity = ARRAY_INITIAL_CAPACITY;
  array->data = malloc(sizeof(float) * array->capacity * array->columns);
  return ARRAY_OK;
}

ArrayError array2d_free(Array2D *array) {
  free(array->data);
  return ARRAY_OK;
}

ArrayError array2d_item(Array2D *array, int row, int column, float *item) {
  if (row < 0 || row >= array->rows || column < 0 || column >= array->columns) {
    return ARRAY_INDEX_OUT_OF_BOUNDS;
  }

  *item = array->data[row * array->columns + column];
  return ARRAY_OK;
}

ArrayError array2d_push_row(Array2D *array, Array *row) {
  if (row->size != array->columns) {
    return ARRAY_DIMENSION_MISMATCH;
  }

  if (array->rows == array->capacity) {
    array->capacity += ARRAY_INITIAL_CAPACITY;
    array->data =
        realloc(array->data, sizeof(float) * array->capacity * array->columns);

    if (array->data == NULL) {
      return ARRAY_ALLOCATION_ERROR;
    }
  }

  for (int i = 0; i < array->columns; i++) {
    array->data[array->rows * array->columns + i] = row->data[i];
  }

  array->rows++;
  return ARRAY_OK;
}

ArrayError array2d_push_row_raw(Array2D *array, float *data) {
  if (array->rows == array->capacity) {
    array->capacity += ARRAY_INITIAL_CAPACITY;
    array->data =
        realloc(array->data, sizeof(float) * array->capacity * array->columns);

    if (array->data == NULL) {
      return ARRAY_ALLOCATION_ERROR;
    }
  }

  memcpy(array->data + array->rows * array->columns, data, array->columns * sizeof(float));
  array->rows++;
  return ARRAY_OK;
}
