#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

namespace gerastyonok
{
class Triangle : public Shape
{
public:
  Triangle(const point_t & a, const point_t & b, const point_t & c);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & pos) override;
  void move(double px, double py) override;
  void scale(const double k) override;
  point_t getCenter() const override;


private:
  point_t a_, b_, c_;
  point_t center_;
};
}

#endif
