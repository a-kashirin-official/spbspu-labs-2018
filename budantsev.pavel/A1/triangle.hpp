#ifndef AA2_TRIANGLE_HPP
#define AA2_TRIANGLE_HPP

#include "shape.hpp"

class Triangle: public Shape 
{
public:
  Triangle(const point_t &a, const point_t &b, const point_t &c);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(const point_t &poss);
  void move(const double dx,const double dy);
  void info() const;
  point_t getCenterPoint () const;
private:
  point_t a_, b_, c_;
  point_t centre_;

};

#endif //AA2_TRIANGLE_HPP
