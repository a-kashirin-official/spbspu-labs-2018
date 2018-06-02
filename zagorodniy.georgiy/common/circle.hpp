#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace zagorodniy {
  class Circle :
    public Shape {
  public:
    Circle(const point_t &center, double rad);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newCenter) override;
    void move(double dx, double dy) override;
    void scale(double coef) override;

  private:
    point_t pos_;
    double radius_;
  };
}

#endif
