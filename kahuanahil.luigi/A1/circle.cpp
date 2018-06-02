#include "circle.hpp"
#include <stdexcept>
#include <math.h>

Circle::Circle(const double r, const point_t &point) :
  m_r(r), m_center(point)
{
  if (m_r <= 0){
    throw std::invalid_argument("Invalid value");
  }
}

point_t Circle::getCenter() const
{
  return m_center;
}

double Circle::getArea() const
{
  return(M_PI * m_r * m_r);
}

rectangle_t Circle::getFrameRect() const
{
  return { m_center.x, m_center.y, 2 * m_r, 2 * m_r };
}

void Circle::move(const double dx, const double dy)
{
  m_center.x += dx;
  m_center.y += dy;
}

void Circle::move(const point_t &pos)
{
  m_center = pos;
}



