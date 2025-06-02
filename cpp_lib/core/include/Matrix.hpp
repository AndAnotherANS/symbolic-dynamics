#pragma once


#if defined(MATRIX_NATIVE)


template<typename T>
class Matrix
{
protected:
    std::vector<std::vector<T>> matrix;
public:
    Matrix() = default;
    Matrix(const std::vector<std::vector<T>> &matrix);
    Matrix(std::vector<std::vector<T>> &&matrix);
    Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &matrix);
    Matrix(Matrix<T> &&matrix);

    Matrix<T>& operator=(const Matrix<T> &matrix);
    Matrix<T>& operator=(Matrix<T> &&matrix);

    Matrix<T>& operator+(const Matrix<T> &other);
    Matrix<T>& operator-(const Matrix<T> &other);
    Matrix<T>& operator*(const Matrix<T> &other);

    Matrix<T>& operator+=(const Matrix<T> &other);
    Matrix<T>& operator-=(const Matrix<T> &other);
    Matrix<T>& operator*=(const Matrix<T> &other);

    
    Matrix<T>& operator+(T scalar);
    Matrix<T>& operator-(T scalar);
    Matrix<T>& operator*(T scalar);
    Matrix<T>& operator/(T scalar);

    Matrix<T>& operator+=(T scalar);
    Matrix<T>& operator-=(T scalar);
    Matrix<T>& operator*=(T scalar);
    Matrix<T>& operator/=(T scalar);

    Matrix<T>& operator()(unsigned int i, unsigned int j);

    static Matrix<T> Zero(unsigned int rows, unsigned int cols);
    
    virtual ~Matrix() = default;
};

#elif defined(MATRIX_EIGEN)

#include <Eigen/Dense>
template<typename T>
using Matrix = typename Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template<typename T>
using RowVector = typename Eigen::Matrix<T, 1, Eigen::Dynamic>;

template<typename T>
using ColumnVector = typename Eigen::Matrix<T, Eigen::Dynamic, 1>;

template<typename T>
using Array = typename Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic>;

inline std::tuple<ColumnVector<double>, double> perron_frobenius_eigen(Matrix<double> const &m)
{
    auto solver = Eigen::EigenSolver<Matrix<double>>();
    solver.compute(m);
    auto eigenvalues = solver.eigenvalues().real();
    auto eigenvectors = solver.eigenvectors().real();
    Eigen::Index max_index;
    double max_eigenval = eigenvalues.maxCoeff(&max_index);
    ColumnVector<double> max_eigenvect = eigenvectors.col(max_index);
    max_eigenvect = max_eigenvect / max_eigenvect.norm();
    return {max_eigenvect, max_eigenval};
}

#else
#error "One of MATRIX_NATIVE, MATRIX_EIGEN has to be defined"

#endif