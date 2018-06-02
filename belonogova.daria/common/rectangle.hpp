#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace belonogova
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t & rect);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & newPos) override;
    void scale(const double coef) override;
    void rotate(const double alfa) override;
  private:
    rectangle_t m_rect;
    double m_angle;
  };
}
#endif //RECTANGLE_HPP
