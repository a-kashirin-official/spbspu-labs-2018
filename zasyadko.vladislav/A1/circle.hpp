#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER
#include "shape.hpp"

class Circle :
  public Shape
{
public:
  
  Circle(const point_t & center, const double radius);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  
  void move(const point_t & Center) override;
  void move(const double add_x, const double add_y) override;
  
  void print() const override;
  
private:
  
  point_t cntr_;
  
  double r_;
  
};
  
#endif
    
