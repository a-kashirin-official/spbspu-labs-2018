#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle:
  public Shape
{
public:
  Circle(double radius, const point_t& center);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t& newPos) override;
  virtual void move(double dx, double dy) override;
private:
  point_t center_;
  double radius_;
};

#endif //CIRCLE_HPP
