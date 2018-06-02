#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace satyukov
{
  class Rectangle:
      public satyukov::Shape
  {
  public:
    Rectangle(const satyukov::point_t & center, const double width, const double height);
    double getArea() const noexcept override;
    double getWidth() const noexcept;
    double getHeight() const noexcept;
    double getAngle() const noexcept override;
    satyukov::point_t getCoordinates() const noexcept override;
    satyukov::rectangle_t getFrameRect() const noexcept override;
    void move(const satyukov::point_t  & newCenter) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
    
  private:
    satyukov::point_t center_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif
