#ifndef CIRCLE_H
#define CIRCLE_H
#include "base-types.hpp"
#include "shape.hpp"

namespace reznik
{
  class Circle :
    public reznik::Shape
  {
  public:
    Circle(double radius, const reznik::point_t& cir);
    void scale(double k);
    double getArea() const;
    reznik::rectangle_t getFrameRect() const;
    void move(double dx,double dy);
    void move(const reznik::point_t& center);
  private:
    double radius_;
    reznik::point_t cir_;
  };
}
#endif // Circle_H

