#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix
{
public:
  Matrix( void );
  /* Construct empty matrix with n rows and m columns */
  Matrix( size_t n, size_t m );

  /* Copy constructor for matrix */
  Matrix( const Matrix &src );
  /* Copy assignment constructor for matrix */
  Matrix& operator=( const Matrix &rhs );
  /* Move constructor */
  Matrix( const Matrix &&src );
  /* Move assignment constructor */
  Matrix& operator=( const Matrix &&rhs );
  /* Destructor for matrix */
  ~Matrix();

private:
  size_t nrow, ncol
  T* data;
};

#endif // !MATRIX_H