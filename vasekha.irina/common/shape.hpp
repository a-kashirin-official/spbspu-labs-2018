#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <memory>
#include "base-types.hpp"

namespace vasekha
{
  class Shape
  {
  public:
    using ptr_shape=std::shared_ptr<Shape>;
    virtual ~Shape() = default;
    friend std::ostream & operator<<(std::ostream & out, const Shape & shape) noexcept;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const point_t & point) noexcept = 0;
    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void scale(const double factor) = 0;
    virtual void rotate(const double angle) noexcept = 0;
  private:
    virtual void print(std::ostream & out) const noexcept = 0;
  };
}

#endif
