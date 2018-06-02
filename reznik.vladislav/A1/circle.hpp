#ifndef CIRCLE_H
#define CIRCLE_H
#include "base-types.hpp"
#include "shape.hpp"
class Circle : public Shape
{
public:
  Circle(double radius, const point_t& cir);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(double dx,double dy);
  void move(const point_t& center);
private:
  double radius_;
  point_t cir_;
};

#endif // Circle_H
