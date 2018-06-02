#ifndef A2_CIRCLE_HPP
#define A2_CIRCLE_HPP

#include "shape.hpp"

namespace khmyrov
{
  class Circle:
          public Shape
  {
  private:
    double radius_;

  public:
    Circle(const point_t & pos, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double coeff) override;
  };
}

#endif //A2_CIRCLE_HPP
