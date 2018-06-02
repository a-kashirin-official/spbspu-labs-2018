#include "circle.hpp"
#include <stdexcept>
#include <cmath>

kahuanahil::Circle::Circle(const double r, const kahuanahil::point_t &point):
  m_r(r),
  m_center(point),
  m_angle(0.0)
{
  if (m_r < 0.0)
  {
    throw std::invalid_argument("Invalid value");
  }
}

kahuanahil::point_t kahuanahil::Circle::getCenter() const noexcept
{
  return m_center;
}

double kahuanahil::Circle::getArea() const noexcept
{
  return M_PI * m_r * m_r;
}

kahuanahil::rectangle_t kahuanahil::Circle::getFrameRect() const noexcept
{
  return {2 * m_r, 2 * m_r, m_center};
}

void kahuanahil::Circle::move(const double dx, const double dy) noexcept
{
  m_center.x += dx;
  m_center.y += dy;
}

void kahuanahil::Circle::move(const point_t &position) noexcept
{
  m_center = position;
}

double kahuanahil::Circle::getAngle() const noexcept
{
  return m_angle;
}

void kahuanahil::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid value");
  }
  m_r *= factor;
}

void kahuanahil::Circle::rotate(const double angle) noexcept
{
  m_angle += angle;
}
