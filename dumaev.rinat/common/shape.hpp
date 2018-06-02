#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace dumaev
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual point_t getPos() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const point_t &point) noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void scale(const double coefficient) = 0;
    virtual void rotate(const double angle) noexcept = 0;
  };
}

#endif
