#ifndef RECTANGLE_HPP_FILE
#define RECTANGLE_HPP_FILE

#include <cassert>
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &position, const double &width, const double &height);

  virtual void move(const point_t &newP);
  virtual void move(const double &nX, const double &nY);

  virtual double getArea() const;
  virtual rectangle_t getFrameRect() const;

private:
  double width_;
  double height_;
  point_t currPos_;
};

#endif
