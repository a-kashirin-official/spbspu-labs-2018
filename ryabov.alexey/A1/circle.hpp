#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
  public:
    Circle(double radius, const point_t &pos = {0.0, 0.0});
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    point_t move(const point_t &coords) override;
    point_t move(double dx, double dy) override;

  private:
    double radius_;
    point_t center_;
};

#endif
