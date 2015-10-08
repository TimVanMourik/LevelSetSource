#include "VolumeField.hpp"

VolumeField::VolumeField(
        const Volume<float>* _volume
        ) :
    ImplicitObject(),
    m_volume(_volume)
{
    setBoundingBox();
}

void VolumeField::setBoundingBox(
        )
{
    if(m_volume)
    {
        m_boundingBox.setBoundingBox(0, 0, 0, m_volume->n_rows, m_volume->n_cols, m_volume->n_slices);
    }
}

float roundToNearest(float num)
{
    return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}

float VolumeField::functionValue(
        float _x,
        float _y,
        float _z
        ) const
{
    unsigned int x = (unsigned int) round(_x);
    unsigned int y = (unsigned int) round(_y);
    unsigned int z = (unsigned int) round(_z);
    x = x > 0 ? x : 0;
    y = y > 0 ? y : 0;
    z = z > 0 ? z : 0;
    x = x < m_volume->n_rows - 1   ? x : m_volume->n_rows - 1;
    y = y < m_volume->n_cols - 1   ? y : m_volume->n_cols - 1;
    z = z < m_volume->n_slices - 1 ? z : m_volume->n_slices - 1;

    return m_volume->operator()(x, y, z);
}
