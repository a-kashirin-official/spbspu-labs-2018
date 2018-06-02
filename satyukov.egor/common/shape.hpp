#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace satyukov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual double getAngle() const noexcept = 0;
    virtual satyukov::point_t getCoordinates() const noexcept = 0;
    virtual satyukov::rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const satyukov::point_t & newPos) noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void scale(const double coefficient) = 0;
    virtual void rotate(const double angle) noexcept = 0;
  };
}

#endif
