#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{

//Public methods, fucntions and variables
public:

  //Constructor of the class
  Rectangle(const rectangle_t & new_center);

  //Function returning Area value
  virtual double getArea() const override;

  //Function returning resctangle, sorrounding the object 
  virtual rectangle_t getFrameRect() const override;

  //Move to new coordinates
  virtual void move(const point_t & new_center) override;

  //Shifting coordinates
  virtual void move(double dx, double dy) override;

  //Private methods, fucntions and variables  
  private:

  //Rectangle's coordinates and size in one variable 
  rectangle_t m_rectangle;

};

#endif
