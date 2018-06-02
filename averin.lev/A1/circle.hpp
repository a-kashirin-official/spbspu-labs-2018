#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle : public Shape 
{
public:   
    
  Circle(double r, double x, double y);
    
  double getArea() const override;
       
  rectangle_t getFrameRect() const override;   
    
  void printInfo() const override;   
  
  void move(point_t c) override;
  
  void move(double dx, double dy) override;
    
private:
    
  double rad_;
  
  point_t center_;
};
#endif
