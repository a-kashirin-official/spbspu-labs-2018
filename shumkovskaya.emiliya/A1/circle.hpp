#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const double r, const point_t & p);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move (const double dx,const double dy) override;
  void move (const point_t & p) override;
  void printParameters() const;
  void printCenter() const;
private:  
  const double radius_;
  point_t pos_;
};

#endif
