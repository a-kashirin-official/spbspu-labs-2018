#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

namespace mihajlov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& centerPos, const double height, const double width);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& centerPos) override;
    void move(const double shiftX, const double shiftY) override;
    void getInfo() const override;
    void printName() const override;
    void scale(const double multiplier) override;
    void rotate(const double angle) override;
  private:
    rectangle_t data_;
    double angle_;
  };
}

#endif //A1_RECTANGLE_HPP
