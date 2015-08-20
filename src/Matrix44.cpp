#include <assert.h>
#include <iostream>

#include "nifti1_io.h"

#include "Matrix44.hpp"

Matrix44::Matrix44(
        ) :
    Matrix(arma::eye<arma::mat>(4, 4))
{
}

Matrix44::Matrix44(
        const arma::mat& _matrix
        ) :
    Matrix(_matrix)
{
}

void Matrix44::setFromNifti(
        const std::string& _fileName
        )
{
    if(!std::ifstream(_fileName.c_str()))
    {
        std::cerr << "Sorry, the file that you are trying to open seems not to exist. Please check if the path name is correct.\n";
        return;
    }
    nifti_image* inputNifti;

    //the options is passed on to 'fopen', so the option needs to be 'r' (read)
    char* options = (char*)"r";
//    std::cerr << "Opening NifTI...\n";
    nifti_image_open(_fileName.c_str(), options, &inputNifti);

    (*this)(0, 0) = inputNifti->qto_xyz.m[0][0];    (*this)(0, 1) = inputNifti->qto_xyz.m[0][1];    (*this)(0, 2) = inputNifti->qto_xyz.m[0][2];    (*this)(0, 3) = inputNifti->qto_xyz.m[0][3];
    (*this)(1, 0) = inputNifti->qto_xyz.m[1][0];    (*this)(1, 1) = inputNifti->qto_xyz.m[1][1];    (*this)(1, 2) = inputNifti->qto_xyz.m[1][2];    (*this)(1, 3) = inputNifti->qto_xyz.m[1][3];
    (*this)(2, 0) = inputNifti->qto_xyz.m[2][0];    (*this)(2, 1) = inputNifti->qto_xyz.m[2][1];    (*this)(2, 2) = inputNifti->qto_xyz.m[2][2];    (*this)(2, 3) = inputNifti->qto_xyz.m[2][3];
    (*this)(3, 0) = inputNifti->qto_xyz.m[3][0];    (*this)(3, 1) = inputNifti->qto_xyz.m[3][1];    (*this)(3, 2) = inputNifti->qto_xyz.m[3][2];    (*this)(3, 3) = inputNifti->qto_xyz.m[3][3];

//    std::cerr << (*this) << "\n";
}
