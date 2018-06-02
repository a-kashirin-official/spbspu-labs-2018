#ifndef TRIANGLE_HPP_FILE
#define TRIANGLE_HPP_FILE

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t fPoint, const point_t sPoint, const point_t tPoint);

  virtual void move(const point_t &newP);
  virtual void move(const double &nX, const double &nY);

  virtual double getArea() const;
  virtual rectangle_t getFrameRect() const;

private:
  point_t vertices_[3];
};

#endif
