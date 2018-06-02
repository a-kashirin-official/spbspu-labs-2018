#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace pichugina
{
  class Rectangle:
    public pichugina::Shape
  {
  public:
    Rectangle(const pichugina::point_t & middle, const double width, const double height);
    double getArea() const override;
    pichugina::rectangle_t getFrameRect() const override;
    void move(const pichugina::point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
  private:
    pichugina::point_t middle_;
    double width_;
    double height_;
  };
}

#endif
