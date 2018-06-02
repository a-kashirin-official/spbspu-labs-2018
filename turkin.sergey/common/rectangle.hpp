#ifndef A3_RECTANGLE_HPP
#define A3_RECTANGLE_HPP

#include "shape.hpp"

namespace turkin
{
  class Rectangle : public turkin::Shape
  {
  public:
    Rectangle(double width, double height, const point_t &pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double Ox, double Oy) override;
    void printInfo() override;
    void scale(double k) override;
    void rotate(double angle) override;
    point_t getCenter() const override;

  private:
    double width_;
    double height_;
    point_t pnt_[4];

  };
}

#endif
