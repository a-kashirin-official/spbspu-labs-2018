#include "rectangle.hpp"
#include <cmath>
#include <cassert>
#include <stdexcept>

shapovalova::Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect),
  angle_(0.0)
{
  if ((rect.width < 0.0) || (rect.height < 0.0))
  {
    throw std::invalid_argument("Invalid rectangle height or width");
  }
  vertex_[0] = {rect_.pos.x + rect_.width / 2, rect_.pos.y + rect_.height / 2}; //right top
  vertex_[1] = {rect_.pos.x - rect_.width / 2, rect_.pos.y + rect_.height / 2}; //left top
  vertex_[2] = {rect_.pos.x - rect_.width / 2, rect_.pos.y - rect_.height / 2}; //left bottom
  vertex_[3] = {rect_.pos.x + rect_.width / 2, rect_.pos.y - rect_.height / 2}; //right bottom
}

double shapovalova::Rectangle::getArea() const noexcept
{
  return rect_.height * rect_.width;
}

shapovalova::rectangle_t shapovalova::Rectangle::getFrameRect() const noexcept
{
  double right = vertex_[0].x;
  double left = vertex_[0].x;
  double top = vertex_[0].y;
  double bottom = vertex_[0].y;
  for (int i =1; i < 4; i++)
  {
    if (vertex_[i].x > right)
    {
      right = vertex_[i].x;
    }
    if (vertex_[i].x < left)
    {
      left = vertex_[i].x;
    }
    if (vertex_[i].y > top)
    {
      top = vertex_[i].y;
    }
    if (vertex_[i].y < bottom)
    {
      bottom = vertex_[i].y;
    }
  }
  return {{((right + left) / 2), ((top + bottom) / 2)}, (right - left), (top - bottom)};
}

void shapovalova::Rectangle::move(const point_t & posTo) noexcept
{
  for (int i = 0; i < 4; i++)
  {
    vertex_[i].x += posTo.x - rect_.pos.x;
    vertex_[i].y += posTo.y - rect_.pos.y;
  }
  rect_.pos = posTo;
}

void shapovalova::Rectangle::move(const double dx, const double dy) noexcept
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
  for (int i = 0; i < 4; i++)
  {
    vertex_[i].x += dx;
    vertex_[i].y += dy;
  }
}
void shapovalova::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument ("Invalid parameter of scaling");
  }
  rect_.width *= coefficient;
  rect_.height *= coefficient;
  vertex_[0] = {rect_.pos.x + rect_.width / 2, rect_.pos.y + rect_.height / 2};
  vertex_[1] = {rect_.pos.x - rect_.width / 2, rect_.pos.y + rect_.height / 2};
  vertex_[2] = {rect_.pos.x - rect_.width / 2, rect_.pos.y - rect_.height / 2};
  vertex_[3] = {rect_.pos.x + rect_.width / 2, rect_.pos.y - rect_.height / 2};
}

void shapovalova::Rectangle::rotate(const double degrees) noexcept
{
  double sinValue = sin(degrees * M_PI / 180);
  double cosValue = cos(degrees * M_PI / 180);
  shapovalova::point_t center = getFrameRect().pos;
  for (int i = 0; i < 4; i++)
  {
    double newX = center.x + (vertex_[i].x - center.x) * cosValue -
        - (vertex_[i].y - center.y) * sinValue;
    double newY = center.y + (vertex_[i].x - center.x) * sinValue +
        + (vertex_[i].y - center.y) * cosValue;
    vertex_[i] = {newX, newY};
  }
}
