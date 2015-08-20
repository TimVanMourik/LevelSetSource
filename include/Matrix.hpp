#ifndef MATRIX_H
#define MATRIX_H

//----------------------------------------------------------------------------------------------------------------
/// @file Matrix.h
/// @brief A Matrix class for a four by four matrix
/// @author Tim van Mourik
/// @version 1.0

/// @date 28 January 2012
//----------------------------------------------------------------------------------------------------------------

#include <string>
#include <ostream>

#include <armadillo>

class Matrix : public arma::mat
{
public:
    /// @brief
    Matrix(
            );
    /// @brief
    Matrix(
            const arma::mat& _matrix
            );
    /// @brief
    /// @warning Note that 'x' is the first dimension, which is usually represented as the vertical dimension.
    /// @warning Not as the horizontal dimension, which is usually the case in mathematics.
    Matrix(
            unsigned int _x,
            unsigned int _y
            );
    /// @brief
    ~Matrix(
            );
};


#endif // MATRIX_H
