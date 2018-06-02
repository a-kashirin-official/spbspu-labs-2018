#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
class Shape 
{
public:  
       
  virtual ~Shape() = default;
        
  virtual double getArea() const = 0; 
    
  virtual rectangle_t getFrameRect() const = 0; 
    
  // Move to point
  virtual void move(point_t c) = 0; 
    
  // Shifting by x,y
  virtual void move(double dx, double dy) = 0;
    
  virtual void printInfo() const = 0;  
  
};
#endif
