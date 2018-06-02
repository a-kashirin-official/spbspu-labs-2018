//
// Created by russk on 30.03.2018.
//

#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace russkov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(point_t &center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &point) override;
    void move(double dx, double dy) override;
    void scale(const double ratio) override;
    void rotate(const double alpha) override;

  private:
    point_t center_;
    double width_, height_;
    double alpha_;
  };
}

#endif //A1_RECTANGLE_HPP
