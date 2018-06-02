#ifndef HPP_SHAPE
#define HPP_SHAPE

#include <memory>

#include "base-types.hpp"

namespace sokolova
{
  class Shape {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const noexcept = 0;
    virtual sokolova::rectangle_t getFrameRect() const noexcept = 0;

    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void move(const sokolova::point_t &newcentre) noexcept = 0;
    virtual void scale(const double factor) = 0;
    virtual void rotate(const double angle) noexcept = 0;
    virtual std::unique_ptr<sokolova::Shape> getCopy() const noexcept = 0;
    virtual void printInfo() const = 0;

  protected:
    sokolova::point_t centre_;
  };
}

#endif
