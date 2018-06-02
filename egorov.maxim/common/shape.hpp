#ifndef SHAPE_HPP
#define SHAPE_HPP
#include<string>
#include "base-types.hpp"

namespace egorov
{
  class Shape
  {
  public :
    virtual ~Shape() = default;

    virtual double getArea() const noexcept  = 0;

    virtual rectangle_t getFrameRect() const noexcept = 0;

    virtual void move(const point_t &point) noexcept = 0;

    virtual void move(const double deltaX, const double deltaY) noexcept = 0;

    virtual void scale(const double coefficent) = 0;

    virtual void rotate(double angle) noexcept = 0;

    virtual std::string getName() const noexcept = 0;
  };
}
#endif
