#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace salykin
{
  class Circle:
    public Shape
  {
  public:
    Circle(const double radius, const point_t & center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPos) override;
    void move(const double dx, const double dy) override;
    point_t getPos() const override;
    void scale(const double multiplier) override;

    double getRadius() const;
  private:
    point_t center_;
    double radius_;
  };
}

#endif
