#include "MarchingCubes/GLData.hpp"

GLData::GLData(
        )
{
}

GLData::GLData(
        const std::vector <float>& _vertices)
{
    m_vertices = _vertices;
}

void GLData::clear(
        )
{
    m_vertices.clear();
    m_indices.clear();
    m_normals.clear();
}

GLData::~GLData(
        )
{
    m_vertices.clear();
    m_indices.clear();
    m_normals.clear();
}
