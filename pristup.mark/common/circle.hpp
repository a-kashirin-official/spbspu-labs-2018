#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"
#include "base-types.hpp"

namespace pristup
{
  class Circle: public Shape
  {
  public:
    Circle(double r, const point_t & position);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & p) noexcept override;
    void scale(double k) override;
    
  private:
    double r_;
    point_t p_;
  };
}

#endif

