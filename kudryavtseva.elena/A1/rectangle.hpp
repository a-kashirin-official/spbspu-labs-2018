#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t & rectCenter, const double w, const double h);
  double getArea () const override;
  rectangle_t getFrameRect () const override;
  void move(double dx, double dy) override;
  void move(const point_t &center) override;
  void printf() override;
  point_t getPos();
private:
  point_t centerRec_;
  double width_;
  double height_;
};

#endif
