#ifndef POSITION_HPP
#define POSITION_HPP

//----------------------------------------------------------------------------------------------------------------
/// @file Position.h
/// @brief A Position is a simple implementation of an x,y,z-coordinate, nothing more
/// @author Tim van Mourik
/// @version 1.0
/// @date 26/02/2012
//----------------------------------------------------------------------------------------------------------------

class Position
{
public:
    inline Position() : m_x(0), m_y(0), m_z(0) {}
    inline Position(float _x, float _y, float _z) : m_x(_x), m_y(_y), m_z(_z) {}
    inline void operator+=(const Position& _p) {m_x += _p.m_x; m_y += _p.m_y; m_z += _p.m_z;}
    inline void operator-=(const Position& _p) {m_x -= _p.m_x; m_y -= _p.m_y; m_z -= _p.m_z;}
    float m_x;
    float m_y;
    float m_z;
};

#endif // POSITION_HPP
