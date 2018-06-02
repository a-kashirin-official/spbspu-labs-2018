#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace styagov
{
  class Shape
  {
  public:    
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual styagov::point_t getPos() const noexcept = 0;
    virtual styagov::rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const styagov::point_t & pos) noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void scale(const double ratio) = 0;
    virtual void rotate(const double alpha /*in degrees*/) noexcept = 0;
  };
}

#endif // SHAPE_HPP
