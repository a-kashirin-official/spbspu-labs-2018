#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace petrov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual petrov::rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const petrov::point_t & dot) noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void scale(const double factor) = 0;
    virtual void rotate(const double angle) noexcept = 0;
  };
}

#endif
