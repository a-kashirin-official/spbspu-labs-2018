#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace hvetsckovich
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t & pos, double radius);
    point_t getPos() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    double getRadius() const;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
    void rotate(const double degrees) override;

  private:
    point_t pos_;
    double radius_;
    double angle_;
  };
}

#endif