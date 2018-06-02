#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <memory>

#include "shape.hpp"

namespace afanasiev
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t & mid);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & newPos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    point_t getPos() const noexcept override;
    double getHeight() const noexcept;
    double getWidth() const noexcept;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
  private:
    point_t mid_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif
