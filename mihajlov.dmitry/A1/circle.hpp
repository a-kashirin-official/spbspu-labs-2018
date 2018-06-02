#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t & centerPos, const double r);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & centerPos) override;
  void move(const double shiftX, const double shiftY) override;
  void getInfo() const override;
private:
  point_t pos;
  double radius;
};


#endif //A1_CIRCLE_HPP
