#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &centerPos, const double radius);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const double dx, const double dy) override;
  virtual void move(const point_t &newPos) override;
private:
  point_t center_;
  double radius_;
};


#endif
