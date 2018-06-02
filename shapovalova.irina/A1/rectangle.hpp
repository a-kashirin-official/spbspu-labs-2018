#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const rectangle_t & rect);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & posTo) override;
  virtual void move(const double dx, const double dy) override;

private:
  rectangle_t rect_;
};

#endif // RECTANGLE_HPP

