#include "rectangle.hpp"
#include <stdexcept>


Rectangle::Rectangle(double width, double height, const point_t & point) :
  m_width(width),
  m_height(height),
  m_centre(point),
  rect_({width,height,point})
{
  if ((m_width < 0.0) || (m_height < 0.0))
  {
    throw std::invalid_argument("Incorrect value");
  }
}

double Rectangle::getWidth() const
{
  return m_width;
}

double Rectangle::getHeight() const
{
  return m_height;
}

point_t Rectangle::getCentre() const
{
  return m_centre;
}

double Rectangle::getArea() const
{
  return(m_width*m_height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(double dx, double dy)
{
  m_centre.x += dx;
  m_centre.y += dy;
}

void Rectangle::move(const point_t & p)
{
  m_centre.x = p.x;
  m_centre.y = p.y;
}
