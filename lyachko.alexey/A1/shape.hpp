#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"


//Abstract class Shape, used to make others
class Shape
{

//Public methods, fucntions and variables
public:

  virtual ~Shape() = default;

  //Pure virtual function returning area
  virtual double getArea() const = 0;

  //Pure virtual fucntion returning rectangle, sorrounding the object
  virtual rectangle_t getFrameRect() const = 0;

  //Pure virtual method moving object to the new coordinates
  virtual void move(const point_t & new_center) = 0;

  //Pure virtual method, shifting coordinates
  virtual void move(double dx, double dy) = 0;

};

#endif 
