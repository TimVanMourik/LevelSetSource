#include "mex.h"

#include "../include/SignedDistanceField.hpp"
#include "../include/Matrix44.hpp"

void makeSignedDistanceField(
        char* objFile, 
        char* sdfFile,
        unsigned int x, 
        unsigned int y,
        unsigned int z,
        const Matrix44& _writeVolumeMatrix,
        const Matrix44& _objectTransformationMatrix
        )
{
    std::cout << "\n";
    SignedDistanceField<float> phi(x, y, z, objFile, _objectTransformationMatrix);
    std::cout << "Creating Signed Distance Field\n";
    phi.computeSdfVolume();

    phi.saveSDF(sdfFile, _writeVolumeMatrix);
    return;
}

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{    
    
    /* check for proper number of arguments */
    if(nrhs < 4 || nrhs > 5)
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:invalidNumInputs",
              "4 or 5 inputs required");
    else if(nlhs > 1) 
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:maxlhs",
              "Too many output arguments.");

    /* input 1 must be a string */
    if ( mxIsChar(prhs[0]) != 1)
    {
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotString",
              "Input 1 must be a string.");
    }
    /* input 2 must be an integer */
    if ( mxIsChar(prhs[1]) != 1)
    {
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotInteger",
              "Input 2 must be a string.");
    }
    /* input 3 must be an integer */
    if ( mxIsNumeric(prhs[2]) != 1)
    {
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotInteger",
              "Input 3 must be the dimensions of the output volume.");
    }
    /* input 4 must be a [4 X 4] matrix */
    if ( mxIsNumeric(prhs[3]) != 1)
    {
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotInteger",
              "Input 4 must be a [4 X 4] matrix.");
    }
    if ( mxGetM(prhs[3]) != 4)
    {
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotTransformationMatrix",
              "Input 4 must be a [4 X 4] matrix.");
    }
    if ( mxGetN(prhs[3]) != 4)
    {
      mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotTransformationMatrix",
              "Input 4 must be a [4 X 4] matrix.");
    }
    /* input 5 must be a [4 X 4] matrix */
    if(nrhs == 5)
    {
        if ( mxIsNumeric(prhs[4]) != 1)
        {
            mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotInteger",
                               "Input 5 must be a [4 X 4] matrix.");
        }
        if ( mxGetM(prhs[4]) != 4)
        {
            mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotTransformationMatrix",
                               "Input 5 must be a [4 X 4] matrix.");
        }
        if ( mxGetN(prhs[4]) != 4)
        {
            mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:inputNotTransformationMatrix",
                               "Input 5 must be a [4 X 4] matrix.");
        }
    }

    /* input must be a row vector */
    if (mxGetM(prhs[0])!=1)
      mexErrMsgIdAndTxt( "MATLAB:revord:inputNotVector",
              "File name must be a row vector.");

    char *objFile, *sdfFile;
    double* matrixValues;

    //check if obj file exist
    objFile = mxArrayToString(prhs[0]);
    sdfFile = mxArrayToString(prhs[1]); 

    if(!std::ifstream(objFile).good())
    {
        mxFree(objFile);
        mxFree(sdfFile);
        mexErrMsgIdAndTxt( "MATLAB:makeSignedDistanceField:FileDoesnotExist",
                           "The input OBJ file does not exist.");
    }

    double* dimensions = mxGetPr(prhs[2]);

    Matrix44 writeVolumeMatrix;
    matrixValues = mxGetPr(prhs[3]);
    for(unsigned int x = 0; x < 4; x++)
    {
        for(unsigned int y = 0; y < 4; y++)
        {
            writeVolumeMatrix(x, y) = matrixValues[y * 4 + x];
        }
    }
    Matrix44 shiftMatrix;
    shiftMatrix(0, 3) = 1;
    shiftMatrix(1, 3) = 1;
    shiftMatrix(2, 3) = 1;
    writeVolumeMatrix.operator *=(shiftMatrix);

    Matrix44 objectTransformationMatrix;
    if(nrhs == 5)
    {
        matrixValues = mxGetPr(prhs[4]);
        for(unsigned int x = 0; x < 4; x++)
        {
            for(unsigned int y = 0; y < 4; y++)
            {
                objectTransformationMatrix(x, y) = matrixValues[y * 4 + x];
            }
        }

    }
    
    /* call the C subroutine */
    makeSignedDistanceField(objFile,
                            sdfFile,
                            (unsigned int)dimensions[0],
                            (unsigned int)dimensions[1],
                            (unsigned int)dimensions[2],
                            writeVolumeMatrix,
                            objectTransformationMatrix);

    /* set C-style string output_buf to MATLAB mexFunction output*/

    mxFree(objFile);
    mxFree(sdfFile);
    return;
}

