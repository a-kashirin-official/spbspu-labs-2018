#ifndef RECTANGLE
#define RECTANGLE
#include "base-types.hpp"
#include "shape.hpp"
namespace shapiev
{
class Rectangle : public Shape
{
public:
  Rectangle ( const double Nwidth, const double Nheight, const point_t & center );
  double getArea() const ;
  rectangle_t getFrameRect() const ;
  void move(const point_t & resPoint) ;
  void move(const double dx, const double dy) ;
  point_t getPos() const;
  double getHeight() const;
  double getWidth() const;
  void scale(double ratio);
  void rotate(const double angle);
  void printRect() const;
private:
  rectangle_t rect_;
  double angle_;
};
}
#endif // RECTANGLE
