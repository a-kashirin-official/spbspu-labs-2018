#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace gerastyonok
{
class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t & rect);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & pos) override;
  void move(double px, double py) override;
  void scale(const double k) override;
  point_t getCenter() const override;

private:
  rectangle_t rect_;
};
}

#endif
