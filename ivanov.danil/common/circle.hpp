#ifndef WORK_CIRCLE_HPP
#define WORK_CIRCLE_HPP

#include "shape.hpp"

namespace ivanov
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & centre, const double radius);

    rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const point_t & newCentrePoint) override;
    void move(const double dx, const double dy) override;
    void scale(const double ratio) override;
  private:
    point_t centre_;
    double radius_;
  };
}

#endif
