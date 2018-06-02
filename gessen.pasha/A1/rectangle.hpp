#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle: public Shape
{
  public:
    Rectangle(const point_t & angle, const double width, const double heigth);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & newPoint) override;
  private:
    point_t angle_;
    double width_;
    double heigth_;
};

#endif
