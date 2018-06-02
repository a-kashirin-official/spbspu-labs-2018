#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle :
  public Shape
{
public:
  Triangle(const point_t & a, const point_t & b, const point_t & c);
  void setVertexAtIndex(const int index, const point_t & vertex);
  point_t getVertexAtIndex(const int index) const;
  point_t getPos() const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & pos) override;
  void move(const double dx, const double dy) override;

private:
  point_t vertices_[3];
};

#endif
