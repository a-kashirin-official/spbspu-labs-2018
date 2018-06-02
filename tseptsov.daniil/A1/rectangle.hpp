#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
public:
  Rectangle(const double width, const double height, const point_t &pos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move(const double Ox, double Oy) override;
  void OutData() const override;

private:
  double width_;
  double height_;
  point_t center_;

};


#endif

