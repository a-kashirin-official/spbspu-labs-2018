#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Circle : public Shape {
public:
  Circle(const point_t &centre, double rad);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t &a) override;

  void move(double dx, double dy) override;

private:
  point_t centre_;
  const double rad_;
};


#endif //CIRCLE_HPP
