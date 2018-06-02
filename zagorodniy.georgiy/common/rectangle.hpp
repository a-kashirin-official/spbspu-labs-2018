#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace zagorodniy {
  class Rectangle :
    public Shape {
  public:
    Rectangle(const point_t &Center, double wdt, double hgh);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newCenter) override;
    void move(double dx, double dy) override;
    void scale(double coef) override;

  private:
    point_t pos_;
    double width_;
    double height_;
  };
}

#endif
