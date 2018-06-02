#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
namespace korovin
{
class Rectangle: public Shape
{
public:
  Rectangle(const point_t & rectCenter, const double width, const double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t & newPoint) override;
  point_t getPos() const override;
  void scale(const double coefficient) override;
private:
  point_t rectCenter_;
  double width_;
  double height_;
};
}
#endif
