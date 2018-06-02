#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include"shape.hpp"

class Circle : public Shape
{   
public:
  Circle(double r,point_t c);
  double getArea()const override;
  rectangle_t getFrameRect() const override; 
  void Move(double xx,double yy) override;
  void Move(point_t newPoint) override;
private:
  double rad_;
  point_t center_;
};
#endif
