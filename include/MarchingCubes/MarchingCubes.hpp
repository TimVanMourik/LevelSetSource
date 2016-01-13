#ifndef MARCHINGCUBES_HPP
#define MARCHINGCUBES_HPP


#include "BoundingBox.hpp"
#include "Position.hpp"
#include "MarchingCubes/GLData.hpp"
#include "MarchingCubes/HashTable.hpp"

class ImplicitObject;

struct GridCell
{
  char cubeindex;
  Position p[8];
  double val[8];
};


class MarchingCubes
{
public:
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Constructor for a MarchingCubes instance
    /// @param[in] _object is a pointer to an SignedFieldObject
    //---------------------------------------------------------------------------------------------------------------
    MarchingCubes(
        ImplicitObject* _object
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Sets the a new SignedFieldObject
    /// @param[in] _object is a pointer to an SignedFieldObject
    //---------------------------------------------------------------------------------------------------------------
    void setObject(
        const ImplicitObject* _object
        );

    void setNumberOfSubdivisions(
            unsigned int _x,
            unsigned int _y,
            unsigned int _z
            );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Returns the GLData (vertices,normals,indices)
    //---------------------------------------------------------------------------------------------------------------
    const GLData getGLData(
            ) const;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief This polygonises an FRep object and computes all the data to visualise it using OpenGL
    //---------------------------------------------------------------------------------------------------------------
    void computeGLData(
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Polygonises a given GridCell
    /// @param[in] _cell is the gid that would be polygonised
    /// @param[in] _isolevel is the input isolevel
    //---------------------------------------------------------------------------------------------------------------
    void polygonise(
        const GridCell& _cell,
        double _isolevel
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Clears the data of the MarchingCubes
    //---------------------------------------------------------------------------------------------------------------
    void clear(
            );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Destructor for Marching Cubes
    //---------------------------------------------------------------------------------------------------------------
    ~MarchingCubes(
            );

private :
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Given a vertex this calculates its index
    //---------------------------------------------------------------------------------------------------------------
    unsigned int calculateIndex(
        const Position& _p
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Computes the vertices of an object
    //---------------------------------------------------------------------------------------------------------------
    void computeVertices(
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Subdivides the space into small GridCells.
    //---------------------------------------------------------------------------------------------------------------
    void computeSubdivisions(
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Compute the normals of an object
    //---------------------------------------------------------------------------------------------------------------
    void computeNormals(
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Compute the normals of an object using the gradient of the function
    //---------------------------------------------------------------------------------------------------------------
    void computeNormalsUsingGradient();
    //---------------------------------------------------------------------------------------------------------------
    /// @brief The SignedFieldObject that needs to be displayed
    //---------------------------------------------------------------------------------------------------------------
    const ImplicitObject* m_implicitObject;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief The BoundingBox for the object
    //---------------------------------------------------------------------------------------------------------------
    BoundingBox m_box;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief List of all x coordinates of the subdivided space
    //---------------------------------------------------------------------------------------------------------------
    std::vector<float> m_Xs;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief List of all y coordinates of the subdivided space
    //---------------------------------------------------------------------------------------------------------------
    std::vector<float> m_Ys;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief List of all coordinates of the subdivided space
    //---------------------------------------------------------------------------------------------------------------
    std::vector<float> m_Zs;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief A table where all the values returned from the SignedFieldObject are saved
    //---------------------------------------------------------------------------------------------------------------
    std::vector<float> m_valueTable;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief The GLData needed for displaying the Object
    //---------------------------------------------------------------------------------------------------------------
    GLData m_glData;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Static variable used to set the quality of an object
    //---------------------------------------------------------------------------------------------------------------
    unsigned int m_numberOfSubdivisionsX;
    unsigned int m_numberOfSubdivisionsY;
    unsigned int m_numberOfSubdivisionsZ;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief A hash table used for indexing
    //---------------------------------------------------------------------------------------------------------------
    HashTable m_hashTable;
};


#endif // MARCHINGCUBES_HPP
