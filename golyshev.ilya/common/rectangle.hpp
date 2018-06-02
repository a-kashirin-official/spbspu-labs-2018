#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace golyshev
{
  class Rectangle : public golyshev::Shape
  {
  public:
    Rectangle(double width, double height, const point_t &poss);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &poss) override;
    void move(double Ox, double Oy) override;
    void scale(double coeff) override;
    void rotate(const double angle) override;
    void OutInf() const override;


  private:
    double width_;
    double height_;
    point_t center_;
    point_t coordinates[4];
  };
}

#endif
