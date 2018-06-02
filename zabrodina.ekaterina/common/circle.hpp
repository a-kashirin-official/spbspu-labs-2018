#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace zabrodina
{
  class Circle: public Shape
  {
  public:
    Circle(const zabrodina::point_t &pos, const double r);
    zabrodina::rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const zabrodina::point_t &pos) override;
    void move(const double Ox, const double Oy) override;
    void printInf() const override;
    void scale(const double coefficient) override;
  private:
    zabrodina::point_t center_;
    double radius_;
};
}

#endif 
