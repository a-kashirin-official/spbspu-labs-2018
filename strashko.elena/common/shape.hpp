#ifndef HPP_SHAPE
#define HPP_SHAPE

#include <memory>

#include "base-types.hpp"

namespace strashko
{
  class Shape {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const noexcept = 0;
    virtual strashko::rectangle_t getFrameRect() const noexcept = 0;

    virtual void move(const double dx, const double dy) noexcept = 0;
    virtual void move(const strashko::point_t &newcentre) noexcept = 0;
    virtual void scale(const double factor) = 0;
    virtual void rotate(const double angle) noexcept = 0;
    virtual std::unique_ptr<strashko::Shape> getCopy() const noexcept = 0;
    virtual void printInfo() const = 0;

  protected:
    strashko::point_t centre_;
  };
}

#endif
