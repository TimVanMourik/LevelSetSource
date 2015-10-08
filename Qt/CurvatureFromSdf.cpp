#include <iostream>

#include "../include/SignedDistanceField.hpp"
#include "../include/Matrix44.hpp"

#define UNUSED(_variable) (void)_variable;


int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cerr << "Input arguments required:\n";
        std::cerr << argv[0] << " -i sdfFile -k1 primaryCurvatureFile -k2 secondaryCurvatureFile\n";
        return 1;
    }

    std::string sdfFile, curvature1File, curvature2File;
    for(int i = 1; i < argc; ++i)
    {
        if(std::string(argv[i]) == "-i")
        {
            sdfFile = argv[i + 1];
            std::cerr << "-i: " << argv[i + 1] << "\n";
        }
        if(std::string(argv[i]) == "-k1")
        {
            curvature1File = argv[i + 1];
            std::cerr << "-k1: " << argv[i + 1] << "\n";
        }
        if(std::string(argv[i]) == "-k2")
        {
            curvature2File = argv[i + 1];
            std::cerr << "-k2: " << argv[i + 1] << "\n";
        }
    }


    Matrix44 matrix1;
//    matrix1.setCustomMatrix();
    SignedDistanceField<float> phi(x, y, z, objFile, matrix1);
//    SignedDistanceField<float> phi(x, y, z, objFile);

    Matrix44 matrix2;
//    matrix2.setFromNifti(matrixFile);

    phi.computeSdfVolume();
    phi.saveSDF(sdfFile, matrix2);


    std::cerr << "Computing curvature...\n";
    phi.computeCurvature();

    std::cerr << "Saving curvature...\n";
    phi.saveCurvature1(curvature1File);
    phi.saveCurvature2(curvature2File);

    std::cerr << "Done \n";

    return 0;
}

