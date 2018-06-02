#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED
#include "base-types.hpp"
#include <string>

namespace stankeviciute
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    void printData() const;
    virtual std::string getName() const = 0;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void printFeatures() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t &pos) = 0;
    virtual void scale(double k) = 0;
    virtual void rotate(double angle) = 0;
  };
}

#endif
