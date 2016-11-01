#include "erl_nif.h"

#include "lib/matrix.c"

//-----------------------------------------------------------------------------
// Exported nifs
//-----------------------------------------------------------------------------

static ERL_NIF_TERM
add(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  data_size   = (int) (first_data[0] * first_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_add(first_data, second_data, result_data);

  return result;
}

static ERL_NIF_TERM
argmax(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  matrix;
  float        *matrix_data;
  int           argmax;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &matrix)) return enif_make_badarg(env);

  matrix_data = (float *) matrix.data;
  argmax      = matrix_argmax(matrix_data);

  return enif_make_int(env, argmax);
}

static ERL_NIF_TERM
divide(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  data_size   = (int) (first_data[0] * first_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_divide(first_data, second_data, result_data);

  return result;
}

static ERL_NIF_TERM
dot(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  data_size   = (int) (first_data[0] * second_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_dot(first_data, second_data, result_data);

  return result;
}

static ERL_NIF_TERM
dot_and_add(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second, third;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *third_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[2], &third )) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  third_data  = (float *) third.data;
  data_size   = (int) (first_data[0] * second_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_dot_and_add(first_data, second_data, third_data, result_data);

  return result;
}

static ERL_NIF_TERM
dot_nt(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  data_size   = (int) (first_data[0] * second_data[0] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_dot_nt(first_data, second_data, result_data);

  return result;
}

static ERL_NIF_TERM
dot_tn(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  data_size   = (int) (first_data[1] * second_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_dot_tn(first_data, second_data, result_data);

  return result;
}

static ERL_NIF_TERM
max(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  matrix;
  float         max;
  float        *matrix_data;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &matrix)) return enif_make_badarg(env);

  matrix_data = (float *) matrix.data;

  max = matrix_max(matrix_data);

  return enif_make_double(env, max);
}

static ERL_NIF_TERM
multiply(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  data_size   = (int) (first_data[0] * first_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_multiply(first_data, second_data, result_data);

  return result;
}

static ERL_NIF_TERM
multiply_with_scalar(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  matrix;
  ERL_NIF_TERM  result;
  double        large_scalar;
  float         scalar;
  float        *matrix_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &matrix)) return enif_make_badarg(env);
  if (enif_get_double(env, argv[1], &large_scalar) == 0) {
    long long_element;
    enif_get_int64(env, argv[1], &long_element);

    large_scalar = (double) long_element;
  }
  scalar = (float) large_scalar;

  matrix_data = (float *) matrix.data;
  data_size   = (int) (matrix_data[0] * matrix_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_multiply_with_scalar(matrix_data, scalar, result_data);

  return result;
}

static ERL_NIF_TERM
substract(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  float        *first_data, *second_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (float *) first.data;
  second_data = (float *) second.data;
  data_size   = (int) (first_data[0] * first_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_substract(first_data, second_data, result_data);

  return result;
}

static ERL_NIF_TERM
sum(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  matrix;
  float         sum;
  float        *matrix_data;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &matrix)) return enif_make_badarg(env);

  matrix_data = (float *) matrix.data;

  sum = matrix_sum(matrix_data);

  return enif_make_double(env, sum);
}

static ERL_NIF_TERM
transpose(ErlNifEnv *env, int argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  matrix;
  ERL_NIF_TERM  result;
  float        *matrix_data, *result_data;
  int           data_size;
  size_t        result_size;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &matrix)) return enif_make_badarg(env);

  matrix_data = (float *) matrix.data;
  data_size   = (int) (matrix_data[0] * matrix_data[1] + 2);

  result_size = sizeof(float) * data_size;
  result_data = (float *) enif_make_new_binary(env, result_size, &result);

  matrix_transpose(matrix_data, result_data);

  return result;
}

static ErlNifFunc nif_functions[] = {
  {"add",                  2, add,                  0},
  {"argmax",               1, argmax,               0},
  {"divide",               2, divide,               0},
  {"dot",                  2, dot,                  0},
  {"dot_and_add",          3, dot_and_add,          0},
  {"dot_nt",               2, dot_nt,               0},
  {"dot_tn",               2, dot_tn,               0},
  {"max",                  1, max,                  0},
  {"multiply",             2, multiply,             0},
  {"multiply_with_scalar", 2, multiply_with_scalar, 0},
  {"substract",            2, substract,            0},
  {"sum",                  1, sum,                  0},
  {"transpose",            1, transpose,            0}
};

ERL_NIF_INIT(Elixir.ExLearn.Matrix, nif_functions, NULL, NULL, NULL, NULL)
