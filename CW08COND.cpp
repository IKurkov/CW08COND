/* Kurkov Ivan, 22.B06-MM, 02.09.2024 */
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "vector.hpp"
#include "matrix.hpp"
#include "COND.hpp"

template <typename T>
void RandomFill( Matrix<T> &dest )
{
  for (size_t i = 0; i < dest.rows(); i++)
    for (size_t j = 0; j < dest.cols(); j++)
      dest[i][j] = rand();
}

int main( void )
{
  Matrix<double> a(2, 2), x(2, 2), b = AlmUnitMatrix<double>(2, 2);
  double det;

  a[0][0] = 2;
  a[1][0] = 5;
  a[0][1] = 3;
  a[1][1] = -1;
  std::cout << a << '\n';
  det = GaussElimination(a, b, x);
  std::cout << a * x << '\n' << det;
  return 0;
}