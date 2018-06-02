#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace shumkovskaya

{
  class Rectangle : public Shape  
{
  public:
    Rectangle(double w, double h, const point_t & p);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t & p) override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
  private:
    double width_;
    double height_;
    point_t pos_;
    double angle_;
  };
}

#endif
