#ifndef VOLUME4D_HPP
#define VOLUME4D_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file Volume4D.hpp
/// @author Tim van Mourik
/// @date 5 February 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <string>

#include <armadillo>

#include "Matrix44.hpp"
#include "Volume.hpp"

template <typename T>
class Volume4D
{
public:
    /// @brief
    Volume4D(
            );
    /// @brief
    Volume4D(
            const std::string& _fileName = ""
            );
    /// @brief
//    bool saveAsNifti(
//            const std::string& _fileName = "",
//            const Matrix44& _matrix = Matrix44()
//            );
    /// @brief
    Volume4D<T> sqrt(
            );
    /// @brief
    void loadFromFile(
            const std::string& _fileName
            );
    /// @brief
    void loadFromFile(
            );
    /// @brief
    const Volume<T>& volumeAt(
            unsigned int _i
            );
    /// @brief
    unsigned int getNumberOfVolumes(
            );
    /// @brief
    unsigned int getSizeX(
            );
    /// @brief
    unsigned int getSizeY(
            );
    /// @brief
    unsigned int getSizeZ(
            );
    /// @brief
    ~Volume4D(
            );
private:
    /// @brief
    std::string m_fileName;
    /// @brief
    bool m_loaded;
    /// @brief
    std::vector<Volume<T> > m_volumes;
    /// @brief
    unsigned int m_sizeX;
    /// @brief
    unsigned int m_sizeY;
    /// @brief
    unsigned int m_sizeZ;
    /// @brief
    unsigned int m_numberOfVolumes;
    /// @brief
    int getDataType(
            );
};


#endif // VOLUME4D_HPP
