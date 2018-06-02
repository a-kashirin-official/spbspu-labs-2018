#ifndef REACTANGLE_HPP
#define REACTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t &rectangle);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t &point) override;
  void move(const double deltaX, const double deltaY) override;

private:
  rectangle_t rectangle_;
};

#endif
