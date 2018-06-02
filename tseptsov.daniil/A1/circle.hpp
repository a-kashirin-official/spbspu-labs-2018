#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
public:
  Circle(const double rad, const point_t &pos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move(const double Ox, const double Oy) override;
  void OutData() const override;

private:
  double radius_;
  point_t center_;

};


#endif

