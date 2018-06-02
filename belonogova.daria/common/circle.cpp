#include "circle.hpp"
#include <cmath>
#include <iostream>

using namespace belonogova;

Circle::Circle(const double newRad, const point_t & newPos) :
  m_rad (newRad),
  m_pos (newPos)
{
  if (newRad < 0.0) {
    throw std::invalid_argument("Wrong radius");
  }
}

double Circle::getArea() const
{
  return(M_PI*m_rad*m_rad);
}

rectangle_t Circle::getFrameRect() const
{
  return {(m_rad*2), (m_rad*2), m_pos};
}

void Circle::move(const double dx, const double dy)
{
  m_pos.x += dx;
  m_pos.y += dy;
}

void Circle::move(const point_t & newPos)
{
  m_pos = newPos;
}

void Circle::scale(const double coef)
{
  if (coef < 0.0) {
    throw std::invalid_argument("Wrong coef");
  }
  m_rad *= coef;
}

void Circle::rotate(const double /*alfa*/)
{
  
}
