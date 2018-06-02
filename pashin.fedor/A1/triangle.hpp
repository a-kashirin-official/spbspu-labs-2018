#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <string>
#include "shape.hpp"
#include "base-types.hpp"

class Triangle : public Shape
{
public:
  Triangle(point_t vertices[3]);
  std::string getInfo() const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& new_center) override;
  void move(double dx, double dy) override;
  point_t getCenter() const;

private:
  point_t vertices_[3];
};

#endif  // TRIANGLE_HPP
