#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &center, const double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &newCenterPoint) override;
  void move(const double dx, const double dy) override;
private:
  point_t center_;
  double radius_;
};

#endif //A1_CIRCLE_HPP
