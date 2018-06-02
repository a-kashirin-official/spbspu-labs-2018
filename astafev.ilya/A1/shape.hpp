#ifndef HPP_SHAPE
#define HPP_SHAPE

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;

  virtual double getArea() const noexcept = 0;
  virtual rectangle_t getFrameRect() const noexcept = 0;
  virtual void move(const double dx, const double dy) noexcept = 0;
  virtual void move(const point_t &newcentre) noexcept = 0;
};

#endif

