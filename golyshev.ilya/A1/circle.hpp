#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double rad, const point_t &poss);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &poss) override;
  void move(double Ox, double Oy) override;
  void OutInf() const override;

private:
  double radius_;
  point_t center_;

};

#endif
