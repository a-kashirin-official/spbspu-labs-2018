#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "base-types.hpp"
#include "shape.hpp"

namespace reznik
{
  class Rectangle :
    public reznik::Shape
  {
  public:
    Rectangle(double width,double height, const reznik::point_t& rec);
    double getArea() const;
    void scale(double k);
    reznik::rectangle_t getFrameRect() const;
    void move(double dx,double dy);
    void move(const point_t& center);
  private:
    double width_;
    double height_;
    reznik::point_t rec_;
  };
}
#endif // RECTANGLE_H
