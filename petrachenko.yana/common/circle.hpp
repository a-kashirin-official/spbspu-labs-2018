#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace petrachenko
{
  class Circle : public Shape
  {
  public:
    Circle(const double radius, const point_t &center);
    double getArea()const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &p) override;
    void move(const double dx, const double dy) override;
    void scale(double coefficient) override;
    void rotate(double /*alpha*/) override;
    void print() const override;
    point_t getPos() const;
  private:
    double radius_;
    point_t center_;
  };
}

#endif

