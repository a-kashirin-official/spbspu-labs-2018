#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace almukhametov
{
  class Circle : public Shape
  {
  public:
    Circle(double r, point_t c);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(point_t c) override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

  private:
    double radius_;
    point_t center_;
  };
}
#endif //CIRCLE_HPP
