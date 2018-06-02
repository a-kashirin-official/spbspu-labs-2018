#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace petrov
{
  class Circle:
    public petrov::Shape
  {
  public:
    Circle(const petrov::point_t & centre, const double radius);
    double getArea() const noexcept override;
    petrov::rectangle_t getFrameRect() const noexcept override;
    void move(const petrov::point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
  private:
    petrov::point_t centre_;
    double radius_;
    double angle_;
  };
}

#endif
