#ifndef RECTANLGE_HPP
#define RECTANLGE_HPP

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t & pos, const double height, const double width);
  double getArea() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t & pos) override;
  rectangle_t getFrameRect() const override;
private:
  double width_;
  double height_;
  point_t pos_;
};

#endif




