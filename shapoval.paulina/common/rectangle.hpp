#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace shapoval
{
  class Rectangle:
    public shapoval::Shape
  {
  public:
    Rectangle(const shapoval::point_t & center, const double widht, const double height);
    double getArea() const noexcept override;
    double getAngle() const noexcept;
    void scale(const double k) override;
    void rotate(const double a) noexcept override;
    shapoval::rectangle_t getFrameRect() const noexcept override;
    void move(const shapoval::point_t & new_centre) noexcept override;
    void move(const double dx, const double dy) noexcept override;
  private:
    shapoval::point_t centre_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif
