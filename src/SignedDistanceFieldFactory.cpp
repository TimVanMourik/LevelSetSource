#include <fstream>
#include <iostream>
#include <sstream>

#include "Matrix44.hpp"
#include "makelevelset3.hpp"
#include "SignedDistanceFieldFactory.hpp"

std::vector<Vec3f> operator*=(
        std::vector<Vec3f>& _vertexList,
        const Matrix44& _matrix
        );

template <typename T>
Volume<T>* SignedDistanceFieldFactory<T>::createSignedDistanceField(
        const std::string& _inputObjFile,
        const unsigned int _sizeX,
        const unsigned int _sizeY,
        const unsigned int _sizeZ,
        const Matrix44& _matrix
        )
{
//    std::cerr << _matrix << "\n";
    if(_inputObjFile.size() < 5 || _inputObjFile.substr(_inputObjFile.size()-4) != std::string(".obj"))
    {
        std::cerr << "Error: Expected OBJ file with filename of the form <name>.obj.\n";
        exit(-1);
    }

    std::ifstream inputFile(_inputObjFile.c_str());

    if(!inputFile)
    {
        std::cerr << "Failed to open. Terminating.\n";
        exit(-1);
    }

    float gridSpacing = 1;

    unsigned int ignored_lines = 0;
    std::string line;
    std::vector<Vec3f> vertexList;
    std::vector<Vec3ui> faceList;
    while(!inputFile.eof())
    {
        std::getline(inputFile, line);
        if(line.substr(0, 2) == std::string("v "))
        {
            std::stringstream data(line);
            char c;
            Vec3f point;
            data >> c >> point[0] >> point[1] >> point[2];
            vertexList.push_back(point);
//            std::cerr << point[0] << " " << point[1] << " " << point[2] << "\n";
        }
        else if(line.substr(0, 2) == std::string("f "))
        {
            std::stringstream data(line);
            char c;
            unsigned int v0, v1, v2;
            data >> c >> v0 >> v1 >> v2;
            faceList.push_back(Vec3ui(v0 - 1, v1 - 1, v2 - 1));
        }
        else
        {
            ++ignored_lines;
        }
    }
    inputFile.close();

    vertexList *= (Matrix44)_matrix.t();

    if(ignored_lines > 0)
    {
//        std::cerr << "Warning: " << ignored_lines << " lines were ignored since they did not contain faces or vertices.\n";
    }

    std::cerr << "Computing signed distance field.\n";
    Array3f phiGrid;
    Vec3f origin = Vec3f(0, 0, 0);
    make_level_set3(faceList, vertexList, origin, gridSpacing, _sizeX, _sizeY, _sizeZ, phiGrid);

    Volume<T>* returnVolume = new Volume<T>(_sizeX, _sizeY, _sizeZ);

    for(unsigned int x = 0; x < _sizeX; ++x)
    {
        for(unsigned int y = 0; y < _sizeY; ++y)
        {
            for(unsigned int z = 0; z < _sizeZ; ++z)
            {
                (*returnVolume)(x, y, z) = phiGrid(x, y, z);
            }
        }
    }
    return returnVolume;
}


std::vector<Vec3f> operator*=(
        std::vector<Vec3f>& _vertexList,
        const Matrix44& _matrix
        )
{
    for (unsigned int i = 0; i < _vertexList.size(); ++i)
    {
        _vertexList[i][0] = _vertexList[i][0] * _matrix(0, 0) + _vertexList[i][1] * _matrix(1, 0) + _vertexList[i][2] * _matrix(2, 0) + _matrix(3, 0);
        _vertexList[i][1] = _vertexList[i][0] * _matrix(0, 1) + _vertexList[i][1] * _matrix(1, 1) + _vertexList[i][2] * _matrix(2, 1) + _matrix(3, 1);
        _vertexList[i][2] = _vertexList[i][0] * _matrix(0, 2) + _vertexList[i][1] * _matrix(1, 2) + _vertexList[i][2] * _matrix(2, 2) + _matrix(3, 2);
    }
    return _vertexList;
}

template class SignedDistanceFieldFactory<double>;
template class SignedDistanceFieldFactory<float>;
