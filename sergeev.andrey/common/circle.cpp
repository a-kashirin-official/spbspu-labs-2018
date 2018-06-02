#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace sergeev;

Circle::Circle(const point_t &center, double r):
  m_center(center), m_radius(r)
{
  if(m_radius < 0.0)
  {
    throw std::invalid_argument("Wrong radius!");
  }
}

double Circle::getArea() const
{
  return {M_PI * m_radius * m_radius};
}

rectangle_t Circle::getFrameRect() const
{
  return {m_center, m_radius * 2, m_radius * 2};
}

void Circle::move(const point_t &point)
{
  m_center = point;
}

void Circle::move(double dx, double dy)
{
  m_center.x += dx;
  m_center.y += dy;
}

void Circle::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Wrong scale factor!");
  }
  m_radius *= factor;
}

void Circle::rotate(double /* angle */)
{}
