#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <cmath>
#include <iostream>
#include "shape.hpp"

namespace vasekha
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & pos, const double width, const double height);
    virtual double getArea() const noexcept override;
    virtual rectangle_t getFrameRect() const noexcept override;
    virtual void move(const point_t & point) noexcept override;
    virtual void move(const double dx, const double dy) noexcept override;
    virtual void scale(const double factor) override;
    virtual void rotate(const double angle) noexcept override;
  private:
    point_t pos_;
    double width_;
    double height_;
    double angle_;
    virtual void print(std::ostream & out) const noexcept override;
  };
}

#endif
