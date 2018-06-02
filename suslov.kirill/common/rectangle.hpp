#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace suslov
{
  class Rectangle: 
    public suslov::Shape
  {
  public:
    Rectangle(const suslov::point_t & center, const double width, const double height);

    suslov::rectangle_t getFrameRect() const noexcept override;    
    double getArea() const noexcept override;
    double getAngle() const noexcept override;

    void move(const double dx, const double dy) noexcept override;
    void move(const suslov::point_t & newPoint) noexcept override;

    void scale(const double coef) override;
    void rotate(const double angle) noexcept override;

  private:
    suslov::point_t center_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif
