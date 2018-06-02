#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace shapovalova
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const rectangle_t & rect);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & posTo) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double degrees) noexcept override;

  private:
    rectangle_t rect_;
    point_t vertex_[4];
    double angle_;
  };
}

#endif // RECTANGLE_HPP

