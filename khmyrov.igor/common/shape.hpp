#ifndef A2_SHAPE_HPP
#define A2_SHAPE_HPP
#include "base-types.hpp"

namespace khmyrov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t & pos)  = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double coeff)= 0;

  protected:
    point_t pos_;
    Shape(const point_t & pos)
    {
      pos_ = pos;
    }
  };
}

#endif //A2_SHAPE_HPP
