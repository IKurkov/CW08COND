/* Kurkov Ivan, 22.B06-MM, 02.09.2024 */
#include <iostream>
#include <iomanip>

#include "vector.hpp"
#include "matrix.hpp"

int main( void )
{
  Matrix<double> m(3, 4);

  m[2][3] = 1;
  std::cout << m[2][3];
  return 0;
}