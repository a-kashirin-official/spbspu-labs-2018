#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t &rect);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const double dx, const double dy) override;
  virtual void move(const point_t &newPos) override;
private:
  rectangle_t rectangle_;
};


#endif
