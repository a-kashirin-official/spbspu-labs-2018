#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace kahuanahil
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double width, const double height, const kahuanahil::point_t &pos);
    kahuanahil::rectangle_t getFrameRect() const noexcept override;
    kahuanahil::point_t getCenter() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t &pos) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
    double getArea() const noexcept override;
    double getAngle() const noexcept override;
  private:
    double m_width, m_height;
    point_t m_center;
    double m_angle;
  };
}

#endif
