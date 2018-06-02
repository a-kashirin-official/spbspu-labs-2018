#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace aktushin
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const point_t &pos, double width, double height);
    double getWidth() const;
    double getHeight() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printInfo() const override;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double k) override;

  private:
    point_t pos_;
    double width_, height_;
  };
}

#endif
