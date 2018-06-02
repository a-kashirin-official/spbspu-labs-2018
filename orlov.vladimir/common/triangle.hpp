#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"
#include <math.h>


namespace orlov
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t & A, const point_t & B, const point_t & C);

    double getArea() const noexcept override;
    point_t getPos() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double koef) override;

  private:
    point_t A_;
    point_t B_;
    point_t C_;
    point_t centre_;
  };
}
#endif
