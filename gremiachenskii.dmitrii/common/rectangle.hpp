#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace gremiachenskii
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t & center, double height, double width);
    Rectangle(const rectangle_t & rect);
    void move(const point_t & pos) override;
    void move(double dx, double dy) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(double ratio) override;

  private:
    rectangle_t rect_;
  };
}

#endif // RECTANGLE_HPP
