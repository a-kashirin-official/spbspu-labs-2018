#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include <iostream>

namespace gubenko
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & pos, double width, double height);
    friend std::ostream & gubenko::operator <<(std::ostream & out, const Rectangle & r);
    double getWidth() const;
    double getHeight() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move (const point_t & pos) override;
    void scale(double n) override;

  private:
    point_t pos_;
    double width_, height_;
  };

  std::ostream & operator <<(std::ostream & out, const Rectangle & r);
}

#endif // RECTANGLE_HPP
