#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace subtselnaya
{
  class Circle : public Shape {
  public:
    Circle (const point_t & center, const double radius);

    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t & resPoint);
    void move(const double dx, const double dy);
    void scale(const double value);

  private:
    point_t center_;
    double radius_;
  };
}

#endif // CIRCLE_HPP

