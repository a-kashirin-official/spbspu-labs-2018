#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace maikenova
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t & center, const double w, const double h);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPos) override;
    void move(const double dx, const double dy) override;
    void scale(const double ratio) override;
    point_t getPos() const override;
    void rotate(double phi) override;
  private:
    rectangle_t myRec_;
    double angle_;
  };
}


#endif //RECTANGLE_HPP
