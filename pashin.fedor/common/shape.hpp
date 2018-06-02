#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

#include "base-types.hpp"

namespace pashin {
  class Shape
  {
  public:
    virtual ~Shape() = default;
    
    virtual point_t getCenter() const = 0;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual std::string getInfo() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t& new_center) = 0;
    virtual void scale(double k) = 0;
    virtual void rotate(double angle) = 0;
  };
}

#endif  // SHAPE_HPP
