#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace rebrin
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& pos, double rad);


    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t& pos) override;

    void move(const double dx, const double dy) override;

    void scale(const double factor) override;

  private:
    point_t center_;
    double radius_;
  };
}

#endif
