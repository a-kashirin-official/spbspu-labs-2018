#ifndef STARIKOV_ANDREY_LABS_CIRCLE_HPP
#define STARIKOV_ANDREY_LABS_CIRCLE_HPP

#include "shape.hpp"

class Circle:public Shape
{
public:
  Circle(const double &radius, const point_t centre);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &centre) override;
  void move(const double offsetAxisX, const double offsetAxisY) override;
private:
  double radius_;
  point_t centre_;
  point_t constCentre_;
};

#endif //STARIKOV_ANDREY_LABS_CIRCLE_HPP
