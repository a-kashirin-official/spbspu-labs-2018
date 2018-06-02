#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
#include <string>

namespace babintseva
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &pos, const double radius);

    friend bool babintseva::operator==(const Circle &cir1, const Circle &cir2);

    double getArea() const override;
    std::string getName() const override;

    rectangle_t getFrameRect() const override;
    point_t getPos() const override;

    void move(const point_t &pos) override;
    void move(const double dx, const double dy) override;

    double getRadius();

    void scale(double ratio) override;

    void rotate(double /*angle*/) override {}

  private:
    point_t pos_;
    double radius_;
  };

  bool operator==(const Circle &cir1, const Circle &cir2);
}

#endif
