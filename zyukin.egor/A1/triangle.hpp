#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.hpp"
#include "base-types.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &p1, const point_t &p2, const point_t &p3);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t &p) override;

private:
  point_t a_, b_, c_;
  point_t findCenter() const;
  static double getDistance(const point_t &p1, const point_t &p2);
};

#endif
