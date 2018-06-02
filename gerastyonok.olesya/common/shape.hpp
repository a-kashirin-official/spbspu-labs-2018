#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace gerastyonok
{
class Shape
{
public:
  virtual ~Shape() = default;
  point_t center;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t & pos) = 0;
  virtual void move(double px, double py) = 0;
  virtual void scale(const double k) = 0;
  virtual point_t getCenter() const = 0;
};
}


#endif
