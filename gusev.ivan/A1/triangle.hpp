#include "shape.hpp"
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

class Triangle : public Shape
{
  public:
    Triangle(const point_t &a, const point_t &b, const point_t &c);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &point) override;
    void move(const double dx, const double dy) override;

  private:
    point_t a_, b_, c_;
};

#endif
