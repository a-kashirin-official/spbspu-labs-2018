#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace gerastyonok
{
class Circle : public Shape
{
public:
  Circle(double r, const point_t & center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & pos) override;
  void move(double px, double py) override;
  void scale(const double k) override;
  point_t getCenter() const override;

private:
  double rad_;
  point_t center_;
};
}

#endif


