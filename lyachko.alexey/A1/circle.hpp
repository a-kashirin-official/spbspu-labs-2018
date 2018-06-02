#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{

//Public methods, fucntions and variables
public:

  //Constructor
  Circle(const point_t & new_center, double new_r);

  //Fucntion returning Area value
  virtual double getArea() const override;

  //Fucntion returning resctangle, sorrounding the object
  virtual rectangle_t getFrameRect()  const override;

  //Move to new coordinates
  virtual void move(const point_t & new_center) override;

  //Shifting coordinates
  virtual void move(double dx, double dy) override;

//Private methods, fucntions and variables
private:

  //Coorinates 
  point_t m_center;

  //Radius
  double m_r;

};

#endif
