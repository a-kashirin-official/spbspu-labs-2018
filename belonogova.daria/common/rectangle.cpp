#include "rectangle.hpp"
#include <iostream>
#include <cmath>

using namespace belonogova;

Rectangle::Rectangle(const rectangle_t & rect):
  m_rect(rect),
  m_angle(0)
{
  if (rect.height < 0.0) {
    throw std::invalid_argument("Wrong height");
  }
  if (rect.width < 0.0) {
    throw std::invalid_argument("Wrong width");
  }
}

double Rectangle::getArea() const
{
  return (m_rect.width * m_rect.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  //Rectangle coordinates when it becomes rotated on m_angle:
  double left_top_x =
      m_rect.pos.x - (m_rect.width / 2) * cos(m_angle * M_PI / 180) - (m_rect.height / 2) * sin(m_angle * M_PI / 180);
  double left_bottom_y =
      m_rect.pos.y - (m_rect.height / 2) * cos(m_angle * M_PI / 180) - (m_rect.width / 2) * sin(m_angle * M_PI / 180);
  double right_top_y =
      m_rect.pos.y + (m_rect.height / 2 ) * cos(m_angle * M_PI / 180) + (m_rect.width / 2) * sin(m_angle * M_PI / 180);
  double right_bottom_x =
      m_rect.pos.x + (m_rect.width / 2) * cos(m_angle * M_PI / 180) + (m_rect.height / 2) * sin(m_angle * M_PI / 180);

  double frameWidth = std::abs(right_bottom_x - left_top_x);
  double frameHeight = std::abs(left_bottom_y - right_top_y);

  return {frameWidth, frameHeight,
         {m_rect.pos} };
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

void Rectangle::scale(const double coef)
{
  if (coef < 0.0) {
    throw std::invalid_argument("Wrong coef");
  }
  m_rect.width *= coef;
  m_rect.height *= coef;
}

void Rectangle::rotate(const double alfa)
{
  m_angle+=alfa;
  while (m_angle > 180) {
    m_angle -= 360;
  };
  while (m_angle < -180) {
    m_angle += 360;
  };
}
