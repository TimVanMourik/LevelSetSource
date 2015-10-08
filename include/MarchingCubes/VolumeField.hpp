#ifndef VOLUMEFIELD_HPP
#define VOLUMEFIELD_HPP

#include "BoundingBox.hpp"
#include "ImplicitObject.hpp"
#include "Volume.hpp"

class VolumeField : public ImplicitObject
{
public:
    ///
    VolumeField(
            const Volume<float>* _volume = 0
            );
    ///
    void setBoundingBox(
            );
    ///
    float functionValue(
            float _x,
            float _y,
            float _z
            ) const;
private:
    const Volume<float>* m_volume;
};

#endif // VOLUMEFIELD_HPP
