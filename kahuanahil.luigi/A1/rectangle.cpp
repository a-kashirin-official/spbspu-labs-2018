#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const double width, const double height, const point_t &pos) :
  m_center(pos),
  m_width(width), 
  m_height(height)
{
  if (m_width <= 0)
  {
    throw std::invalid_argument("Invalid value");
  }
  if (m_height <= 0) 
  {
    throw std::invalid_argument("Invalid value");
  }
}

double Rectangle::getArea() const
{
  return (m_width*m_height);
}

point_t Rectangle::getCenter() const
{
  return m_center;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {  m_width, m_height, m_center.x, m_center.y };
}

void Rectangle::move(const point_t &pos)
{
  m_center = pos;
}

void Rectangle::move(const double x, const double y) 
{
  m_center.x += x;
  m_center.y += y;
}



