#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

namespace pristup
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t & firstPt, const point_t & secondPt, const point_t & thirdPt);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & p) noexcept override;
    void scale(double k) override;
    
  private:
    point_t firstPt_;
    point_t secondPt_;
    point_t thirdPt_;
  };
};

#endif

