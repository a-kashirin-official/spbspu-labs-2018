#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace shumkovskaya

{
  class Circle : public Shape
  {
  public:
    Circle(const double r, const point_t & p);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & p) override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
  private:
    double radius_;
    point_t pos_;
    double angle_;
  };
}

#endif
