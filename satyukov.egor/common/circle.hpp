#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace satyukov
{
  class Circle:
      public satyukov::Shape
  {
  public:
    Circle(const satyukov::point_t & center, const double radius);
    double getArea() const noexcept override;
    double getRadius() const noexcept;
    double getAngle() const noexcept override;
    satyukov::point_t getCoordinates() const noexcept override;
    satyukov::rectangle_t getFrameRect() const noexcept override;
    void move(const satyukov::point_t  & newCenter) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
    
  private:
    satyukov::point_t center_;
    double radius_;
    double angle_;
  };
}

#endif
