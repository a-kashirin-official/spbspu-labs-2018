#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace ivanov
{
  class Circle : public Shape
  {
  public:
    Circle (const point_t & pos, double radius);
    rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const point_t & pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t centr_;
    double rad_;
  };
}

#endif // CIRCLE_HPP