#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace semakina
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t & pos) = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double coefficient) = 0;
    virtual void rotate(const double degree) = 0;
  };
}

#endif // SHAPE_HPP
