#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include <iostream>

namespace volkov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & pos, double width, double height);
    friend std::ostream & volkov::operator<<(std::ostream & out, const Rectangle & rect);
    double getWidth() const;
    double getHeight() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move (const point_t & pos) override;
    void scale(const double f) override;

  private:
    point_t pos_;
    double width_, height_;
  };

  std::ostream & operator <<(std::ostream & out, const Rectangle & rect);
}

#endif // RECTANGLE_HPP
