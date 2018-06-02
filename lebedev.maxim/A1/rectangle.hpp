#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle (const point_t & center, const double width, const double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & transferPoint) override;
  void move(const double dx, const double dy) override;
  void printCurrentInfo() const override;
private:
  point_t center_;
  double width_;
  double heigth_;
};

#endif
