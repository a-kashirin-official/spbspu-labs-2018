#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

namespace lashchenov
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t & center);
    Circle(double radius, double x, double y);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & NewCenter) override;
    void move(double dx, double dy) override;
    void scale(double multiplier) override;
    void rotate(double /*degrees*/) override;
    std::unique_ptr<Shape> getCopy() const override;
    void printInfo() const override;

  private:
    double radius_;
    point_t center_;
  };
}

#endif //A1_CIRCLE_HPP
