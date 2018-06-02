#ifndef CIRCLE_HPP_G
#define CIRCLE_HPP_G

#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t &pos, const double radius);
  void move(const point_t &pos);
  void move(const double dx, const double dy);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void printInfo() const;

private:
  point_t pos_;
  double radius_;
};

#endif
