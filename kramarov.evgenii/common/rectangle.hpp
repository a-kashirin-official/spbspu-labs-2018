#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace kramarov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double height, const double width, const point_t & center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move (const point_t & newLocation) override;
    void move (const double dx, const double dy) override;
    void scale (const double scaleRate) override;
    point_t getXY() const override;
  private:
    double height_;
    double width_;
    point_t center_;
  };
}

#endif
