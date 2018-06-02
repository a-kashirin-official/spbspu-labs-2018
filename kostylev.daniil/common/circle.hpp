#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace kostylev
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t & mid, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(const double dx, const double dy) override;
    void scale(const double coef) override;

  private:
    point_t mid_;
    double radius_;
  };
}

#endif // CIRCLE_HPP