#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape 
{
public:       

  //Height, width, x y cords of center
  Rectangle(double h, double w, double x, double y);
    
  double getArea() const override;
       
  rectangle_t getFrameRect() const override;  
    
  void printInfo() const override;
  
  void move(point_t c) override;
  
  void move(double dx, double dy) override;  
    
private:
    
  double height_;
    
  double width_;
  
  point_t center_;
 
};
#endif
