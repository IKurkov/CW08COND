/* Kurkov Ivan, 22.B06-MM, 13.06.2024 */
#ifndef COND_H
#define COND_H

#include <iostream>
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
    T mx = abs(rows[i][i]);
    size_t idx = i;

    /* Select pivot element from the column */
    for (size_t j = 0; j < A.rows(); j++)
      if (mx < abs(rows[j][i]))
      {
        mx = abs(rows[j][i]);
        idx = j;
      }
    if (mx == 0)
      throw std::invalid_argument("System hasn't got solutions");
    det *= rows[idx][idx] * (i != idx ? -1 : 1);
    /* Swap rows */
    swap<T>(rows[i], rows[idx]);
    std::swap(x[i], x[idx]);
    for (size_t j = i + 1; j < A.cols(); j++)
      rows[i][j] /= mx;
    x[i] /= mx;
    for (size_t j = i + 1; j < A.rows(); j++)
    {
      T tmp = rows[j][i];
      for (size_t k = i + 1; k < A.cols(); k++)
        rows[j][k] -= rows[i][k] * tmp;
      x[j] -= x[i] * tmp;
    }
  }
  /* Reverse step */
  for (size_t i = n - 1; i > 0; i--)
    x[i - 1] -= rows[i - 1][i] * x[i];
  return det;
}

#endif // !COND_H
