#ifndef A2_RECTANGLE_HPP
#define A2_RECTANGLE_HPP
#include "shape.hpp"

namespace khmyrov
{
  class Rectangle:public Shape
  {
  private:
    double width_;
    double height_;

  public:
    Rectangle(const point_t & pos, const double width, const double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double coeff) override;
  };
}

#endif //A2_RECTANGLE_HPP
