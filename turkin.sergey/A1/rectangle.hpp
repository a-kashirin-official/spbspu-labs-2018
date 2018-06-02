#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t &pos);
  Rectangle(double x, double y, double width, double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move(double Ox, double Oy) override;
  void printInfo() override;
private:
  double width_;
  double height_;
  point_t center_;

};

#endif
