#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

namespace mihajlov
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& centerPos, const double r);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& centerPos) override;
    void move(const double shiftX, const double shiftY) override;
    void getInfo() const override;
    void printName() const override;
    void scale(const double multiplier) override;
    void rotate(const double angle) override;
  private:
    point_t pos_;
    double radius_;
    double angle_;
  };
}

#endif //A1_CIRCLE_HPP
