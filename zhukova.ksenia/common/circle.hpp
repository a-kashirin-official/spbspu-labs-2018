
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace zhukova
{
  class Circle: public Shape
  {
  public:
    Circle(const point_t & center, double radius);
    Circle(const Circle & arg);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t & point) override;
    void scale(double coefficient) override;
    void rotate(double deg) override;

  private:
    point_t center_;
    double radius_;
    double angle_;
  };
}

#endif // CIRCLE_HPP
