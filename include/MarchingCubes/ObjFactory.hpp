#ifndef OBJGENERATOR_HPP
#define OBJGENERATOR_HPP

#include <string>

class MarchingCubes;

class ObjFactory
{
public:
    //---------------------------------------------------------------------------------------------------------------------
    /// @brief Exports all objects to an obj-file
    /// @param[in] _filename is the name of the output file
    static void exportObject(
            const MarchingCubes& _marchingCubes,
            const std::string& _filename
            );
    //---------------------------------------------------------------------------------------------------------------------
    /// @brief Change the indexing default
    /// @param[in] _filename is the name of the output file
    static void setOneIndexing(
            const bool _oneIndexing
             );
private:
    static bool s_oneIndexing;
};

#endif // OBJGENERATOR_HPP
