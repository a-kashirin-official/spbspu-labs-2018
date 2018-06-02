#include "shape.hpp"

class Rectangle:public Shape
{
public:
  Rectangle(const double width,const double height,const point_t &poss);
  double getArea() const;
  rectangle_t getFrameRect() const ;
  void move(const point_t &poss);
  void move(const double Ox, double Oy);
  void info() const;

private:
  double width_;
  double height_;
  point_t center_;

};
