#include "../include/matrix.h"

void
matrix_clone(Matrix destination, Matrix source) {
  int length = source[0] * source[1] + 2;

  for (int index = 0; index < length; index += 1) {
    destination[index] = source[index];
  }
}

void
matrix_free(Matrix *matrix_address) {
  Matrix matrix = *matrix_address;

  if (matrix != NULL) free(matrix);

  *matrix_address = NULL;
}

Matrix
matrix_new(int rows, int columns) {
  int    length = rows * columns + 2;
  Matrix result = malloc(sizeof(float) * length);

  result[0] = rows;
  result[1] = columns;

  return result;
}

void
matrix_fill(Matrix matrix, int value) {
  int length = matrix[0] * matrix[1] + 2;

  for (int index = 2; index < length; index += 1) {
    matrix[index] = value;
  }
}

int
matrix_equal(Matrix first, Matrix second) {
  if (first[0] != second[0]) return 0;
  if (first[1] != second[1]) return 0;

  int length = first[0] * first[1] + 2;

  for (int index = 2; index < length; index += 1) {
    if (first[index] != second[index]) return 0;
  }

  return 1;
}

void
matrix_add(const Matrix first, const Matrix second, Matrix result) {
  int data_size = (int) (first[0] * first[1] + 2);

  result[0] = first[0];
  result[1] = first[1];

  for (int index = 2; index < data_size; index += 1) {
    result[index] = first[index] + second[index];
  }
}

int
matrix_argmax(const Matrix matrix) {
  int data_size = (int) (matrix[0] * matrix[1] + 2);
  int argmax    = 2;

  for (int index = 3; index < data_size; index += 1) {
    if (matrix[argmax] < matrix[index]) {
      argmax = index;
    }
  }

  return argmax - 2;
}

void
matrix_divide(const Matrix first, const Matrix second, Matrix result) {
  int data_size = (int) (first[0] * first[1] + 2);

  result[0] = first[0];
  result[1] = first[1];

  for (int index = 2; index < data_size; index += 1) {
    result[index] = first[index] / second[index];
  }
}

void
matrix_dot(const Matrix first, const Matrix second, Matrix result) {
  result[0] = first[0];
  result[1] = second[1];

  cblas_sgemm(
    CblasRowMajor,
    CblasNoTrans,
    CblasNoTrans,
    first[0],
    second[1],
    first[1],
    1.0,
    first + 2,
    first[1],
    second + 2,
    second[1],
    0.0,
    result + 2,
    result[1]
  );
}

void
matrix_dot_and_add(
  const Matrix first, const Matrix second, const Matrix third, Matrix result
) {
  int data_size = (int) (first[0] * first[1] + 2);

  result[0] = first[0];
  result[1] = second[1];

  cblas_sgemm(
    CblasRowMajor,
    CblasNoTrans,
    CblasNoTrans,
    first[0],
    second[1],
    first[1],
    1.0,
    first + 2,
    first[1],
    second + 2,
    second[1],
    0.0,
    result + 2,
    result[1]
  );

  for(int index = 2; index < data_size; index += 1) {
    result[index] += third[index];
  }
}

void
matrix_dot_nt(const Matrix first, const Matrix second, Matrix result) {
  result[0] = first[0];
  result[1] = second[0];

  cblas_sgemm(
    CblasRowMajor,
    CblasNoTrans,
    CblasTrans,
    first[0],
    second[0],
    first[1],
    1.0,
    first + 2,
    first[1],
    second + 2,
    second[1],
    0.0,
    result + 2,
    result[1]
  );
}

void
matrix_dot_tn(const Matrix first, const Matrix second, Matrix result) {
  result[0] = first[1];
  result[1] = second[1];

  cblas_sgemm(
    CblasRowMajor,
    CblasTrans,
    CblasNoTrans,
    first[1],
    second[1],
    first[0],
    1.0,
    first + 2,
    first[1],
    second + 2,
    second[1],
    0.0,
    result + 2,
    result[1]
  );
}

float
matrix_first(const Matrix matrix) {
  return matrix[2];
}

float
matrix_max(const Matrix matrix) {
  int   data_size = (int) (matrix[0] * matrix[1] + 2);
  float max       = matrix[2];

  for (int index = 3; index < data_size; index += 1) {
    if (max < matrix[index]) {
      max = matrix[index];
    }
  }

  return max;
}

void
matrix_multiply(const Matrix first, const Matrix second, Matrix result) {
  int data_size = (int) (first[0] * first[1] + 2);

  result[0] = first[0];
  result[1] = first[1];

  for (int index = 2; index < data_size; index += 1) {
    result[index] = first[index] * second[index];
  }
}

void
matrix_multiply_with_scalar(
  const Matrix matrix, const float scalar, Matrix result
) {
  int data_size = (int) (matrix[0] * matrix[1] + 2);

  result[0] = matrix[0];
  result[1] = matrix[1];

  for (int index = 2; index < data_size; index += 1) {
    result[index] = matrix[index] * scalar;
  }
}

void
matrix_substract(const Matrix first, const Matrix second, Matrix result) {
  int data_size = (int) (first[0] * first[1] + 2);

  result[0] = first[0];
  result[1] = first[1];

  for (int index = 2; index < data_size; index += 1) {
    result[index] = first[index] - second[index];
  }
}

float
matrix_sum(const Matrix matrix) {
  int   data_size = matrix[0] * matrix[1] + 2;
  float sum       = 0;

  for (int index = 2; index < data_size; index += 1) {
    sum += matrix[index];
  }

  return sum;
}

void
matrix_transpose(const Matrix matrix, Matrix result) {
  result[0] = matrix[1];
  result[1] = matrix[0];

  for (int row = 0; row < matrix[0]; row += 1) {
    for (int column = 0; column < matrix[1]; column += 1) {
      int result_index = column * result[1] + row    + 2;
      int matrix_index = row *    matrix[1] + column + 2;

      result[result_index] = matrix[matrix_index];
    }
  }
}
