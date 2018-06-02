#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace hvetsckovich
{
  class Rectangle :
    public Shape
  {
  public:
    Rectangle(const point_t & pos, const double width, const double height);
    point_t getPos() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
    void rotate(const double degrees) override;

  private:
    point_t pos_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif
