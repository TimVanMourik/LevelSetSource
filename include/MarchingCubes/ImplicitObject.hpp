#ifndef SIGNEDFIELDOBJECT_HPP
#define SIGNEDFIELDOBJECT_HPP

#include "BoundingBox.hpp"

class ImplicitObject
{
public:
    ///
    ImplicitObject(
            );
    ///
    virtual float functionValue(
            float _x,
            float _y,
            float _z
            ) const = 0;
    ///
    const BoundingBox& getBoundingBox(
            ) const;
protected:
    BoundingBox m_boundingBox;
};

#endif // SIGNEDFIELDOBJECT_HPP
