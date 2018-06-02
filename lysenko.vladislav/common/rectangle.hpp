#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace lysenko
{
  class Rectangle: public Shape {
  public:
    Rectangle(const point_t &rect, const double width, const double heigth);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &center) override;
    void move(const double dx, const double dy) override;
    virtual void scale(const double dk) override;
  private:
    point_t center_;
    double width_;
    double heigth_;
  };
}
#endif
