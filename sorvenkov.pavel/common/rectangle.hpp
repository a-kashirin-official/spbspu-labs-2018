#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace sorvenkov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double Ox, double Oy) override;
    void scale(double ratio) override;

  private:
    double width_, height_;
    point_t center_;
  };
}
#endif
