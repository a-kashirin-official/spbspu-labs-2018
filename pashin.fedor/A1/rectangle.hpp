#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <string>
#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t& center, double width, double height);
  std::string getInfo() const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& new_center) override;
  void move(double dx, double dy) override;

private:
  point_t center_;
  double width_;
  double height_;
};

#endif  // RECTANGLE_HPP
