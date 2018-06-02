#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace revtova
{
  class Rectangle:
  public Shape
  {
  public:
    Rectangle(const point_t & pos, const double width, const double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(double kscale) override;
    void move(const point_t & pos) override;
    void move(double dx, double dy) override;
  private:
    point_t pos_;
    double width_;
    double height_;
  };
}

#endif // RECTANGLE_HPP_INCLUDED
