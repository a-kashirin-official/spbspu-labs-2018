#include "shape.hpp"
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle : public Shape
{
  public:
    Rectangle(const double width, const double height, const point_t &pos);
    rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const point_t &point) override;
    void move(const double dx, const double dy) override;

  private:
      double width_;
      double height_;
      point_t center_;
};

#endif
