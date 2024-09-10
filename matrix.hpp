#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Matrix
{
private:
  size_t row_, col_;
  T *data_;

  class Row
  {
  public:
    Row(T *b) : begin_(b) {}
    T &operator[](size_t j) { return begin_[j]; }
    T const &operator[](size_t j) const { return begin_[j]; }
  private:
    T *begin_ = nullptr;
  };

public:
  Matrix( void ) : row_(0), col_(0), data_(nullptr) {}
  /* Construct zero matrix with n rows and m columns */
  Matrix( size_t r, size_t c ) : row_(r), col_(c), data_(new T[r * c])
  {
    memset(data_, 0, sizeof(T) * row_ * col_);
  }

  void swap( Matrix &other )
  {
    std::swap(data_, other.data_);
    std::swap(row_, other.row_);
    std::swap(col_, other.col_);
  }

  /* Copy constructor for matrix */
  Matrix( const Matrix &other ) : row_(other.row_), col_(other.col_), data_(new T[row_ * col_])
  {
    memcpy(data_, other.data_, sizeof(T) * other.row_ * other.col_);
  }
  /* Copy assignment constructor for matrix */
  Matrix & operator=( const Matrix &rhs )
  {
    Matrix temp(rhs);

    swap(temp);
    return *this;
  }
  /* Move constructor */
  Matrix( Matrix &&other ) { swap(other); }
  /* Move assignment constructor */
  Matrix & operator=( Matrix &&rhs )
  {
    swap(rhs);
    return *this;
  }
  /* Destructor for matrix */
  ~Matrix( void ) { delete[] data_; }

  /* Get number of rows in matrix */
  size_t rows( void ) const { return row_; }
  /* Get number of cols in matrix */
  size_t cols( void ) const { return col_; }
  
  Row operator[]( size_t i ) { return Row(data_ + i * col_); }
  Row const operator[]( size_t i ) const { return Row(data_ + i * col_); }
};

template <typename T>
std::ostream & operator<<( std::ostream &out, const Matrix<T> &m )
{
  for (size_t i = 0; i < m.rows(); i++)
  {
    out << "{" << m[i][0];
    for (size_t j = 1; j < m.cols(); j++)
      out << " " << m[i][j];
    out << "}\n";
  }
  return out;
}

template <typename T>
Matrix<T> & operator+=( Matrix<T> &lhs, const Matrix<T> &rhs )
{
  if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
    throw std::invalid_argument("Can't add matrices with different dimensions");
  
  for (size_t i = 0; i < lhs.rows(); i++)
    for (size_t j = 0; j < lhs.cols(); j++)
      lhs[i][j] += rhs[i][j];
  return lhs;
}

template <typename T>
Matrix<T> operator+( const Matrix<T> &lhs, const Matrix<T> &rhs )
{
  Matrix<T> sum = lhs;

  return sum += rhs;
}

#endif // !MATRIX_H