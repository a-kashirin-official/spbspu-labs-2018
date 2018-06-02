#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED
#include "shape.hpp"

namespace revtova
{
  class Circle:
  public Shape
  {
  public:
    Circle(const point_t & pos, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(const double kscale) override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;
  private:
    point_t pos_;
    double radius_;
  };
}

#endif // CIRCLE_HPP_INCLUDED
