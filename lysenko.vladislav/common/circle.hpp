#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace lysenko
{
  class Circle : public lysenko::Shape {
  public:
    Circle(const point_t &center, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &center) override;
    void move(const double dx, const double dy) override;
    void scale(const double dk) override;
  private:
    point_t center_;
    double radius_;
  };
}
#endif
