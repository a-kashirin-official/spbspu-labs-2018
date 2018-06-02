#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace mordvintseva 
{
  class Circle : public Shape
  {
  public:
    Circle(const double r, const point_t & point);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
  private:
    double radius_;
    point_t center_;
  };
}

#endif
