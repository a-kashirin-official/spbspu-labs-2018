#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "base-types.hpp"

namespace spodeneyko
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual std::string getName() const noexcept = 0;
    virtual void scale(const double factor) = 0;
    virtual void move(const point_t & point) noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void rotate(const double angle) = 0;
  };
}

#endif
