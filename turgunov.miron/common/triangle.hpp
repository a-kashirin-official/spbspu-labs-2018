#ifndef TRIANGLE_HPP_INCLUDED
#define TRIANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace turgunov
{
  class Triangle:
    public Shape
  {
  public:
    Triangle(const point_t &, const point_t &, const point_t &);
    point_t getCenter() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printInfo() const override;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double k) override;

  private:
    point_t corners_[3];
  };
}

#endif
