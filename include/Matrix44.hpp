#ifndef MATRIX44_HPP
#define MATRIX44_HPP

#include "Matrix.hpp"

class Matrix44 : public Matrix
{
public:
    /// @brief
    Matrix44 (
            );
    /// @brief
    Matrix44(
            const arma::mat& _matrix
            );
    /// @brief
    Matrix44 (
            const Matrix& _matrix
            );
    /// @brief
    void setFreeSurferMatrix(
            );
    /// @brief
    void setCustomMatrix(
            );
    /// @brief
    void setFromNifti(
            const std::string& _inputObjFile = ""
            );
};

#endif // MATRIX44_HPP
