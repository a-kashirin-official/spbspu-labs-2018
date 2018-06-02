#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace krasilnikov
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t & center, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPosition) override;
    void move(const double dx, const double dy) override;
    point_t getPosition() const;
    double getRadius() const;
    void scale(const double factor) override;
    void rotate(const double angle) override;
  private:
    point_t center_;
    double radius_;
    double angle_;
  };
}

#endif
