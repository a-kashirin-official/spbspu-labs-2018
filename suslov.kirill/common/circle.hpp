#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace suslov
{
  class Circle: 
    public suslov::Shape
  {
  public:
    Circle(const suslov::point_t & center, const double radius);

    double getArea() const noexcept override;
    suslov::rectangle_t getFrameRect() const noexcept override;
    double getAngle() const noexcept override;

    void move(const double dx, const double dy) noexcept override;
    void move(const suslov::point_t & newPoint) noexcept override;

    void scale(const double coef) override;
    void rotate(const double angle) noexcept override;

  private:
    suslov::point_t center_;
    double radius_;
    double angle_;
  };
}

#endif
