#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>


Circle::Circle(double radius, const point_t & point) :
  m_radius(radius),
  m_centre(point)
{
  if (m_radius < 0.0)
  {
    throw std::invalid_argument("Incorrect value");
  }
}

point_t Circle::getCentre() const
{
  return m_centre;
}

double Circle::getArea() const
{
  return m_radius*m_radius*M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ m_radius * 2,m_radius * 2,m_centre };
}

void Circle::move(const point_t & p)
{
  m_centre.x = p.x;
  m_centre.y = p.y;
}

void Circle::move(double dx, double dy)
{
  m_centre.x += dx;
  m_centre.y += dy;
}
