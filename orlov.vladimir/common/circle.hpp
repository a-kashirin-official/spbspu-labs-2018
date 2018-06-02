#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include <math.h>


namespace orlov
{
  class Circle : public Shape
  {
  public:
    Circle(const double r, const point_t & point);

    double getArea() const noexcept override;
    point_t getPos() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double koef) override;

  private:
    point_t centre_;
    double radius_;
  };
}

#endif
