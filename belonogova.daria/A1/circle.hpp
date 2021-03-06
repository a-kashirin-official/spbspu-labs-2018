#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const double newRad, const point_t & newPos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t & newPos) override;
private:
  double m_rad;
  point_t m_pos;
};

#endif //CIRCLE_HPP
