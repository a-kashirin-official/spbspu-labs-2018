#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"


namespace shalgueva
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t & rect);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & posTo) noexcept override;
    void scale(double coefficient) override;
    void rotate(double alpha) noexcept override;

  private:
    rectangle_t rect_;
    point_t corner_[4];
    double angle_;
  };
} // shalgueva

#endif // RECTANGLE_HPP
