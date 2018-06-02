#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

#include "base-types.hpp"

// Own namespace
namespace hvatov {

  // shape abstract class
  class Shape
  {
    // Public members
  public:
    // Virtual destructor of the class
    virtual ~Shape() = default;

    // Scale method
    virtual void scale(double k) = 0;

    // Get area method
    virtual double getArea() const noexcept = 0;

    // Get frame rectangle method
    virtual rectangle_t getFrameRect() const noexcept = 0;

    // Move to the point method
    virtual void move(const point_t &pos) = 0;

    // Move by dx and dy
    virtual void move(double dx, double dy) = 0;

    // Rotate method
    virtual void rotate(double angle) noexcept = 0;

    // Get the coordinates of current position
    virtual point_t getPosition() const noexcept = 0;

    // Get the information of about shape
    virtual std::ostream & getInfo(std::ostream & stream) const noexcept = 0;
  };
}

#endif // SHAPE_HPP

