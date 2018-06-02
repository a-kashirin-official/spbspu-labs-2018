
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape {
public:
  Rectangle(const point_t &centre, double width, double height);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t &a) override;

  void move(double dx, double dy) override;

private:
  point_t centre_;
  const double width_;
  const double height_;

};


#endif //RECTANGLE_HPP
