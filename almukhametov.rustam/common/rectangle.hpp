#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace almukhametov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double h, double w, point_t c);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(point_t c) override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

  private:
    double height_, width_;
    point_t center_;
  };
}

#endif //RECTANGLE_HPP
