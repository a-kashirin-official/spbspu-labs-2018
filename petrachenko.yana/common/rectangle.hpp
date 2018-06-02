#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace petrachenko
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t &center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &p) override;
    void move(const double dx, const double dy) override;
    void scale(double coefficient) override;
    void rotate(double alpha) override;
    void print() const override;
  private:
    point_t getPos() const;
    point_t vertices_[4];
    double getDistance(const point_t &point1, const point_t &point2) const;
  };
}

#endif

