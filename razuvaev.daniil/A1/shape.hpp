#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape {
public:   
  virtual ~Shape() = default; // distruct
        
  virtual double getArea() const = 0; 
  virtual rectangle_t getFrameRect() const = 0; 
  virtual void move(point_t c) = 0;            // to point
  virtual void move(double dx, double dy) = 0; // axial displacement
    
  virtual void writeInfoOfObject() const = 0;  
};
#endif