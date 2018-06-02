#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <string>
#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& center, double radius);
  std::string getInfo() const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& new_center) override;
  void move(double dx, double dy) override;
  
private:
  point_t center_;
  double radius_;
};

#endif  // CIRCLE_HPP
