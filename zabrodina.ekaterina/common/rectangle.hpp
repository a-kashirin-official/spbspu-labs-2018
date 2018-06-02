#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"


namespace zabrodina
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const zabrodina::point_t &pos, const double width, const double height);
    zabrodina::rectangle_t getFrameRect() const override;
    double getArea() const override;
    void move(const zabrodina::point_t &pos) override;
    void move(const double Ox, const double Oy) override;
    void printInf() const override;
    void scale(const double coefficient) override;
  private:
    point_t pos_;
    double width_;
    double height_;
  };
}

#endif 
