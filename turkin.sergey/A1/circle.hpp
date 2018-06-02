#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double x, double y, double r);
  Circle(double r, const point_t &pos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move(double Ox, double Oy) override;
  void printInfo() override;
private:
  double radius_;
  point_t center_;

};

#endif
