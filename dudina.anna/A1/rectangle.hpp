#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle :
  public Shape
{
public:
  Rectangle(const point_t & pos, const double width, const double height);
  virtual double getArea() const override;
  virtual rectangle_t getFrameRect() const override;
  virtual void move(const point_t & pos) override;
  virtual void move(double dx, const double dy) override;
  void printInformation() override;

private:
  point_t pos_;
  double width_;
  double height_;

};
#endif // !RECTANGLE_HPP
