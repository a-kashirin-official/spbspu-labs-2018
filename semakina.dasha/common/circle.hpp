#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include <stdexcept>

namespace semakina
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t & pos, const double radius);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double degree) noexcept override;
  private:
    point_t pos_;
    double radius_;
    double degree_;
  };
}

#endif // CIRCLE_HPP
