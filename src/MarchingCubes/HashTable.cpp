#include "MarchingCubes/HashTable.hpp"

const unsigned int PRIME_NUMBER = 907;

HashTable::HashTable(
        )
{
}

/// this function was sent to us by Mathieu Sanchez
/// modified from:
/// http://codesuppository.blogspot.com/2006/04/welding.html
/// Ignacio Castaño (http://www.ludicon.com/castano/blog/articles/)
/// Pierre Terdiman (http://codercorner.com/Pierre.htm)
/// Ville Miettinen (http://www.linkedin.com/in/wilihybrid)
unsigned int HashTable::vertexHashFunction(
        const Position& _vertex
        )
{
  // Read the floats as if they were ints
  const unsigned int primes[] = { 1,11,17 };
  const unsigned int removefloatsign = 0x7fffffff;
  const unsigned int* as_ints = (const unsigned int*)(&_vertex);
  const unsigned int f = ( as_ints[0]*primes[0]+as_ints[1]*primes[1]-(as_ints[2]*primes[2]) ) & removefloatsign;
  return ((f>>22)^(f>>12)^(f))%PRIME_NUMBER;
}
/// end of citation

void HashTable::initialise(
        )
{
  m_nextIndex = 0;
  m_hashTable.resize(PRIME_NUMBER);
  for (unsigned int i=0; i<PRIME_NUMBER; ++i)
  {
    m_hashTable[i].L = new std::vector<int>;
  }
}

bool exact_compare(
        const Position& _A,
        const Position& _B
        )
{
  return    _A.m_x ==_B.m_x &&
            _A.m_y ==_B.m_y &&
            _A.m_z ==_B.m_z;

}

int HashTable::getIndex(
        const Position& _vertex
        )
{
  unsigned int hPosition = vertexHashFunction(_vertex);
  int index = -1;
  std::vector<int> *p=0;
  p=m_hashTable[hPosition].L;
  for (int i=(*p).size()-1; i>=0; --i)
  {
    if (exact_compare(m_vertices[(*p)[i]], _vertex))
    {
      index =(*p)[i];
      break;
    }
  }
  if (index == -1)
  {
    m_vertices.push_back(_vertex);
    p->push_back(m_nextIndex);
    index = m_nextIndex;
    m_nextIndex++;
  }
  return index;
}

std::vector<float> HashTable::getVertices(
        )
{
  int size = m_vertices.size();
  std::vector<float> vertices;
  for (int i=0; i<size; i++ )
  {
    vertices.push_back(m_vertices[i].m_x);
    vertices.push_back(m_vertices[i].m_y);
    vertices.push_back(m_vertices[i].m_z);
  }

  return vertices;
}

HashTable::~HashTable(
        )
{
  for (int unsigned i = 0; i < PRIME_NUMBER; ++i)
  {
    m_hashTable[i].L->clear();
    delete m_hashTable[i].L;
  }
  m_vertices.clear();
}

void HashTable::clear(
        )
{
  for (unsigned int i = 0; i < PRIME_NUMBER; ++i)
  {
    m_hashTable[i].L->clear();
    delete m_hashTable[i].L;
  }
  m_vertices.clear();
}
