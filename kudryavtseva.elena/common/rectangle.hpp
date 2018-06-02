#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace kudryavtseva
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t &rectCenter, const double w, const double h);
    double getArea () const override;
    rectangle_t getFrameRect () const override;
    void move(double dx, double dy) override;
    void move(const point_t &center) override;
    void scale(const double k) override;
    void rotate(double angle) override;
    point_t getPos() const override;
    void printf() const override;
    double getHeight () const;
    double getWidth () const;
  private:
    point_t centerRec_;
    double width_;
    double height_;
    point_t p[4];
  };
}

#endif
