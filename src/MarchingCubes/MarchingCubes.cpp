#include <assert.h>

#include "BoundingBox.hpp"
#include "MarchingCubes/MarchingCubes.hpp"
#include "MarchingCubes/MarchingCubeTables.hpp"

MarchingCubes::MarchingCubes(
        ImplicitObject* _object
        )
{
    m_implicitObject = _object;
    if(m_implicitObject)
    {
        const BoundingBox& box = m_implicitObject->getBoundingBox();
        m_numberOfSubdivisionsX = box.getMaximumX();
        m_numberOfSubdivisionsY = box.getMaximumY();
        m_numberOfSubdivisionsZ = box.getMaximumZ();
    }

    m_hashTable.initialise();
}

void MarchingCubes::setObject(
        const ImplicitObject* _object
        )
{
  m_glData.clear();
  m_Xs.clear();
  m_Ys.clear();
  m_Zs.clear();
  m_implicitObject = _object;
//  computeGLData();
//  initialiseGL();
}

/// Modified from:-
/// Paul Bourke (May, 1994) Polygonise a scalar field
/// Available from: paulbourke.net/geometry/polygonise [Accessed 10 Feb 2012]
/*
   Linearly interpolate the position where an isosurface cuts
   an edge between two vertices, each with their own scalar value
*/
Position VertexInterp(
        double isolevel,
        Position p1,
        Position p2,
        double valp1,
        double valp2
        )
{
   double mu;
   Position p;
   mu = (isolevel - valp1) / (valp2 - valp1);
   p.m_x = p1.m_x + mu * (p2.m_x - p1.m_x);
   p.m_y = p1.m_y + mu * (p2.m_y - p1.m_y);
   p.m_z = p1.m_z + mu * (p2.m_z - p1.m_z);
   return(p);
}

void MarchingCubes::polygonise(
        const GridCell& grid,
        double isolevel
        )
{
  unsigned short int cubeindex = 0;
  unsigned int indiceslist[12];
   /*
      Determine the index into the edge table which
      tells us which vertices are inside of the surface
   */
  if (m_valueTable[grid.val[0]] < isolevel) cubeindex |= 1;
  if (m_valueTable[grid.val[1]] < isolevel) cubeindex |= 2;
  if (m_valueTable[grid.val[2]] < isolevel) cubeindex |= 4;
  if (m_valueTable[grid.val[3]] < isolevel) cubeindex |= 8;
  if (m_valueTable[grid.val[4]] < isolevel) cubeindex |= 16;
  if (m_valueTable[grid.val[5]] < isolevel) cubeindex |= 32;
  if (m_valueTable[grid.val[6]] < isolevel) cubeindex |= 64;
  if (m_valueTable[grid.val[7]] < isolevel) cubeindex |= 128;

  /* Cube is entirely in/out of the surface */
  if (edgeTable[cubeindex] == 0)
    return;

  /* Find the vertices where the surface intersects the cube */
  if (edgeTable[cubeindex] & 1)
    indiceslist[0] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[0],grid.p[1],m_valueTable[grid.val[0]],m_valueTable[grid.val[1]]));
  if (edgeTable[cubeindex] & 2)
    indiceslist[1] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[1],grid.p[2],m_valueTable[grid.val[1]],m_valueTable[grid.val[2]]));
  if (edgeTable[cubeindex] & 4)
    indiceslist[2] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[2],grid.p[3],m_valueTable[grid.val[2]],m_valueTable[grid.val[3]]));
  if (edgeTable[cubeindex] & 8)
    indiceslist[3] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[3],grid.p[0],m_valueTable[grid.val[3]],m_valueTable[grid.val[0]]));
  if (edgeTable[cubeindex] & 16)
    indiceslist[4] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[4],grid.p[5],m_valueTable[grid.val[4]],m_valueTable[grid.val[5]]));
  if (edgeTable[cubeindex] & 32)
    indiceslist[5] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[5],grid.p[6],m_valueTable[grid.val[5]],m_valueTable[grid.val[6]]));
  if (edgeTable[cubeindex] & 64)
    indiceslist[6] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[6],grid.p[7],m_valueTable[grid.val[6]],m_valueTable[grid.val[7]]));
  if (edgeTable[cubeindex] & 128)
    indiceslist[7] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[7],grid.p[4],m_valueTable[grid.val[7]],m_valueTable[grid.val[4]]));
  if (edgeTable[cubeindex] & 256)
    indiceslist[8] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[0],grid.p[4],m_valueTable[grid.val[0]],m_valueTable[grid.val[4]]));
  if (edgeTable[cubeindex] & 512)
    indiceslist[9] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[1],grid.p[5],m_valueTable[grid.val[1]],m_valueTable[grid.val[5]]));
  if (edgeTable[cubeindex] & 1024)
    indiceslist[10] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[2],grid.p[6],m_valueTable[grid.val[2]],m_valueTable[grid.val[6]]));
  if (edgeTable[cubeindex] & 2048)
    indiceslist[11] = m_hashTable.getIndex(
          VertexInterp(isolevel,grid.p[3],grid.p[7],m_valueTable[grid.val[3]],m_valueTable[grid.val[7]]));
   /* Create the triangle */


  for (int i=0;triTable[cubeindex][i]!=-1;i+=3)
  {
    m_glData.m_indices.push_back(indiceslist[triTable[cubeindex][i]]);
    m_glData.m_indices.push_back(indiceslist[triTable[cubeindex][i+1]]);
    m_glData.m_indices.push_back(indiceslist[triTable[cubeindex][i+2]]);
  }
}

/// end of citation

void MarchingCubes::computeSubdivisions(
        )
{
    if(!m_implicitObject)
    {
        ///@todo write appropriate error message
        return;
    }
    const BoundingBox& box = m_implicitObject->getBoundingBox();

    m_Xs.resize(m_numberOfSubdivisionsX + 1);
    m_Ys.resize(m_numberOfSubdivisionsY + 1);
    m_Zs.resize(m_numberOfSubdivisionsZ + 1);
    m_Xs[0] = box.getMinimumX();
    m_Ys[0] = box.getMinimumY();
    m_Zs[0] = box.getMinimumZ();
    m_Xs[m_numberOfSubdivisionsX] = box.getMaximumX();
    m_Ys[m_numberOfSubdivisionsY] = box.getMaximumY();
    m_Zs[m_numberOfSubdivisionsZ] = box.getMaximumZ();
    float stepX = (m_Xs[m_numberOfSubdivisionsX] - m_Xs[0]) / (float) m_numberOfSubdivisionsX;
    float stepY = (m_Ys[m_numberOfSubdivisionsY] - m_Ys[0]) / (float) m_numberOfSubdivisionsY;
    float stepZ = (m_Zs[m_numberOfSubdivisionsZ] - m_Zs[0]) / (float) m_numberOfSubdivisionsZ;
    for(unsigned int i = 1; i <= m_numberOfSubdivisionsX; i++)
    {
        m_Xs[i] = m_Xs[i - 1] + stepX;
    }
    for(unsigned int i = 1; i <= m_numberOfSubdivisionsY; i++)
    {
        m_Ys[i] = m_Ys[i - 1] + stepY;
    }
    for(unsigned int i = 1; i <= m_numberOfSubdivisionsZ; i++)
    {
        m_Zs[i] = m_Zs[i - 1] + stepZ;
    }
}

void MarchingCubes::setNumberOfSubdivisions(
        unsigned int _x,
        unsigned int _y,
        unsigned int _z
        )
{
    m_numberOfSubdivisionsX = _x;
    m_numberOfSubdivisionsY = _y;
    m_numberOfSubdivisionsZ = _z;
}

void MarchingCubes::computeVertices(
        )
{
    int iTemp;
//    int len = m_numberOfSubdivisions + 1;
    unsigned int numberOfPositionsInRow    =  m_numberOfSubdivisionsX;
    unsigned int numberOfPositionsInSlice  = m_numberOfSubdivisionsX * m_numberOfSubdivisionsY;
    unsigned int numberOfPositionsInVolume = (m_numberOfSubdivisionsX + 1) * (m_numberOfSubdivisionsY + 1) * (m_numberOfSubdivisionsZ + 1);
//    std::vector<bool> outSideVolume(numberOfVoxelsInVolume);
    m_valueTable.resize(numberOfPositionsInVolume);
    for (unsigned int z = 0; z <= m_numberOfSubdivisionsZ; z++)
    {
        for (unsigned int y = 0; y <= m_numberOfSubdivisionsY; y++)
        {
            for(unsigned int x = 0; x <= m_numberOfSubdivisionsX; x++)
            {
                ///@todo if something goes wrong, this should be the first place to look.
                iTemp = x + m_numberOfSubdivisionsX * y + m_numberOfSubdivisionsX * m_numberOfSubdivisionsY * z;
                m_valueTable[iTemp] = m_implicitObject->functionValue(m_Xs[x], m_Ys[y] ,m_Zs[z]);
            }
        }
    }
    GridCell cube;
    for (unsigned int z = 0; z < m_numberOfSubdivisionsZ; z++)
    {
        for (unsigned int y = 0; y < m_numberOfSubdivisionsY; y++)
        {
            for(unsigned int x = 0; x < m_numberOfSubdivisionsX; x++)
            {
                cube.val[0] = x + numberOfPositionsInRow * y + numberOfPositionsInSlice * z;;
                cube.val[1] = cube.val[0]+1;
                cube.val[2] = (x+1) + (y)   * numberOfPositionsInRow + (z + 1) * numberOfPositionsInSlice;
                cube.val[3] = (x)   + (y)   * numberOfPositionsInRow + (z + 1) * numberOfPositionsInSlice;
                cube.val[4] = (x)   + (y+1) * numberOfPositionsInRow + (z)     * numberOfPositionsInSlice;
                cube.val[5] = (x+1) + (y+1) * numberOfPositionsInRow + (z)     * numberOfPositionsInSlice;
                cube.val[6] = (x+1) + (y+1) * numberOfPositionsInRow + (z + 1) * numberOfPositionsInSlice;
                cube.val[7] = (x)   + (y+1) * numberOfPositionsInRow + (z + 1) * numberOfPositionsInSlice;
                cube.p[0]   = Position(m_Xs[x],  m_Ys[y],  m_Zs[z]);
                cube.p[1]   = Position(m_Xs[x+1],m_Ys[y],  m_Zs[z]);
                cube.p[2]   = Position(m_Xs[x+1],m_Ys[y],  m_Zs[z+1]);
                cube.p[3]   = Position(m_Xs[x],  m_Ys[y],  m_Zs[z+1]);
                cube.p[4]   = Position(m_Xs[x],  m_Ys[y+1],m_Zs[z]);
                cube.p[5]   = Position(m_Xs[x+1],m_Ys[y+1],m_Zs[z]);
                cube.p[6]   = Position(m_Xs[x+1],m_Ys[y+1],m_Zs[z+1]);
                cube.p[7]   = Position(m_Xs[x],  m_Ys[y+1],m_Zs[z+1]);
//                cube.p[0][0] = m_Xs[x];   cube.p[0][1] = m_Ys[y];   cube.p[0][2] = m_Zs[z];
//                cube.p[1][0] = m_Xs[x+1]; cube.p[1][1] = m_Ys[y];   cube.p[1][2] = m_Zs[z];
//                cube.p[2][0] = m_Xs[x+1]; cube.p[2][1] = m_Ys[y];   cube.p[2][2] = m_Zs[z+1];
//                cube.p[3][0] = m_Xs[x];   cube.p[3][1] = m_Ys[y];   cube.p[3][2] = m_Zs[z+1];
//                cube.p[4][0] = m_Xs[x];   cube.p[4][1] = m_Ys[y+1]; cube.p[4][2] = m_Zs[z];
//                cube.p[5][0] = m_Xs[x+1]; cube.p[5][1] = m_Ys[y+1]; cube.p[5][2] = m_Zs[z];
//                cube.p[6][0] = m_Xs[x+1]; cube.p[6][1] = m_Ys[y+1]; cube.p[6][2] = m_Zs[z+1];
//                cube.p[7][0] = m_Xs[x];   cube.p[7][1] = m_Ys[y+1]; cube.p[7][2] = m_Zs[z+1];
                polygonise(cube, 0);
            }
        }
    }
}

void MarchingCubes::computeNormalsUsingGradient(
        )
{
  int vsize = m_glData.m_vertices.size();
  const std::vector<float>& vertices = m_glData.m_vertices;
  float gx, gy, gz;
  float offset = 0.0001;
  for(int i=0;i<vsize;i+=3)
  {
    gx = (m_implicitObject->functionValue(vertices[i]+offset,vertices[i+1],vertices[i+2]) -
          m_implicitObject->functionValue(vertices[i]-offset,vertices[i+1],vertices[i+2])) / (2*offset);
    gy = (m_implicitObject->functionValue(vertices[i],vertices[i+1]+offset,vertices[i+2]) -
          m_implicitObject->functionValue(vertices[i],vertices[i+1]-offset,vertices[i+2])) / (2*offset);
    gz = (m_implicitObject->functionValue(vertices[i],vertices[i+1],vertices[i+2]+offset) -
          m_implicitObject->functionValue(vertices[i],vertices[i+1],vertices[i+2]-offset)) / (2*offset);
    m_glData.m_normals.push_back(gx);
    m_glData.m_normals.push_back(gy);
    m_glData.m_normals.push_back(gz);
  }
}

void MarchingCubes::computeNormals(
        )
{
//    int vsize = m_glData.m_vertices.size()/3;
//    int numOfNormalsPerVertex[vsize];
//    PositionnormalsPerVertex[vsize][9];
//    const std::vector<float>& vertices = m_glData.m_vertices;
//    const std::vector<unsigned int>& indices = m_glData.m_indices;
//    unsigned int size = m_glData.m_indices.size();
//    for (int i =0; i<vsize; ++i)
//    {
//        numOfNormalsPerVertex[i]=0;
//    }
//    // calculate normals
//    Positionnormal;
//    Position A;
//    Position B;
//    Position C;
//    for (unsigned int i=0;i<size;i+=3) // size
//    {
//        int index = indices[i] * 3;
//        A[0] = vertices[index]; A[1] = vertices[index + 1]; A[2] = vertices[index + 2];
//        index = indices[i + 1] * 3;
//        B[0] = vertices[index]; B[1] = vertices[index + 1]; B[2] = vertices[index + 2];
//        index = indices[i + 2] * 3;
//        C[0] = vertices[index]; C[1] = vertices[index + 1]; C[2] = vertices[index + 2];
//        //    const Position& AB = B - A;
//        //    const Position& AC = C - A;
//        //    normal.cross(AB, AC);
//        normal = arma::cross(B - A, C - A);
//        if (arma::norm(normal)!=0)
//        {
//            // normal.normalize();
//            normalsPerVertex[indices[i]][numOfNormalsPerVertex[indices[i]]]=normal;
//            numOfNormalsPerVertex[indices[i]]++;
//            normalsPerVertex[indices[i+1]][numOfNormalsPerVertex[indices[i+1]]]=normal;
//            numOfNormalsPerVertex[indices[i+1]]++;
//            normalsPerVertex[indices[i+2]][numOfNormalsPerVertex[indices[i+2]]]=normal;
//            numOfNormalsPerVertex[indices[i+2]]++;
//        }
//    }
//    // compute average normals
//    for(int i = 0; i < vsize; ++i)
//    {
//        int s = numOfNormalsPerVertex[i];
//        normal = Position(arma::fill::zeros);
//        for(int j=0; j<s;j++)
//        {
//            normal+= normalsPerVertex[i][j];
//        }
//        //    normal/=s;
//        //    normal.normalize();
//        m_glData.m_normals.push_back(normal[0]);
//        m_glData.m_normals.push_back(normal[1]);
//        m_glData.m_normals.push_back(normal[2]);
//    }
}

void MarchingCubes::computeGLData(
        )
{
    ///@todo for an arbitrary object, the bounding box should be loaded first
//  BoundingBox bb = m_obj->getBoundingBox();
//  float offset = 0.1;
//  Position p1(-offset,-offset,-offset);
//  Position p2(offset,offset,offset);
//  p1 += bb.getPoint1();
//  p2 += bb.getPoint2();
//  m_box.setBoundingBox(p1,p2);
//  glPointSize(3.0f);
  m_glData.clear();
  computeSubdivisions();
  computeVertices();
  m_glData.m_vertices = m_hashTable.getVertices();
//  computeNormalsUsingGradient();
//  computeNormals();
}


const GLData MarchingCubes::getGLData(
        ) const
{
    return m_glData;
}

void MarchingCubes::clear(
        )
{
  m_Xs.clear();
  m_Ys.clear();
  m_Zs.clear();
  m_valueTable.clear();
  m_glData.clear();
  m_hashTable.clear();
}

MarchingCubes::~MarchingCubes(
        )
{
  m_Xs.clear();
  m_Ys.clear();
  m_Zs.clear();
//  m_vao->removeVOA();
  m_valueTable.clear();
}
