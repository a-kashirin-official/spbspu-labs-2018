#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const rectangle_t &rect_init):
  m_rect(rect_init)
{
  assert((m_rect.width >= 0) && (m_rect.height >= 0));

}

double Rectangle::getArea() const
{
  return m_rect.height * m_rect.width;
}
rectangle_t Rectangle::getFrameRect() const
{
  return m_rect;
}

void Rectangle::move(const point_t & newpos)
{
  m_rect.pos = newpos;
}

void Rectangle::move(double dx, double dy)
{
  m_rect.pos.x += dx;
  m_rect.pos.y += dy;
}
