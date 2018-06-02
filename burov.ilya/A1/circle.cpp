#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

Circle::Circle(const point_t &center, double r):
  m_center(center), m_radius(r)
{
  assert(m_radius >= 0);

}

double Circle::getArea() const
{
  return {M_PI * m_radius * m_radius};
}

rectangle_t Circle::getFrameRect() const
{
  return { m_center, m_radius * 2, m_radius * 2};
}
void Circle::move(const point_t & newpos)
{
  m_center = newpos;
}
void Circle::move(double dx, double dy)
{
  m_center.x += dx;
  m_center.y += dy;
}
