#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <cmath>
#include <iostream>
#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t & pos, const double width, const double height);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & point) override;
  virtual void move(const double dx, const double dy) override;
private:
  point_t pos_;
  double width_;
  double height_;;
  virtual void print(std::ostream & out) const override;
};

#endif
