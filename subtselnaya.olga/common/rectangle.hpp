#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace subtselnaya
{
  class Rectangle : public Shape {
  public:
    Rectangle (const double width, const double height, const point_t & center);

    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t & resPoint);
    void move(const double dx, const double dy);
    void scale(const double value);

  private:
    rectangle_t rect_;
  };
}
#endif // RECTANGLE_HPP

