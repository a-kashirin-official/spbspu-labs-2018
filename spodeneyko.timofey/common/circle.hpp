#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace spodeneyko
{
  class Circle: public Shape
  {
  public:
    Circle(const double radius, const point_t & center);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    std::string getName() const noexcept override;
    void scale(const double factor) override;
    void move(const point_t & point) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void rotate(const double /*angle*/) noexcept override;
    
  private:
    double radius_;
    point_t center_;
  };
}

#endif
