#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <memory>

#include "shape.hpp"

namespace afanasiev
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t & center, const double radius);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & newPos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    point_t getPos() const noexcept override;
    double getRadius() const noexcept;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
  private:
    point_t center_;
    double radius_;
    double angle_;
  };
}

#endif
