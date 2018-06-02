#include <iostream>
#include <cassert>
#include "rectangle.hpp"

Rectangle::Rectangle(const rectangle_t & rect):
  m_rect(rect)
{
  assert ((rect.height >= 0.0)&&(rect.width >= 0.0));
}

double Rectangle::getArea() const
{
  return (m_rect.width * m_rect.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return m_rect;
}

void Rectangle::move(const double dx, const double dy)
{
  m_rect.pos.x += dx;
  m_rect.pos.y += dy;
}

void Rectangle::move(const point_t & newPos)
{
  m_rect.pos = newPos;
}
