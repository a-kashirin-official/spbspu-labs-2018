#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"
#include "base-types.hpp"
#include <cstdlib>
class Triangle : public Shape
{
public:
  Triangle(point_t a ,point_t b ,point_t c);
  double getArea()const override;
  rectangle_t getFrameRect()const override;
  void Move(double xx,double yy) override;
  void Move(point_t newPoint) override;
private:
  point_t center_;
  point_t a_;
  point_t b_;
  point_t c_;    
};
#endif
