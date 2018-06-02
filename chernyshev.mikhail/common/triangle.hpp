#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include <cstdlib>
#include "shape.hpp"
#include "base-types.hpp"

namespace chernyshev
{
  class Triangle : public Shape
  {
  public:
    Triangle(point_t a ,point_t b ,point_t c);
    double getArea()const override;
    rectangle_t getFrameRect()const override;
    void Move(double delta_x,double delta_y) override;
    void Move(point_t newPoint) override;
    void scale(double size) override;//koeff- коэффициент увеличения(уменьшения) фигуры
    void printScale()const override;//для вывода данных
  private:
    point_t center_;
    point_t a_;
    point_t b_;
    point_t c_;    
  };
}
#endif
