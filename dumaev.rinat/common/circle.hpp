#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace dumaev
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &point, const double radius);
    double getArea() const noexcept override;
    point_t getPos() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;

  private:
    point_t pos_;
    double radius_;
    double angle_;
  };
}
#endif
