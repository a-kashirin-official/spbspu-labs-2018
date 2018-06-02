#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED
#include <iostream>
#include "shape.hpp"

namespace xiezhuang
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const point_t &pos, double width, double height);
    point_t getPosition() const;
    double getWidth() const;
    double getHeight() const;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double factor) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printInfo() const override;

  private:
    point_t pos_;
    double width_, height_;
  };
}

#endif
