#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace spodeneyko
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const rectangle_t & rect);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    std::string getName() const noexcept override;
    void scale(const double factor) override;
    void move(const point_t & point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void rotate(const double angle) noexcept override;
    
  private:
    rectangle_t rect_;
    point_t vertex_[4];
  };
}

#endif
