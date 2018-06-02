#ifndef STARIKOV_ANDREY_LABS_RECTANGLE_HPP
#define STARIKOV_ANDREY_LABS_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const rectangle_t modelRect);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &centre) override;
  void move(const double offsetAxisX, const double offsetAxisY) override;
private:
  rectangle_t modelRect_;
  point_t constCentre_;
};

#endif //STARIKOV_ANDREY_LABS_RECTANGLE_HPP
