#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace sibikin
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t & center, const double h, const double w);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    point_t getPos() const override;
    void move(const point_t & newCenter) override;
    void move(const double dx, const double dy) override;
    void scale(const double coef) override;
    void rotate(const double phi);
  private:
    double width_, height_;
    point_t pos_;
    double angle_;
  };
}

#endif
