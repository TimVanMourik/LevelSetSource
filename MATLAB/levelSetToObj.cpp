#include "mex.h"

#include "../include/Volume4D.hpp"
#include "../include/MarchingCubes/VolumeField.hpp"
#include "../include/MarchingCubes/MarchingCubes.hpp"
#include "../include/MarchingCubes/ObjFactory.hpp"

struct FileParts
{
    std::string path;
    std::string name;
    std::string ext;
};

FileParts fileparts(
        std::string filename
        )
{
    int idx0 = filename.rfind("/");
    int idx1 = filename.rfind(".");

    FileParts fp;
    fp.path = filename.substr(0, idx0 + 1);
    fp.name = filename.substr(idx0 + 1, idx1 - idx0 - 1);
    fp.ext  = filename.substr(idx1);

    return fp;
}

void levelSetToObj(
        char* levelSetFile,
        char* objFile
        )
{
    Volume4D<float> volumes(levelSetFile);
    volumes.loadFromFile();

    if(volumes.getNumberOfVolumes() > 1)
    {
        FileParts fileParts = fileparts(objFile);
        for(unsigned int i = 0; i < volumes.getNumberOfVolumes(); ++i)
        {
            VolumeField volumeField(&volumes.volumeAt(i));
            MarchingCubes marchingCubes(&volumeField);
            marchingCubes.setNumberOfSubdivisions(volumes.getSizeX(), volumes.getSizeY(), volumes.getSizeZ());
            marchingCubes.computeGLData();

            char buff[100];
            snprintf(buff, sizeof(buff), "%02d", i);
            std::string buffAsStdStr = buff;
            ObjFactory::exportObject(marchingCubes, fileParts.path + fileParts.name + buffAsStdStr + fileParts.ext);
        }
    }
    else
    {
        VolumeField volumeField(&volumes.volumeAt(0));
        MarchingCubes marchingCubes(&volumeField);
        marchingCubes.setNumberOfSubdivisions(volumes.getSizeX(), volumes.getSizeY(), volumes.getSizeZ());
        marchingCubes.computeGLData();

        ObjFactory::exportObject(marchingCubes, objFile);
    }
    std::cerr << "Done \n";
    return;
}

void mexFunction( int nlhs, mxArray* plhs[],
                  int nrhs, const mxArray* prhs[])
{    
    /* check for proper number of arguments */
    if(nrhs != 2)
      mexErrMsgIdAndTxt( "MATLAB:levelSetToObj:invalidNumInputs",
              "Exactly 2 inputs required");
    else if(nlhs > 1) 
      mexErrMsgIdAndTxt( "MATLAB:levelSetToObj:maxlhs",
              "Too many output arguments.");

    /* input 1 must be a string */
    if ( mxIsChar(prhs[0]) != 1)
    {
      mexErrMsgIdAndTxt( "MATLAB:levelSetToObj:inputNotString",
              "Input 1 must be a string.");
    }
    /* input 2 must be a string */
    if ( mxIsChar(prhs[1]) != 1)
    {
      mexErrMsgIdAndTxt( "MATLAB:levelSetToObj:inputNotString",
              "Input 2 must be a string.");
    }

    /* input must be a row vector */
    if (mxGetM(prhs[0]) != 1)
      mexErrMsgIdAndTxt( "MATLAB:revord:inputNotVector",
              "File name must be a row vector.");
    if (mxGetM(prhs[1]) != 1)
      mexErrMsgIdAndTxt( "MATLAB:revord:inputNotVector",
              "File name must be a row vector.");

    char* levelSetFile  = mxArrayToString(prhs[0]);
    char* objFile       = mxArrayToString(prhs[1]);

    //check if obj file exist
    if(!std::ifstream(levelSetFile).good())
    {
        mxFree(objFile);
        mxFree(levelSetFile);
        mexErrMsgIdAndTxt( "MATLAB:levelSetToObj:FileDoesnotExist",
                           "The input Level Set file does not exist.");
    }
    
    /* call the C subroutine */
    levelSetToObj(levelSetFile, objFile);

    /* set C-style string output_buf to MATLAB mexFunction output*/
    mxFree(objFile);
    mxFree(levelSetFile);
    return;
}

