#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

  class Rectangle:public Shape
  {
  public:
    Rectangle(const rectangle_t widthHeightPos);
    double getArea() const;
    rectangle_t getFrameRect() const;
    void move(const point_t &poss);
    void move(const double xOffset, const double yOffset);
  private:
    double width_, height_;
    point_t center_;
  };

#endif //VLASOV_DMITRY_LABS_RECTANGLE_HPP
