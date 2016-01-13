#include <iostream>

#include "../include/SignedDistanceField.hpp"
#include "../include/Matrix44.hpp"

#define UNUSED(_variable) (void)_variable;


int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cerr << "Input arguments required:\n";
        std::cerr <<  argv[0] << " -i objFile -m matrixFile -o sdfFile -k1 primaryCurvatureFile -k2 secondaryCurvatureFile\n";
        return 1;
    }

    std::string objFile, matrixFile, sdfFile, curvature1File, curvature2File;
    for(int i = 1; i < argc; ++i)
    {
        if(std::string(argv[i]) == "-i")
        {
            objFile = argv[i + 1];
            std::cerr << "-i: " << objFile << "\n";
        }
        if(std::string(argv[i]) == "-m")
        {
            matrixFile = argv[i + 1];
            std::cerr << "-m: " << argv[i + 1] << "\n";
        }
        if(std::string(argv[i]) == "-o")
        {
            sdfFile = argv[i + 1];
            std::cerr << "-o: " << argv[i + 1] << "\n";
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

    const unsigned int x = 169, y = 180, z = 250;

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

