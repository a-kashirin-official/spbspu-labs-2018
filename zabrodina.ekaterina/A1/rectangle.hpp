#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t &pos, const double width, const double height);
  rectangle_t getFrameRect() const override;
  double getArea() const override;
  void move(const point_t &pos) override;
  void move(const double Ox, const double Oy) override;
  void printInf() override;
private:
  point_t pos_;
  double width_;
  double height_;
};

#endif 
