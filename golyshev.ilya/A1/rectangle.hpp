#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t &poss);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &poss) override;
  void move(double Ox, double Oy) override;
  void OutInf()const override;

private:
  double width_;
  double height_;
  point_t center_;

};

#endif
