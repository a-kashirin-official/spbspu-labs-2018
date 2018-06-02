#ifndef WORK_RECTANGLE_HPP
#define WORK_RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t &rectangle);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & newCentrePoint) override;
  void move(const double dx, const double dy) override;
private:
  rectangle_t rectangle_;
};
#endif
