#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED
#include "base-types.hpp"

namespace revtova
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void scale (const double kscale) = 0;
    virtual void move(const point_t & pos ) = 0;
    virtual void move(const double dx,const double dy) = 0;
  };
}

#endif // SHAPE_HPP_INCLUDED
