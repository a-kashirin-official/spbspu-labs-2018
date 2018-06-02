#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

namespace pristup
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const rectangle_t & rect);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & p) noexcept override;
    void scale(double k) override;
      
  private:
    rectangle_t rect_;
  };
}

#endif

