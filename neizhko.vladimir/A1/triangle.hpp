#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"
#include "base-types.hpp"

class Triangle : public Shape
{
public:
  //  Cords of points: A (x, y), B (x, y), C (x, y)
  Triangle(double Ax, double Ay, double Bx, double By, double Cx, double Cy);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(point_t c) override;

  void move(double dx, double dy) override;

  void printInfo() const override;

private:

  point_t center_;

  point_t tri_A_;

  point_t tri_B_;

  point_t tri_C_;

};

#endif
