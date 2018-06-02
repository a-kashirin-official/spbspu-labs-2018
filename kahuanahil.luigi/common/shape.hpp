#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace kahuanahil
{
  class Shape
  {
    public:
    virtual ~Shape() = default;
    virtual point_t getCenter() const noexcept = 0;
    virtual rectangle_t getFrameRect () const noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void move(const point_t &pos) noexcept = 0;
    virtual void scale(const double factor) = 0;
    virtual double getArea() const noexcept = 0;
    virtual double getAngle() const = 0;
    virtual void rotate(const double angle) noexcept = 0;
  };
}

#endif
