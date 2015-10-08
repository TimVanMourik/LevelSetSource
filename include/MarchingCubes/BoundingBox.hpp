#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <Position.hpp>

class BoundingBox
{
public:
    BoundingBox(
            );
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Constructor for a BoundingBox
    /// @param[in] _p1 is the top front right point of the bounding box
    /// @param[in] _p2 the bottom back left point of the bounding box
    //-------------------------------------------------------------------------------------------------------------
    BoundingBox(
            const Position& _p1,
            const Position& _p2
            );
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor
    /// @param[in] _b a BoundingBox
    BoundingBox(
            const BoundingBox& _boundingBox
            );
    //-------------------------------------------------------------------------------------------------------------
    /// @brief method that set the values of the Bounding Box
    /// @param[in] _x1 the x coordinate of the first bottom, back, left point of the Bounding Box
    /// @param[in] _y1 the y coordinate of the first bottom, back, left point of the Bounding Box
    /// @param[in] _z1 the z coordinate of the first bop, front, right ottom, back, left point of the Bounding Box
    /// @param[in] _x2 the x coordinate of the first top, front, right point of the Bounding Box
    /// @param[in] _y2 the y coordinate of the first top, front, right point of the Bounding Box
    /// @param[in] _z2 the z coordinate of the first top, front, right point of the Bounding Box
    //-------------------------------------------------------------------------------------------------------------
    void setBoundingBox(
            float _x1,
            float _y1,
            float _z1,
            float _x2,
            float _y2,
            float _z2
            );
    //-------------------------------------------------------------------------------------------------------------
    /// @brief method that set the values of the Bounding Box
    /// @param[in] _p1 the bottom, back, left of the bounding box
    /// @param[in] _p2 the top, front, right point of the bounding box
    //-------------------------------------------------------------------------------------------------------------
    void setBoundingBox(
            const Position& _p1,
            const Position& _p2
            );
    //-------------------------------------------------------------------------------------------------------------
    /// @brief method that returns m_point1
    //-------------------------------------------------------------------------------------------------------------
    const Position& getPoint1(
            ) const;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief method that returns m_point2
    //-------------------------------------------------------------------------------------------------------------
    const Position& getPoint2(
            ) const;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Returns the minimum x-value
    //-------------------------------------------------------------------------------------------------------------
    float getMinimumX(
            ) const;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Returns the minimum y-value
    //-------------------------------------------------------------------------------------------------------------
    float getMinimumY(
            ) const;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Returns the minimum z-value
    //-------------------------------------------------------------------------------------------------------------
    float getMinimumZ(
            ) const;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Returns the maximum x-value
    //-------------------------------------------------------------------------------------------------------------
    float getMaximumX(
            ) const;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Returns the maximum y-value
    //-------------------------------------------------------------------------------------------------------------
    float getMaximumY(
            ) const;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief Returns the maximum z-value
    //-------------------------------------------------------------------------------------------------------------
    float getMaximumZ(
            ) const;
private:
    //-------------------------------------------------------------------------------------------------------------
    /// @brief m_point1 is the bottom, back, left point of the bounding box
    //-------------------------------------------------------------------------------------------------------------
    Position m_point1;
    //-------------------------------------------------------------------------------------------------------------
    /// @brief m_point2 is the top, front, right point of the bounding box
    //-------------------------------------------------------------------------------------------------------------
    Position m_point2;
};

#endif // BOUNDINGBOX_HPP
