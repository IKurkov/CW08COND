/* Kurkov Ivan, 22.B06-MM, 02.09.2024 */
#include <iostream>
#include <iomanip>

#include "vector.hpp"

int main( void )
{
  Vector<double> a(3), b(3), c;
  
  a[0] = 1.0;
  a[1] = a[2] = 0;
  b[1] = 1;
  b[0] = b[2] = 0;
  c = a + b;
  c[2] = 2024;
  std::cout << std::setprecision(15) << Norm1(c) << ' ' << Norm2(c) << ' ' << NormInf(c);
  return 0;
}