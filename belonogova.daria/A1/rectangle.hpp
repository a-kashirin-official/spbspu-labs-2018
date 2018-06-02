#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape 
{
public:
  Rectangle(const rectangle_t & rect);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t & newPos) override;
private:
  rectangle_t m_rect;
};
#endif //RECTANGLE_HPP
