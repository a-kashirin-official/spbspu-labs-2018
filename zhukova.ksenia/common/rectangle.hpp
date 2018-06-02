
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace zhukova
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & center, double width, double height, double angle = 0);
    Rectangle(const Rectangle & arg);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t & point) override;
    void scale(double coefficient) override;
    void rotate(double deg) override;

  private:
    point_t center_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif // RECTANGLE_HPP
