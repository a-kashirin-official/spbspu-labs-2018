#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  // Constructor
  Rectangle(const point_t & new_coord, double h, double w);
  // Get area of Rectangle method
  virtual double getArea() const override;
  // Get frame of Rectangle method
  virtual rectangle_t getFrameRect() const override;
  // Move by Rectangle by dx and dy method
  virtual void move(double dx, double dy) override;
  // Move to a certain point method
  virtual void move(const point_t & pos) override;

private:
  // Position of Center
  point_t coord_;
  // Height of Rectangle
  double h_;
  // Width of Rectangle
  double w_;
};

#endif
