#ifndef HPP_CIRCLE
#define HPP_CIRCLE

#include "shape.hpp"

class Circle:
  public Shape
{
public:
  Circle(const point_t &centre, double radius);

  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(const double dx, const double dy) noexcept override;
  void move(const point_t &newcentre) noexcept override;

private:
  point_t centre_;
  double radius_;
};

#endif

