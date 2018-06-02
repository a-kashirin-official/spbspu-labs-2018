#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace lobanova {
  class Rectangle : public Shape {
  public:
    Rectangle(const point_t &centre, double width, double height);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &a) override;

    void move(double dx, double dy) override;

    void scale(double p) override;

    void rotate(double p) override;

    void rotatePoint(const point_t &a, double p) override;

    double getWidth() const;

    double getHeight() const;

    point_t getCentre() const;


  private:
    point_t centre_;
    double width_;
    double height_;
    double angle_;

  };
}

#endif //RECTANGLE_HPP
