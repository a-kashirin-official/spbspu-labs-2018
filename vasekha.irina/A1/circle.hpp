#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t & pos, const double radius);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & point) override;
  virtual void move(const double dx, const double dy) override;
private:
  point_t pos_;
  double radius_;
  virtual void print(std::ostream & out) const override;
};

#endif
