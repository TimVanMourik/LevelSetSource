#include <assert.h>
#include <string>

#include "CurvatureKernel.hpp"
#include "SignedDistanceField.hpp"
#include "SignedDistanceFieldFactory.hpp"

static const CurvatureKernel s_curvatureKernel;

template<typename T>
SignedDistanceField<T>::SignedDistanceField(
        const unsigned int& _x,
        const unsigned int& _y,
        const unsigned int& _z,
        const std::string& _inputObjFile,
        const Matrix44& _matrix
        ) :
    m_sizeX(_x),
    m_sizeY(_y),
    m_sizeZ(_z),
    m_objFile(_inputObjFile),
    m_matrix(_matrix),
    m_factory(new SignedDistanceFieldFactory<T>),
    m_sdf(0),
//    m_absGradient(0),
    m_curvature1(0),
    m_curvature2(0)
{
}

template<typename T>
bool SignedDistanceField<T>::setObj(
        const std::string& _inputObjFileName
        )
{
    m_objFile = _inputObjFileName;
    return true;
}

template<typename T>
bool SignedDistanceField<T>::saveSDF(
        const std::string& _outputFile,
        const Matrix44& _matrix
        )
{
    if(_outputFile.empty() || !m_sdf)
    {
        return false;
    }
    if(m_sdf->saveAsNifti(_outputFile, _matrix))
    {
        return true;
    }
    else
    {
        return false;
    }
}


template<typename T>
bool SignedDistanceField<T>::computeCurvature(
        )
{
    delete m_curvature1;
    delete m_curvature2;

    arma::vec sdfKernel(26);
    arma::vec paraboloidCoefficients(9);
    m_curvature1 = new Volume<T>(m_sizeX, m_sizeY, m_sizeZ);
    m_curvature2 = new Volume<T>(m_sizeX, m_sizeY, m_sizeZ);
    for(unsigned int x = 1; x < m_sizeX - 1; ++x)
    {
        for(unsigned int y = 1; y < m_sizeY - 1; ++y)
        {
            for(unsigned int z = 1; z < m_sizeZ - 1; ++z)
            {
                sampleSDF(x, y, z, sdfKernel);
//                    std::cerr << sdfKernel;

                //N. J. Wildberger, Differential Geometry Lecture 28: Curvature for the general paraboloid
                //http://www.youtube.com/watch?v=PTh_wI6xjIQ,
                //See 44:36 for the formulas

//                    paraboloidCoefficients = solve(s_curvatureKernel, sdfKernel);
                solve(paraboloidCoefficients, s_curvatureKernel, sdfKernel);
//                    std::cerr << paraboloidCoefficients;
                double lSquared = paraboloidCoefficients(6) * paraboloidCoefficients(6);
                double mSquared = paraboloidCoefficients(7) * paraboloidCoefficients(7);
                double nSquared = paraboloidCoefficients(8) * paraboloidCoefficients(8);
                (*m_curvature1)(x, y, z) =
                        (( paraboloidCoefficients(0) + paraboloidCoefficients(1)) * lSquared
                        + (paraboloidCoefficients(0) + paraboloidCoefficients(2)) * mSquared
                        + (paraboloidCoefficients(1) + paraboloidCoefficients(2)) * nSquared)
                        / (lSquared + mSquared + nSquared);
                (*m_curvature2)(x, y, z) =
                          paraboloidCoefficients(0) * paraboloidCoefficients(1) * lSquared
                        + paraboloidCoefficients(0) * paraboloidCoefficients(2) * mSquared
                        + paraboloidCoefficients(1) * paraboloidCoefficients(2) * nSquared;
            }
        }
    }

    return true;
}

template<typename T>
void SignedDistanceField<T>::sampleSDF(
        const unsigned int _x,
        const unsigned int _y,
        const unsigned int _z,
        arma::vec& o_kernel
        )
{
//    for(unsigned int i = 0; i < 26; ++i)
//    {
        o_kernel(0)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y - 1,_z - 1);
        o_kernel(1)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y - 1,_z);
        o_kernel(2)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y - 1,_z + 1);
        o_kernel(3)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y,_z - 1);
        o_kernel(4)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y,_z);
        o_kernel(5)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y,_z + 1);
        o_kernel(6)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y + 1,_z - 1);
        o_kernel(7)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y + 1,_z);
        o_kernel(8)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x - 1, _y + 1,_z + 1);
        o_kernel(9)  = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y - 1,_z - 1);
        o_kernel(10) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y - 1,_z);
        o_kernel(11) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y - 1,_z + 1);
        o_kernel(12) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y,_z - 1);
        o_kernel(13) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y,_z + 1);
        o_kernel(14) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y + 1,_z - 1);
        o_kernel(15) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y + 1,_z);
        o_kernel(16) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x, _y + 1,_z + 1);
        o_kernel(17) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y - 1,_z - 1);
        o_kernel(18) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y - 1,_z);
        o_kernel(19) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y - 1,_z + 1);
        o_kernel(20) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y,_z - 1);
        o_kernel(21) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y,_z);
        o_kernel(22) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y,_z + 1);
        o_kernel(23) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y + 1,_z - 1);
        o_kernel(24) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y + 1,_z);
        o_kernel(25) = (*m_sdf)(_x, _y,_z) - (*m_sdf)(_x + 1, _y + 1,_z + 1);
//    }
//    arma::vec weighting(26);
//    for(unsigned int i = 0; i < 26; ++i)
//    {
//        // standard deviation = 1;
//        weighting(0)  = std::exp(- weighting(0)  * weighting(0));
//        weighting(1)  = std::exp(- weighting(1)  * weighting(1));
//        weighting(2)  = std::exp(- weighting(2)  * weighting(2));
//        weighting(3)  = std::exp(- weighting(3)  * weighting(3));
//        weighting(4)  = std::exp(- weighting(4)  * weighting(4));
//        weighting(5)  = std::exp(- weighting(5)  * weighting(5));
//        weighting(6)  = std::exp(- weighting(6)  * weighting(6));
//        weighting(7)  = std::exp(- weighting(7)  * weighting(7));
//        weighting(8)  = std::exp(- weighting(8)  * weighting(8));
//        weighting(9)  = std::exp(- weighting(9)  * weighting(9));
//        weighting(10) = std::exp(- weighting(10) * weighting(10));
//        weighting(11) = std::exp(- weighting(11) * weighting(11));
//        weighting(12) = std::exp(- weighting(12) * weighting(12));
//        weighting(13) = std::exp(- weighting(13) * weighting(13));
//        weighting(14) = std::exp(- weighting(14) * weighting(14));
//        weighting(15) = std::exp(- weighting(15) * weighting(15));
//        weighting(16) = std::exp(- weighting(16) * weighting(16));
//        weighting(17) = std::exp(- weighting(17) * weighting(17));
//        weighting(18) = std::exp(- weighting(18) * weighting(18));
//        weighting(19) = std::exp(- weighting(19) * weighting(19));
//        weighting(20) = std::exp(- weighting(20) * weighting(20));
//        weighting(21) = std::exp(- weighting(21) * weighting(21));
//        weighting(22) = std::exp(- weighting(22) * weighting(22));
//        weighting(23) = std::exp(- weighting(23) * weighting(23));
//        weighting(24) = std::exp(- weighting(24) * weighting(24));
//        weighting(25) = std::exp(- weighting(25) * weighting(25));
//    }

}

//template<typename T>
//bool SignedDistanceField<T>::saveAbsGradient(
//        const std::string& _outputFile
//        )
//{
//    if(_outputFile.empty() || !m_absGradient)
//    {
//        return false;
//    }
//    if(m_absGradient->saveAsNifti(_outputFile))
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}

template<typename T>
bool SignedDistanceField<T>::saveCurvature1(
        const std::string& _outputFile
        )
{
    if(_outputFile.empty() || !m_curvature1)
    {
        return false;
    }
    if(m_curvature1->saveAsNifti(_outputFile))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
bool SignedDistanceField<T>::saveCurvature2(
        const std::string& _outputFile
        )
{
    if(_outputFile.empty() || !m_curvature2)
    {
        return false;
    }
    if(m_curvature2->saveAsNifti(_outputFile))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
bool SignedDistanceField<T>::computeSdfVolume(
        )
{
    assert(!m_objFile.empty());
    //No if(m_dx) necessary, deleting a null object is harmless
    delete m_sdf;
    m_sdf = m_factory->createSignedDistanceField(m_objFile, m_sizeX, m_sizeY, m_sizeZ, m_matrix);
    return true;
}


template<typename T>
SignedDistanceField<T>::~SignedDistanceField(
        )
{
    if(m_factory) delete m_factory;
    if(m_sdf) delete m_sdf;
//    if(m_absGradient) delete m_absGradient;
}

template class SignedDistanceField<double>;
template class SignedDistanceField<float>;
