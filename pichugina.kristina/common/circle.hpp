#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace pichugina
{
  class Circle:
    public pichugina::Shape
  {
  public:
    Circle(const pichugina::point_t & centre, const double radius);
    double getArea() const override;
    pichugina::rectangle_t getFrameRect() const override;
    void move(const pichugina::point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
  private:
    pichugina::point_t centre_;
    double radius_;
  };
}

#endif
