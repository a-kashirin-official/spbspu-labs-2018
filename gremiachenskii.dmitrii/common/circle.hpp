#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace gremiachenskii
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & pos, double rad);
    void move(const point_t & pos) override;
    void move(double dx, double dy) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(double ratio) override;

  private:
    point_t center_;
    double radius_;
  };
}

#endif // CIRCLE_HPP
