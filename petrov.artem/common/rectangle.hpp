#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace petrov
{
  class Rectangle:
    public petrov::Shape
  {
  public:
    Rectangle(const petrov::point_t & middle, const double width, const double height);
    double getArea() const noexcept override;
    petrov::rectangle_t getFrameRect() const noexcept override;
    void move(const petrov::point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
  private:
    petrov::point_t middle_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif
