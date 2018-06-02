#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace tseptsov
{

  class Circle : public tseptsov::Shape
  {
  public:
    Circle(const double rad, const point_t &pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(const double Ox, const double Oy) override;
    void OutData() const override;
    void scale(double coef) override;
    void rotate(double deg) override;
    point_t getCenter() const override;
  private:
    double radius_;
    point_t center_;
    double deg_;
  };
}

#endif

