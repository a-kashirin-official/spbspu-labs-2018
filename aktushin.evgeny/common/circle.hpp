#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED
#include "shape.hpp"

namespace aktushin
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t &pos, double radius);
    double getRadius() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printInfo() const override;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double k) override;

  private:
    point_t pos_;
    double radius_;
  };
}

#endif
