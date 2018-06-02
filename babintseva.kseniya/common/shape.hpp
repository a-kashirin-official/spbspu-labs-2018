#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
#include <string>

namespace babintseva
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual std::string getName() const = 0;
    virtual rectangle_t getFrameRect() const = 0;

    virtual point_t getPos() const = 0;

    virtual void move(const point_t &pos) = 0;
    virtual void move(const double dx, const double dy) = 0;

    virtual void scale(double ratio) = 0;

    virtual void rotate(double angle) = 0;
  };
}

#endif
