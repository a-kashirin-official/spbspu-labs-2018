#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>

using namespace sergeev;

Rectangle::Rectangle(const rectangle_t &rect_init, double angle):
  m_rect(rect_init),
  angle_(angle)
{
  if(m_rect.height < 0.0 || m_rect.width < 0.0)
  {
    throw std::invalid_argument("Wrong height or width!");
  }
}

double Rectangle::getArea() const
{
  return m_rect.height * m_rect.width;
}

rectangle_t Rectangle::getFrameRect() const
{
  point_t leftUp = {-m_rect.width / 2, m_rect.height / 2};
  point_t leftBottom = {-m_rect.width / 2,-m_rect.height / 2};
  point_t rightUp = {m_rect.width / 2, m_rect.height / 2};
  point_t rightBottom = {m_rect.width / 2, -m_rect.height / 2};

  leftUp.rotate(angle_);
  leftBottom.rotate(angle_);
  rightUp.rotate(angle_);
  rightBottom.rotate(angle_);
  
  double leftCoord = std::min(std::min(leftUp.x, leftBottom.x), std::min(rightUp.x, rightBottom.x));
  double rightCoord = std::max(std::max(leftUp.x, leftBottom.x), std::max(rightUp.x, rightBottom.x));
  double bottomCoord = std::min(std::min(leftUp.y, leftBottom.y), std::min(rightUp.y, rightBottom.y));
  double upCoord = std::max(std::max(leftUp.y, leftBottom.y), std::max(rightUp.y, rightBottom.y));

  return { m_rect.pos, rightCoord - leftCoord, upCoord - bottomCoord };

}

void Rectangle::move(const point_t &point)
{
  m_rect.pos = point;
}

void Rectangle::move(double dx, double dy)
{
  m_rect.pos.x += dx;
  m_rect.pos.y += dy;
}

void Rectangle::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Wrong scale factor!");
  }
  m_rect.height *= factor;
  m_rect.width *= factor;
}

void Rectangle::rotate(double angle)
{
  angle_ = std::fmod(angle_ + angle, 360.0);
}
