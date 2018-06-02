#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : 
  public Shape
{
public:
  Circle(const point_t & pos, const double radius);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & pos) override;
  virtual void move(double dx, double dy) override;
  void printInformation() override;

private:
  point_t pos_;
  double radius_;
};

#endif 
