#ifndef SIGNEDDISTANCEFIELDFACTORY_HPP
#define SIGNEDDISTANCEFIELDFACTORY_HPP

#include <string>

#include "Matrix44.hpp"
#include "Volume.hpp"

template <typename T>
class SignedDistanceFieldFactory
{
public:
    Volume<T>* createSignedDistanceField(
            const std::string& _inputObjFile,
            const unsigned int _sizeX,
            const unsigned int _sizeY,
            const unsigned int _sizeZ,
            const Matrix44& _matrix = Matrix44()
            );
};

#endif // SIGNEDDISTANCEFIELDFACTORY_HPP
