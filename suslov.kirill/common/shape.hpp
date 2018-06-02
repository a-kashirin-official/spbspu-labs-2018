#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace suslov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual suslov::rectangle_t getFrameRect() const noexcept = 0;
    virtual double getAngle() const = 0;
    virtual void move(const double dx, double dy) noexcept = 0;
    virtual void move(const suslov::point_t & newPoint) noexcept = 0;
    virtual void scale(const double coef) = 0;
    virtual void rotate(const double angle) noexcept = 0;
  };
}

#endif
