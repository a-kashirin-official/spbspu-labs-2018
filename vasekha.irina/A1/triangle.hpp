#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include "shape.hpp"

class Triangle: public Shape
{
public:
  Triangle(const point_t & vertex_1, const point_t & vertex_2, const point_t & vertex_3);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & point) override;
  virtual void move(const double dx, const double dy) override;
private:
  point_t pos_;
  point_t vertices_[3];
  virtual void print(std::ostream & out) const override;
};

#endif
