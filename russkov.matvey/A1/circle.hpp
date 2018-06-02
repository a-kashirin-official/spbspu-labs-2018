//
// Created by russk on 31.03.2018.
//

#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &center, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &point) override;
  void move(double dx, double dy) override;
  void scale(const double ratio) override;

private:
  point_t center_;
  double radius_;
};

#endif //A1_CIRCLE_HPP
