#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include <memory>
#include "base-types.hpp"

namespace lashchenov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t & NewCenter) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double multiplier) = 0;
    virtual void rotate(double degrees) = 0;
    virtual std::unique_ptr<Shape> getCopy() const = 0;
    virtual void printInfo() const = 0;
  };
}
#endif //A1_SHAPE_HPP
