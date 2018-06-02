#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace lobanova {

  class Circle : public Shape {
  public:
    Circle(const point_t &centre, double rad);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &a) override;

    void move(double dx, double dy) override;

    void scale(double p) override;

    void rotate(double p) override;

    void rotatePoint(const point_t &a, double p) override;

    double getRadius() const;

  private:
    point_t centre_;
    double rad_;
    double angle_;
  };
}

#endif //CIRCLE_HPP
