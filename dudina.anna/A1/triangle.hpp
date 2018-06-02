#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle :
  public Shape
{
public:
  Triangle(const point_t & A, const point_t & B, const point_t & C);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & pos) override;
  virtual void move(double dx, double dy) override;
  void printInformation() override;

private:

  point_t A_;
  point_t B_;
  point_t C_;
  point_t centerpos_;
};

#endif
