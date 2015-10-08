#ifndef GLDATA_HPP
#define GLDATA_HPP

#include <vector>

class GLData
{
public:
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Constructor for GLData
    GLData(
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Constructor for GLData
    /// @param[_in] _vertices are the input vertices for the data
    GLData(
        const std::vector<float> & _vertices
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief A method used to clear data
    void clear(
        );
    //---------------------------------------------------------------------------------------------------------------
    /// @brief the vertices of an object
    std::vector<float> m_vertices;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief the indices of an object
    std::vector<unsigned int> m_indices;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief the normals of an object
    std::vector<float> m_normals;
    //---------------------------------------------------------------------------------------------------------------
    /// @brief Destructor for GLData
    ~GLData(
            );
};

#endif // GLDATA_HPP
