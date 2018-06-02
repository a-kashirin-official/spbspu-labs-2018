#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED
#include "shape.hpp"

namespace xiezhuang
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t &pos, double radius);
    point_t getPosition() const;
    double getRadius() const;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double factor) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printInfo() const override;

  private:
    point_t pos_;
    double radius_;
  };
}

#endif
