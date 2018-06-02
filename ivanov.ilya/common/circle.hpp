#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace ivanov
{
class Circle: public Shape
{
public:
  Circle(const point_t & center, double r);
  void show() const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & movement) override;
  void move(double dx, double dy) override;
  void scale(double koeff) override;
private:
  point_t center_;
  double radius_;
};
}
#endif // CIRCLE_HPP
