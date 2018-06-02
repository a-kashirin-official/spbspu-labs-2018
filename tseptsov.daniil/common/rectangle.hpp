#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace tseptsov
{

  class Rectangle : public tseptsov::Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t &pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newpos) override;
    void move(const double Ox, double Oy) override;
    void OutData() const override;
    void scale(double coef) override;
    void rotate(double deg) override;
    point_t getCenter() const override;
  private:
    point_t vertexes_[4];
    double getDistance(const point_t & p1, const point_t & p2) const;


  };
}


#endif

