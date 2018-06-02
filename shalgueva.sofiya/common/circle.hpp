#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace shalgueva
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & pos, const double radius);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & posTo)noexcept override;
    void scale(double coefficient) override;
    void rotate(double /*alpha*/) noexcept override;

  private:
    point_t position_;
    double radius_;
    double angle_;
  };
} // shalgueva

#endif // CIRCLE_HPP
