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
  Matrix<double> a(3, 3), a_inv;

  RandomFill(a);
  std::cout << "A = " << a << '\n';
  a_inv = Inverse(a);
  std::cout << "A^{-1} = " << a_inv << '\n'
    << "A * A^{-1} = " << a * a_inv << '\n'
    << "cond(A) = " << Norm1(a) * Norm1(a_inv);
  return 0;
}