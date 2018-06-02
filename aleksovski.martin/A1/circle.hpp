#include "shape.hpp"

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class Circle : public Shape
{
public:
  Circle(double radius, const point_t & point);

  point_t getCentre() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t & p) override;

private:
  double m_radius;
  point_t m_centre;
};

#endif
