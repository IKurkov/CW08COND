/* Kurkov Ivan, 22.B06-MM, 13.06.2024 */
#ifndef COND_H
#define COND_H

#include <cassert>
#include <stdexcept>

#include "matrix.hpp"
#include "vector.hpp"

template <typename T>
T GaussElimination( Matrix<T> A, const Vector<T> &b, Vector<T> &x )
{
  using row_t = typename Matrix<T>::Row;

  row_t *rows = new row_t[A.rows()];
  T det = 1;
  size_t n = std::min(A.rows(), A.cols());

  for (size_t i = 0; i < A.rows(); i++)
    rows[i] = A[i];
  x = b;

  /* Forward step */
  for (size_t i = 0; i < n; i++)
  {
    T mx = abs(rows[i][i]), tmp;
    size_t idx = i;

    /* Select pivot element from the column */
    for (size_t j = i + 1; j < A.rows(); j++)
      if (mx < abs(rows[j][i]))
      {
        mx = abs(rows[j][i]);
        idx = j;
      }
    if (mx == 0)
      throw std::invalid_argument("System hasn't got solutions");
    /* Swap rows */
    swap<T>(rows[i], rows[idx]);
    std::swap(x[i], x[idx]);

    tmp = rows[i][i];
    det *= tmp * (i != idx ? -1 : 1);

    for (size_t j = i + 1; j < A.cols(); j++)
      rows[i][j] /= tmp;
    x[i] /= tmp;
    for (size_t j = i + 1; j < A.rows(); j++)
    {
      tmp = rows[j][i];
      for (size_t k = i + 1; k < A.cols(); k++)
        rows[j][k] -= rows[i][k] * tmp;
      x[j] -= x[i] * tmp;
    }
  }
  /* Reverse step */
  for (size_t i = n - 1; i > 0; i--)
    for (size_t j = n - 1; j >= i; j--)
      x[i - 1] -= rows[i - 1][j] * x[j];
  return det;
}

template <typename T>
T GaussElimination( Matrix<T> A, const Matrix<T> &B, Matrix<T> &X )
{
  using row_t = typename Matrix<T>::Row;

  row_t *rows = new row_t[A.rows()];
  T det = 1;
  size_t n = std::min(A.rows(), A.cols());

  for (size_t i = 0; i < A.rows(); i++)
    rows[i] = A[i];
  X = B;

  /* Forward step */
  for (size_t i = 0; i < n; i++)
  {
    T mx = abs(rows[i][i]), tmp;
    size_t idx = i;

    /* Select pivot element from the column */
    for (size_t j = i + 1; j < A.rows(); j++)
      if (mx < abs(rows[j][i]))
      {
        mx = abs(rows[j][i]);
        idx = j;
      }
    if (mx == 0)
      throw std::invalid_argument("System hasn't got solutions");
    /* Swap rows of A */
    swap<T>(rows[i], rows[idx]);
    /* Swap rows of X */
    for (size_t j = 0; j < X.cols(); j++)
      std::swap(X[i][j], X[idx][j]);

    tmp = rows[i][i];
    det *= tmp * (i != idx ? -1 : 1);
    for (size_t j = i + 1; j < A.cols(); j++)
      rows[i][j] /= tmp;
    for (size_t j = 0; j < X.cols(); j++)
      X[i][j] /= tmp;
    for (size_t j = i + 1; j < A.rows(); j++)
    {
      tmp = rows[j][i];
      for (size_t k = i + 1; k < A.cols(); k++)
        rows[j][k] -= rows[i][k] * tmp;
      for (size_t k = 0; k < X.cols(); k++)
        X[j][k] -= X[i][k] * tmp;
    }
  }
  /* Reverse step */
  for (size_t i = n - 1; i > 0; i--)
    for (size_t j = n - 1; j >= i; j--)
      for (size_t k = 0; k < X.cols(); k++)
        X[i - 1][k] -= rows[i - 1][j] * X[j][k];
  return det;
}

template <typename T>
Matrix<T> Inverse( const Matrix<T> &A )
{
  assert(A.rows() == A.cols());

  size_t n = A.rows();
  Matrix<T> E = AlmUnitMatrix<T>(n, n), inverse(n, n);

  GaussElimination(A, E, inverse);
  return inverse;
}

template <typename T>
T Cond( const Matrix<T> &A )
{
  Matrix<T> AInv = Inverse(A);

  return Norm1(A) * Norm1(A_inv);
}

#endif // !COND_H
