#ifndef CIRCLE
#define CIRCLE
#include "base-types.hpp"
#include "shape.hpp"

class Circle : public Shape {
public:
  Circle (const point_t & Ncenter, const double Nradius);

  double getArea() const ;
  rectangle_t getFrameRect() const ;
  void move(const point_t & resPoint) ;
  void move(const double dx, const double dy) ;
  void printCircle() const;

private:
  point_t center_;
  double radius_;
};
#endif // CIRCLE

