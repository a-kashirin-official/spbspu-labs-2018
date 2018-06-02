#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace ivanov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & centr, double height, double width);
    rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const point_t & pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    rectangle_t rec_;
  };
}
#endif // RECTANGLE_HPP
