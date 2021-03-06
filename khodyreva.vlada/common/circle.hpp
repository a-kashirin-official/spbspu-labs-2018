#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace khodyreva
{
  class Circle: public Shape
  {
  public:
    Circle(const point_t & pos, double radius);
    double getArea() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & pos) override;
    rectangle_t getFrameRect() const override;
    void scale(const double ratio) override;
    void rotate(double /*angle*/) override;
    std::string getName() const override;
  private:
    double radius_;
    point_t pos_;
  };
}

#endif // CIRCLE_HPP
