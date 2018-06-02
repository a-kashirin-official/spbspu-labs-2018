#ifndef CIRCLE
#define CIRCLE
#include "base-types.hpp"
#include "shape.hpp"
namespace shapiev
{
class Circle : public Shape
{
public:
  Circle (const point_t & Ncenter, const double Nradius);
  double getArea() const ;
  rectangle_t getFrameRect() const ;
  void move(const point_t & resPoint);
  void move(const double dx, const double dy);
  void scale(double ratio);
  void printCircle() const;
  point_t getPos() const;
  double getRadius() const;
  void rotate(const double angle);
private:
  point_t center_;
  double radius_;
  double angle_;
};
}
#endif // CIRCLE
