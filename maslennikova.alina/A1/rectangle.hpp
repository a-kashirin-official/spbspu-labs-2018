#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape{
public:
  Rectangle(const point_t & center,const double h,const double w);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & newCenter) override;
  void move(const double dx, const double dy) override;
private:
  double width, height;
  point_t pos;
};

#endif //A1_RECTANGLE_HPP
