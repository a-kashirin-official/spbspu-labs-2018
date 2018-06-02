#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t &pos, const double r);
  rectangle_t getFrameRect() const override;
  double getArea() const override;
  void move(const point_t &pos) override;
  void move(const double Ox, const double Oy) override;
  void printInf() override;
private:
  point_t center_;
  double radius_;
};

#endif 
