#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
  public:
    Rectangle(double width, double height, const point_t &pos = { 0.0, 0.0 });
    Rectangle(const rectangle_t &frame);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    point_t move(const point_t &coords) override;
    point_t move(double dx, double dy) override;

  private:
    rectangle_t frame_;
};

#endif
