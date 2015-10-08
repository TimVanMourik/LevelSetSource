#include <iostream>
#include <fstream>

#include "MarchingCubes/MarchingCubes.hpp"
#include "MarchingCubes/GLData.hpp"
#include "MarchingCubes/ObjFactory.hpp"

void ObjFactory::exportObject(
        const MarchingCubes& _marchingCubes,
        const std::string& _fileName
        )
{
    // Check file name
    std::ofstream myfile;
    const std::string extension = ".obj";

    std::string fileName = _fileName;
    if (fileName.find(extension)!=std::string::npos)
    {
        std::size_t pos = fileName.find_last_of(extension);
        if (pos!=fileName.size()-1)
        {
            fileName += extension;
        }
    }
    else
    {
        fileName += extension;
    }

    // Open file
    myfile.open(fileName.c_str());
    if (myfile.is_open())
    {
        std::cerr << "Saving file...\n";
        myfile << "# Tim van Mourik, Marching Cubes algorithm\n";
        const std::vector<float>& vertices = _marchingCubes.getGLData().m_vertices;

        for(unsigned int i = 0; i < vertices.size(); i += 3)
        {
            myfile << "v " << vertices[i] << " "<< vertices[i + 1] << " "<< vertices[i + 2] << "\n";
        }
        myfile << "\n";

        ///@todo make vertex normals optional
//            const GLData& glData = _marchingCubes[i]->getGLData();
//            int vsize = glData.m_vertices.size();
//            for(int i=0; i<vsize; i+=3)
//            {
//                myfile << "vn " << glData.m_normals[i]<< " " << glData.m_normals[i+1]<< " " << glData.m_normals[i+2] << std::endl;
//            }
//        myfile << "\n\n";

        const std::vector<unsigned int>& indices = _marchingCubes.getGLData().m_indices;
        int isize = indices.size();
        for(int i = 0; i < isize; i += 3)
        {
            int x = (int)indices[i];
            int y = (int)indices[i + 1];
            int z = (int)indices[i + 2];
            x++; y++; z++;
            myfile << "f " << x << " "  << y << " "  << z << "\n";
        }
        myfile.close();
    }
}
