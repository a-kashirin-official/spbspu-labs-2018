#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace egorov
{
  class Circle: public Shape
  {
  public:
    Circle(const double radius, const point_t &centr);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &point) noexcept override;

    void move(const double deltaX, const double  deltaY) noexcept override;

    void scale(const double coefficent) override;

    void rotate(double) noexcept override;

    std::string getName() const noexcept override;

  private:
    double radius_;
    point_t centr_;
  };
}
#endif
