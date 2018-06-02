#ifndef CRICLE_HPP
#define CRICLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  // Constructor of Circle
  Circle(const point_t & new_coord, double new_radius);
  // Get area of Circle method
  virtual double getArea() const override;
  // Get frame of Circle method
  virtual rectangle_t getFrameRect() const override;
  // Move Circle by dx and dy method
  virtual void move(double dx, double dy) override;
  // Move to a point method
  virtual void move(const point_t & pos) override;

private:
  // Center coordinates
  point_t coord_;
  // Radius
  double radius_;
};


#endif
