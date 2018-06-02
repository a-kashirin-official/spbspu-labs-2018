#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace solovev{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(point_t pos, double width, double height);

    rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move (point_t pos) override;
    void move (double dx, double dy) override;
    void scale (double factor) override;

  private:
    double width_, height_;
    point_t center_;
  };
}
#endif
