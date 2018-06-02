#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t & centerPos, const double height, const double width);
  Rectangle(const rectangle_t & tempRect);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & centerPos) override;
  void move(const double shiftX, const double shiftY) override;
  void getInfo() const override;
private:
  rectangle_t data;
};


#endif //A1_RECTANGLE_HPP
