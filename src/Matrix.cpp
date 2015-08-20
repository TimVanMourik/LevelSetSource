#include <assert.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <typeinfo>

#include "Matrix.hpp"

Matrix::Matrix(
        ) :
    arma::mat()
{
}

Matrix::Matrix(
        const arma::mat& _matrix
        ) :
    arma::mat(_matrix)
{
}

Matrix::Matrix(
        unsigned int _x,
        unsigned int _y
        ) :
    arma::mat(_x, _y)
{
}

Matrix::~Matrix(
        )
{
}
