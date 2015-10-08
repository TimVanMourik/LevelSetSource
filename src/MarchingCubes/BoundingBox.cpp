#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(
        const Position& _p1,
        const Position& _p2
        ) :
    m_point1(_p1),
    m_point2(_p2)
{
}

BoundingBox::BoundingBox(
        const BoundingBox &_b
        )
{
    m_point1 = _b.getPoint1();
    m_point2 = _b.getPoint2();
}

void BoundingBox::setBoundingBox(
        const Position& _p1,
        const Position& _p2
        )
{
    m_point1 = _p1;
    m_point2 = _p2;
}

void BoundingBox::setBoundingBox(
        float _x1,
        float _y1,
        float _z1,
        float _x2,
        float _y2,
        float _z2
        )
{
    m_point1.m_x = _x1;
    m_point1.m_y = _y1;
    m_point1.m_z = _z1;
    m_point2.m_x = _x2;
    m_point2.m_y = _y2;
    m_point2.m_z = _z2;
}

const Position& BoundingBox::getPoint1(
        ) const
{
    return m_point1;
}

const Position& BoundingBox::getPoint2(
        ) const
{
    return m_point2;
}

float BoundingBox::getMinimumX(
        ) const
{
    return m_point1.m_x;
}

float BoundingBox::getMinimumY(
        ) const
{
    return m_point1.m_y;
}

float BoundingBox::getMinimumZ(
        ) const
{
    return m_point1.m_z;
}

float BoundingBox::getMaximumX(
        ) const
{
    return m_point2.m_x;
}

float BoundingBox::getMaximumY(
        ) const
{
    return m_point2.m_y;
}

float BoundingBox::getMaximumZ(
        ) const
{
    return m_point2.m_z;
}
