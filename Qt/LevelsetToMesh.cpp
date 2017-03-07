#include <iostream>

#include "Volume4D.hpp"
#include "VolumeField.hpp"
#include "MarchingCubes.hpp"
#include "ObjFactory.hpp"

#define UNUSED(_variable) (void)_variable;

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

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cerr << "Input arguments required:\n";
        std::cerr <<  argv[0] << " -i sdfFile -o objFile\n";
        return 1;
    }

    std::string sdfFile, objFile;
    for(int i = 1; i < argc; ++i)
    {
        if(std::string(argv[i]) == "-i")
        {
            sdfFile = argv[i + 1];
            std::cerr << "-i: " << sdfFile << "\n";
        }
        if(std::string(argv[i]) == "-o")
        {
            objFile = argv[i + 1];
            std::cerr << "-o: " << objFile << "\n";
        }
    }

    Volume4D<float> volumes(sdfFile);
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

            ObjFactory::exportObject(marchingCubes, fileParts.path + fileParts.name + std::to_string(i) + fileParts.ext);
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

    return 0;
}

