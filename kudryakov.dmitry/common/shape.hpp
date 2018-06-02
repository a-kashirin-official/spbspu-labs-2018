#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include"base-types.hpp"

namespace kudryakov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &newCenterPoint) = 0;
    virtual void move(const double dx, const double dy) = 0;
    virtual void scale(const double factor) = 0;
  };
}
#endif //A1_SHAPE_HPP
