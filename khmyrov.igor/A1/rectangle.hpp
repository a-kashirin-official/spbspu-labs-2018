#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:
        public Shape
{
public:
  Rectangle(const point_t & pos, const double width, const double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & pos) override;
  void move(const double dx, const double dy) override;

private:
  double width_, height_;
};

#endif //A1_RECTANGLE_HPP
