#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace kahuanahil
{
  class Circle : public Shape
  {
   public:
    Circle(const double r, const kahuanahil::point_t &pos);
    kahuanahil::rectangle_t getFrameRect() const noexcept override;
    kahuanahil::point_t getCenter() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const kahuanahil::point_t &pos) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
    double getArea() const noexcept override;
    double getAngle() const noexcept override;
  private:
    double m_r;
    point_t m_center;
    double m_angle;
  };
}

#endif 
