#include "ImplicitObject.hpp"

ImplicitObject::ImplicitObject(
            )
{
}

const BoundingBox& ImplicitObject::getBoundingBox(
        ) const
{
    return m_boundingBox;
}
