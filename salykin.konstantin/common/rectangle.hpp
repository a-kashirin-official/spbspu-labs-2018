#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace salykin
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t & center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPos) override;
    void move(const double dx, const double dy) override;
    point_t getPos() const override;
    void scale(const double multiplier) override;
    
    double getHeight() const;
    double getWidth() const;
  private:
    point_t center_;
    double width_, height_;
  };
}

#endif
