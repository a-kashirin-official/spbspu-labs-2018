#ifndef RECTANGLE
#define RECTANGLE
#include "base-types.hpp"
#include "shape.hpp"

class Rectangle : public Shape {
public:
  Rectangle ( const double Nwidth, const double Nheight, const point_t & center );

  double getArea() const ;
  rectangle_t getFrameRect() const ;
  void move(const point_t & resPoint) ;
  void move(const double dx, const double dy) ;
  void printRect() const;

private:
    rectangle_t rect_;
};

#endif // RECTANGLE

