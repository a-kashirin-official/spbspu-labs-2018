#include "rectangle.hpp"
#include <stdexcept>
#include <math.h>

kahuanahil::Rectangle::Rectangle(const double width,const double height, const point_t &pos):
  m_width(width),
  m_height(height),
  m_center(pos),
  m_angle(0.0)
{
  if (m_width < 0.0)
  {
    throw std::invalid_argument("Invalid value");
  }
  if (m_height < 0.0)
  {
    throw std::invalid_argument("Invalid value");
  }
}

double kahuanahil::Rectangle::getArea() const noexcept
{
  return (m_width * m_height);
}

double kahuanahil::Rectangle::getAngle() const noexcept
{
  return m_angle;
}

kahuanahil::point_t kahuanahil::Rectangle::getCenter() const noexcept
{
  return m_center;
}

kahuanahil::rectangle_t kahuanahil::Rectangle::getFrameRect() const noexcept
{
  const double width_ = (m_width * abs(cos(m_angle * M_PI / 180.0))) + (m_height * abs(sin(m_angle * M_PI / 180.0)));
  const double height_ = (m_width * abs(sin(m_angle * M_PI / 180.0))) + (m_height * abs(cos(m_angle * M_PI / 180.0)));
  return { width_, height_, m_center};
}

void kahuanahil::Rectangle::move(const point_t &pos) noexcept
{
  m_center = pos;
}

void kahuanahil::Rectangle::move( const double dx, const double dy) noexcept
{
  m_center.x += dx;
  m_center.y += dy;
}

void kahuanahil::Rectangle::scale( const double factor)
{
  if (factor < 0.0 )
  {
    throw std::invalid_argument("Invalid value");
  }
  m_width *= factor;
  m_height *= factor;
}

void kahuanahil::Rectangle::rotate(const double angle) noexcept
{
  m_angle += angle;
}
