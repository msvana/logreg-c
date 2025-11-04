#include "array.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

Error array_init(Array *array) {
  array->size = 0;
  array->capacity = ARRAY_INITIAL_CAPACITY;
  array->data = malloc(sizeof(float) * array->capacity);

  if (array->data == NULL) {
    return E_ALLOCATION;
  }

  return E_OK;
}

void array_free(Array *array) { free(array->data); }

Error array_item(Array *array, size_t index, float *item) {
  if (index < 0 || index >= array->size) {
    return E_INDEX;
  }

  *item = array->data[index];
  return E_OK;
}

Error array_push(Array *array, float item) {
  if (array->size == array->capacity) {
    array->capacity += ARRAY_INITIAL_CAPACITY;
    array->data = realloc(array->data, sizeof(float) * array->capacity);

    if (array->data == NULL) {
      return E_ALLOCATION;
    }
  }

  array->data[array->size] = item;
  array->size++;
  return E_OK;
}

Error array2d_init(Array2D *array, size_t num_columns) {
  array->columns = num_columns;
  array->rows = 0;
  array->capacity = ARRAY_INITIAL_CAPACITY;
  array->data = malloc(sizeof(float) * array->capacity * array->columns);

  if (array->data == NULL) {
    return E_ALLOCATION;
  }

  return E_OK;
}

void array2d_free(Array2D *array) { free(array->data); }

Error array2d_item(Array2D *array, size_t row, size_t column, float *item) {
  if (row >= array->rows || column >= array->columns) {
    return E_INDEX;
  }

  *item = array->data[row * array->columns + column];
  return E_OK;
}

Error array2d_push_row(Array2D *array, Array *row) {
  if (row->size != array->columns) {
    return E_DIMENSION_MISMATCH;
  }

  if (array->rows == array->capacity) {
    array->capacity += ARRAY_INITIAL_CAPACITY;
    size_t new_size = array->capacity * array->columns * sizeof(float);
    array->data = realloc(array->data, new_size);

    if (array->data == NULL) {
      return E_ALLOCATION;
    }
  }

  for (size_t i = 0; i < array->columns; i++) {
    array->data[array->rows * array->columns + i] = row->data[i];
  }

  array->rows++;
  return E_OK;
}

Error array2d_push_row_raw(Array2D *array, float *data) {
  if (array->rows == array->capacity) {
    array->capacity += ARRAY_INITIAL_CAPACITY;
    size_t new_size = array->capacity * array->columns * sizeof(float);
    array->data = realloc(array->data, new_size);

    if (array->data == NULL) {
      return E_ALLOCATION;
    }
  }

  void *start = array->data + array->rows * array->columns;
  size_t num_bytes = array->columns * sizeof(float);
  memcpy(start, data, num_bytes);
  array->rows++;

  return E_OK;
}

Error array2d_switch_rows(Array2D *array, size_t r1, size_t r2) {
  if (r1 >= array->rows || r2 >= array->rows) {
    return E_INDEX;
  }

  float *row1 = array->data + r1 * array->columns;
  float *row2 = array->data + r2 * array->columns;
  float tmp;

  for (size_t i = 0; i < array->columns; i++) {
    tmp = row1[i];
    row1[i] = row2[i];
    row2[i] = tmp;
  }

  return E_OK;
}
