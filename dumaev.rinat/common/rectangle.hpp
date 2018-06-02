#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace dumaev
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &point, const double width, const double height);
    double getArea() const noexcept override;
    point_t getPos() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;

  private:
    point_t pos_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif
