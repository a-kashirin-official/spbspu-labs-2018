#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace averin
{
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
  
  virtual void scale(double ratio) = 0;
  
  virtual void rotate(double deg) = 0;
  
  virtual void printAngle() const = 0;
  
  virtual void setAngle(double deg) = 0;
  
  virtual void printName() const = 0;
  
};
}
#endif
