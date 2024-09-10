/* Kurkov Ivan, 22.B06-MM, 07.09.2024 */
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector
{
public:
  Vector( void ) : dim_(0), data_(nullptr) {}
  /* Construct empty vector of size n */
  explicit Vector( size_t n ) : dim_(n), data_(new T[n]) {}
  Vector( size_t n, T* data) : dim_(n), data_(data) {}

  void swap( Vector &other )
  {
    std::swap(data_, other.data_);
    std::swap(dim_, other.dim_);
  }

  /* Copy constructor for vector */
  Vector( const Vector &other ) : dim_(other.dim_), data_(new T[dim_])
  {
    memcpy(data_, other.data_, sizeof(T) * other.dim_);
  }
  /* Copy assignment constructor for vector */
  Vector & operator=( const Vector &rhs )
  {
    Vector temp(rhs);

    swap(temp);
    return *this;
  }
  /* Move constructor */
  Vector( Vector &&other ) { swap(other); }
  /* Move assignment constructor */
  Vector & operator=( Vector &&rhs )
  {
    swap(rhs);
    return *this;
  }
  /* Destructor for vector */
  ~Vector( void ) { delete[] data_; }

  size_t dim( void ) const { return dim_; }
  T const & operator[]( size_t i ) const { return data_[i]; }
  T & operator[]( size_t i ) { return data_[i]; }

  /* Calc Godels norm with p -> +inf of given vector */
  friend T NormInf( const Vector<T> &v )
  {
    return *std::max_element(v.data_, v.data_ + v.dim_);
  }

private:
  size_t dim_;
  T *data_;
};

template <typename T>
Vector<T> & operator+=( Vector<T> &lhs, const Vector<T> &rhs )
{
  if (lhs.dim() != rhs.dim())
    throw std::invalid_argument("Can't add vectors with different dimensities!");

  for (size_t i = 0; i < lhs.dim(); i++)
    lhs[i] += rhs[i];
  return lhs;
}

template <typename T>
Vector<T> operator+( const Vector<T> &lhs, const Vector<T> &rhs)
{
  Vector<T> sum = lhs;

  return sum += rhs;
}

template <typename T>
Vector<T> & operator-=( Vector<T> &lhs, const Vector<T> &rhs )
{
  if (lhs.dim() != rhs.dim())
    throw std::invalid_argument("Can't substract vectors with different dimensities!");

  for (size_t i = 0; i < lhs.dim(); i++)
    lhs[i] -= rhs[i];
  return lhs;
}

template <typename T>
Vector<T> operator-( const Vector<T> &lhs, const Vector<T> &rhs )
{
  Vector<T> diff = lhs;

  return diff -= rhs;
}

template <typename T>
Vector<T> & operator*=( Vector<T> &lhs, T rhs )
{
  for (size_t i = 0; i < lhs.dim(); i++)
    lhs[i] *= rhs;
  return lhs;
}

template <typename T>
Vector<T> operator*( T lhs, const Vector<T> &rhs )
{
  Vector<T> prod = rhs;

  return prod *= lhs;
}

template <typename T>
std::ostream & operator<<( std::ostream &out, const Vector<T> &v )
{
  out << "{";
  if (v.dim() > 0)
  {
    out << v[0];
    for (size_t i = 1; i < v.dim(); i++)
      out << ", " << v[i];
  }
  out << "}^T\n";
  return out;
}

/* Dot product of two vectors */
template <typename T>
T DotProd( const Vector<T> &lhs, const Vector<T> &rhs )
{
  T prod = 0;

  if (lhs.dim() != rhs.dim())
    throw std::invalid_argument("Can't evaluate dot product for vectors with different dimensities!");

  for (size_t i = 0; i < lhs.dim(); i++)
    prod += lhs[i] * rhs[i];
  return prod;
}

/* Calc Godels norm with p = 1 of given vector */
template <typename T>
T Norm1( const Vector<T> &v )
{
  T norm = 0;

  for (size_t i = 0; i < v.dim(); i++)
    norm += abs(v[i]);
  return norm;
}

/* Calc Godels norm with p = 2 of given vector */
template <typename T>
T Norm2( const Vector<T> &v )
{
  T norm = 0;

  for (size_t i = 0; i < v.dim(); i++)
    norm += v[i] * v[i];
  return sqrt(norm);
}

#endif // !VECTOR_HPP