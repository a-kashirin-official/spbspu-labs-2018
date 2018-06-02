#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace shapoval
{
  class Circle: 
    public shapoval::Shape
  {
  public:
    Circle(const shapoval::point_t & centre, const double radius);
    double getArea() const noexcept override;
    double getAngle() const noexcept;
    void scale(const double k) override;
    void rotate(const double a) noexcept override;
    shapoval::rectangle_t getFrameRect() const noexcept override;
    void move(const shapoval::point_t & new_centre) noexcept override;
    void move(const double dx, const double dy) noexcept override;
  private:
    shapoval::point_t centre_;
    double radius_;
    double angle_;
  };
}

#endif
