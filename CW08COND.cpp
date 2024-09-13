/* Kurkov Ivan, 22.B06-MM, 02.09.2024 */
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "vector.hpp"
#include "matrix.hpp"

template <typename T>
void RandomFill( Matrix<T> &dest )
{
  for (size_t i = 0; i < dest.rows(); i++)
    for (size_t j = 0; j < dest.cols(); j++)
      dest[i][j] = rand();
}

int main( void )
{
  Matrix<int> a(3, 5), b = AlmUnitMatrix<int>(5, 2);
  Vector<int> v(5);

  v[3] = 1;
  RandomFill(a);
  std::cout << a << '\n' << a * v << '\n' << b << '\n' << a * b;
  return 0;
}