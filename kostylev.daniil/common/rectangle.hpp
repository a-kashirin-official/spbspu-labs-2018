#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace kostylev
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const point_t & centre, const double width, const double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(const double dx, const double dy) override;
    void scale(const double coef) override;
  private:
    point_t centre_;
    double width_;
    double height_;
  };
}

#endif // RECTANGLE_HPP
