#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace shapovalova
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & pos, const double radius);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & posTo) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double degrees) noexcept override;

  private:
    point_t position_;
    double radius_;
    double angle_;
  };
}

#endif // CIRCLE_HPP
