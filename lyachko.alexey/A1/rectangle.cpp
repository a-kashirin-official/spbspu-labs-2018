#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t & new_center) : 
 m_rectangle(new_center)
{
  if ((m_rectangle.width <= 0.0) || (m_rectangle.height <= 0.0))
  {
    throw std::invalid_argument("Height and Width must be greater than 0");
  }
}

double Rectangle::getArea() const
{
  return m_rectangle.width * m_rectangle.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return m_rectangle;
}

void Rectangle::move(double dx, double dy)
{
  m_rectangle.pos.x += dx;
  m_rectangle.pos.y += dy;
}

void Rectangle::move(const point_t & new_cord)
{
  m_rectangle.pos = new_cord;
}
