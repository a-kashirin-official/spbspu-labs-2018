#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace shapoval
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual double getAngle() const noexcept = 0;
    virtual void scale(const double k) = 0;
    virtual void rotate(const double a) noexcept = 0;
    virtual shapoval::rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const shapoval::point_t & new_centre) noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
  };
}

#endif
