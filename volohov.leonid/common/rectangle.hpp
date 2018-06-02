#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace volohov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t & center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(const double coeff) override;
    void move(const point_t & newCenter) override;
    void move(const double dx, const double dy) override;

  private:
    point_t center_;
    double width_;
    double height_;

  };
}
#endif //RECTANGLE_HPP
