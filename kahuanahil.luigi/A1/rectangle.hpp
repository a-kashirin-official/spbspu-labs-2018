#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape 
{
public:
  Rectangle(const double width, const double height, const point_t &pos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move(const double x, const double y) override;
  point_t getCenter() const;
private:
  point_t m_center;
  double m_width, m_height;
};
#endif
