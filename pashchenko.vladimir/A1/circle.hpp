#ifndef CIRCLE_HPP_FILE
#define CIRCLE_HPP_FILE

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &position, const double &radius);

  virtual void move(const point_t &newP);
  virtual void move(const double &nX, const double &nY);

  virtual double getArea() const;
  virtual rectangle_t getFrameRect() const;

private:
  double radius_;
  point_t currPos_;
};

#endif
