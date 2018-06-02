#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include "shape.hpp"

namespace vasekha
{
  class Triangle: public Shape
  {
  public:
    Triangle(const point_t & vertex_1, const point_t & vertex_2, const point_t & vertex_3) noexcept;
    virtual double getArea() const noexcept override;
    virtual rectangle_t getFrameRect() const noexcept override;
    virtual void move(const point_t & point) noexcept override;
    virtual void move(const double dx, const double dy) noexcept override;
    virtual void scale(const double factor) override;
    virtual void rotate(const double angle) noexcept override;
  private:
    point_t pos_;
    point_t vertices_[3];
    virtual void print(std::ostream & out) const noexcept override;
  };
}

#endif
