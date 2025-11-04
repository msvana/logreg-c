#ifndef ERROR_H
#define ERROR_H

typedef enum {
  E_OK,
  E_ALLOCATION,
  E_FILE_READ,
  E_INDEX,
  E_DIMENSION_MISMATCH,
  E_ARGUMENT,
} Error;

#define RETURN_IF_ERROR(error)                                                 \
  if (error != E_OK) {                                                         \
    return error;                                                              \
  }

#define PRINT_AND_RETURN_IF_ERROR(error) {                                     \
  if (error != E_OK) {                                                         \
    printf("Error: %d\n", error);                                              \
    return error;                                                              \
  }                                                                            \
}
#endif
