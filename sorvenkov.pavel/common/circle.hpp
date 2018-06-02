#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace sorvenkov
{
  class Circle: public Shape
  {
  public:
    Circle(double radius, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double Ox, double Oy) override;
    void scale(double ratio) override;
  private:
    double radius_;
    point_t center_;

  };
}
#endif
