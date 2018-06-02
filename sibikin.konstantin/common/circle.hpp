#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace sibikin
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & center, const double r);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    point_t getPos() const override;
    void move(const point_t & newCenter) override;
    void move(const double dx, const double dy) override;
    void scale(const double coef) override;
    void rotate(const double phi) override;
  private:
    double r_;
    point_t pos_;
  };
}

#endif
