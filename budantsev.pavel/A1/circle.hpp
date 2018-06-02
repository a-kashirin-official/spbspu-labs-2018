#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include "shape.hpp"

class Circle:public Shape
{
public:
  Circle(const double r,const point_t &pos);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(const point_t& poss);
  void move(const double Ox,const double Oy);
  void info() const;

private:
  double radius_;
  point_t center_;

};

#endif /* CIRCLE_HPP_ */
