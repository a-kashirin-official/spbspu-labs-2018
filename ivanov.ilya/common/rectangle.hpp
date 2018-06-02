#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace ivanov
{
class Rectangle: public Shape
{
public:
  Rectangle(const rectangle_t & rect);
  void show() const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & p) override;
  void move(double dx, double dy) override;
  void scale(double koeff) override;
private:
  rectangle_t bar_;
};
}
#endif // RECTANGLE_HPP
