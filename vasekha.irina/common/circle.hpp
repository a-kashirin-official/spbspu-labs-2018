#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include "shape.hpp"

namespace vasekha
{
  class Circle: public Shape
  {
  public:
    Circle(const point_t & pos, const double radius);
    virtual double getArea() const noexcept override;
    virtual rectangle_t getFrameRect() const noexcept override;
    virtual void move(const point_t & point) noexcept override;
    virtual void move(const double dx, const double dy) noexcept override;
    virtual void scale(const double factor) override;
    virtual void rotate(const double angle) noexcept override;
  private:
    point_t pos_;
    double radius_;
    virtual void print(std::ostream & out) const noexcept override;
  };
}

#endif
