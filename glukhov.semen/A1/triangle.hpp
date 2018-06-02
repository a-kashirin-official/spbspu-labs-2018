#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &AngelA, const point_t &AngelB, const point_t &AngelC);
  void setPoints(const point_t &AngelA, const point_t &AngelB, const point_t &AngelC);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &point) override;
  void move(double dx, double dy) override;
  void printShapeInfo() const override;
private:
  point_t pos_;
  point_t A_vertex;
  point_t B_vertex;
  point_t C_vertex;
  static double getMin(const double &AngelA, const double &AngelB, const double &AngelC);
  static double getMax(const double &AngelA, const double &AngelB, const double &AngelC);
};
#endif

