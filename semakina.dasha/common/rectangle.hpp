#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace semakina
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const point_t & center, const double w, const double h);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double degree) noexcept override;
  private:
    point_t pos_;
    double width_;
    double height_;
    double degree_;
  };
}

#endif // RECTANGLE_HPP
