#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace stashevskii
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t& point);
    rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t &point) override;
    void scale(const double k) override;
    void printf() const;
    point_t getPosition() const  override;
    void rotate(const double angle) override;

  private:
    double width_;
    double height_;
    point_t pos;
    point_t p_a_;
    point_t p_b_;
    point_t p_c_;
    point_t p_d_;
  };
}

#endif
