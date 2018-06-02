#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace krasilnikov
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle (const double height, const double width, const point_t & middle);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPosition) override;
    void move(const double dx, const double dy) override;
    point_t getPosition() const override;
    double getHeight() const;
    double getWidth() const;
    void scale(const double factor) override;
    void rotate(const double angle) override;

  private:
    point_t middle_;
    double height_;
    double width_;
    double angle_;
  };
}

#endif
