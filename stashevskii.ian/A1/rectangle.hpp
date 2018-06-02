#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const double width, const double height, const point_t& point);
  rectangle_t getFrameRect() const override;
  double getArea() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t &point) override;
  void printf() const;
private:
  double width_;
  double height_;
  point_t pos;
};

#endif
