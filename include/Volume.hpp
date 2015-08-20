#ifndef VOLUME_H
#define VOLUME_H

//----------------------------------------------------------------------------------------------------------------------
/// @file Volume.hpp
/// @author Tim van Mourik
/// @date 5 February 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <string>

#include <armadillo>


#include "Matrix44.hpp"

template <typename T>
class Volume : public arma::Cube<T>
{
public:
    /// @brief
    Volume(
            const unsigned int& _x,
            const unsigned int& _y,
            const unsigned int& _z
            );
    /// @brief
    Volume(
            const std::string& _fileName = ""
            );
    /// @brief
    bool saveAsNifti(
            const std::string& _fileName = "",
            const Matrix44& _matrix = Matrix44()
            );
    /// @brief
    Volume<T> sqrt(
            );
//    /// @brief
//    friend Volume operator*(
//            const Volume& _volume1,
//            const Volume& _volume2
//            )
//    {
//        /// @todo check the sizes
//        unsigned int sizeX = _volume1.n_rows;
//        unsigned int sizeY = _volume1.n_cols;
//        unsigned int sizeZ = _volume1.n_slices;
//        Volume<T> multiplication(sizeX, sizeY, sizeZ);
//        for(unsigned int x = 0; x < sizeX; ++x)
//        {
//            for(unsigned int y = 0; y < sizeY; ++y)
//            {
//                for(unsigned int z = 0; z < sizeZ; ++z)
//                {
//                    multiplication(x, y, z) = _volume1(x, y, z) *  _volume2(x, y, z);
//                }
//            }
//        }
//        return multiplication;
//    }
//    /// @brief
//    friend Volume operator+(
//            const Volume& _volume1,
//            const Volume& _volume2
//            )
//    {
//        /// @todo check the sizes
//        unsigned int sizeX = _volume1.n_rows;
//        unsigned int sizeY = _volume1.n_cols;
//        unsigned int sizeZ = _volume1.n_slices;
//        Volume<T> addition(sizeX, sizeY, sizeZ);
//        for(unsigned int x = 0; x < sizeX; ++x)
//        {
//            for(unsigned int y = 0; y < sizeY; ++y)
//            {
//                for(unsigned int z = 0; z < sizeZ; ++z)
//                {
//                    addition(x, y, z) = _volume1(x, y, z) +  _volume2(x, y, z);
//                }
//            }
//        }
//        return addition;
//    }
//    /// @brief
//    Volume<T>& operator+=(
//            const Volume<T>& _volume2
//            );
//    /// @brief
//    Volume<T>& operator-=(
//            const Volume<T>& _volume2
//            );
//    /// @brief
//    Volume<T>& operator/=(
//            const Volume<T>& _volume2
//            );
//    /// @brief
//    friend Volume operator-(
//            const Volume& _volume1,
//            const Volume& _volume2
//            )
//    {
//        /// @todo check the sizes
//        unsigned int sizeX = _volume1.n_rows;
//        unsigned int sizeY = _volume1.n_cols;
//        unsigned int sizeZ = _volume1.n_slices;
//        Volume<T> subtraction(sizeX, sizeY, sizeZ);
//        for(unsigned int x = 0; x < sizeX; ++x)
//        {
//            for(unsigned int y = 0; y < sizeY; ++y)
//            {
//                for(unsigned int z = 0; z < sizeZ; ++z)
//                {
//                    subtraction(x, y, z) = _volume1(x, y, z) -  _volume2(x, y, z);
//                }
//            }
//        }
//        return subtraction;
//    }
//    /// @brief
//    friend Volume operator*(
//            int _scalar,
//            const Volume& _volume1
//            )
//    {
//        unsigned int sizeX = _volume1.n_rows;
//        unsigned int sizeY = _volume1.n_cols;
//        unsigned int sizeZ = _volume1.n_slices;
//        Volume<T> multiplication(sizeX, sizeY, sizeZ);
//        for(unsigned int x = 0; x < sizeX; ++x)
//        {
//            for(unsigned int y = 0; y < sizeY; ++y)
//            {
//                for(unsigned int z = 0; z < sizeZ; ++z)
//                {
//                    multiplication(x, y, z) = _scalar *  _volume1(x, y, z);
//                }
//            }
//        }
//        return multiplication;
//    }
    /// @brief
    friend Volume operator/(
            const Volume& _volume1,
            const Volume& _volume2
            )
    {
        /// @todo check the sizes
        unsigned int sizeX = _volume1.n_rows;
        unsigned int sizeY = _volume1.n_cols;
        unsigned int sizeZ = _volume1.n_slices;
        Volume<T> division(sizeX, sizeY, sizeZ);
        for(unsigned int x = 0; x < sizeX; ++x)
        {
            for(unsigned int y = 0; y < sizeY; ++y)
            {
                for(unsigned int z = 0; z < sizeZ; ++z)
                {
                    division(x, y, z) = _volume1(x, y, z) /  _volume2(x, y, z);
                }
            }
        }
        return division;
    }
    /// @brief
    ~Volume(
            );
private:
    int getDataType(
            );
};


#endif // VOLUME_H
