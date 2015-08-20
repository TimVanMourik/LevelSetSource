#ifndef LEVELSET_HPP
#define LEVELSET_HPP

//----------------------------------------------------------------------------------------------------------------------
/// @file LevelSet.hpp
/// @author Tim van Mourik
/// @date 5 February 2014
/// @brief
//----------------------------------------------------------------------------------------------------------------------

#include <string>

#include "Matrix44.hpp"
#include "SignedDistanceFieldFactory.hpp"

template<typename T>
class SignedDistanceField
{
public:
     /// @brief
    SignedDistanceField(
            const unsigned int& _x = 0,
            const unsigned int& _y = 0,
            const unsigned int& _z = 0,
            const std::string& _inputObjFile = "",
            const Matrix44& _matrix = Matrix44()
            );
    /// @brief
    bool setObj(
            const std::string& _inputObjFile
            );
    /// @brief
    bool computeSdfVolume(
            );
    /// @brief
    bool computeGradients(
            );
    /// @brief
    bool computeCurvature(
            );
    /// @brief
    bool loadSdfFromFile(
            const std::string& _inputFile = ""
            );
    /// @brief
    bool loadGradientFromFile(
            const std::string& _inputFile = ""
            );
    /// @brief
    bool loadCurvatureFromFile(
            const std::string& _inputFile = ""
            );
    /// @brief
    bool saveSDF(
            const std::string& _outputFile = "",
            const Matrix44& _matrix = Matrix44()
            );
    /// @brief
//    bool saveAbsGradient(
//            const std::string& _outputFile = ""
//            );
    /// @brief
    bool saveCurvature1(
            const std::string& _outputFile = ""
            );
    /// @brief
    bool saveCurvature2(
            const std::string& _outputFile = ""
            );
    /// @brief
    ~SignedDistanceField(
            );
private:
    /// @brief
    void sampleSDF(
            const unsigned int _x,
            const unsigned int _y,
            const unsigned int _z,
            arma::vec& o_kernel
            );
    /// @brief
//    bool absGradient(
//            );
    /// @brief
    unsigned int m_sizeX;
    /// @brief
    unsigned int m_sizeY;
    /// @brief
    unsigned int m_sizeZ;
    /// @brief
    std::string m_objFile;
    /// @brief
    Matrix44 m_matrix;
    /// @brief
    SignedDistanceFieldFactory<T>* m_factory;
    /// @brief
    Volume<T>* m_sdf;
    /// @brief
//    Volume<T>* m_absGradient;
    /// @brief
    Volume<T>* m_curvature1;
    /// @brief
    Volume<T>* m_curvature2;
};

#endif // LEVELSET_HPP
