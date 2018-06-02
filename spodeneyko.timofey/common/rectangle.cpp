#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

spodeneyko::Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if ((rect_.height < 0.0) || (rect_.width < 0.0))
  {
    throw std::invalid_argument("Error. Invalid height or width of rectangle.");
  }
  vertex_[0] = {rect_.pos.x - rect_.width / 2, rect_.pos.y + rect_.height / 2};
  vertex_[1] = {rect_.pos.x + rect_.width / 2, rect_.pos.y + rect_.height / 2};
  vertex_[2] = {rect_.pos.x + rect_.width / 2, rect_.pos.y - rect_.height / 2};
  vertex_[3] = {rect_.pos.x - rect_.width / 2, rect_.pos.y - rect_.height / 2};
}

double spodeneyko::Rectangle::getArea() const noexcept
{
  return (rect_.width * rect_.height);
}

spodeneyko::rectangle_t spodeneyko::Rectangle::getFrameRect() const noexcept
{
  double leftSide = vertex_[0].x;
  double rightSide = vertex_[0].x;
  double topSide = vertex_[0].y;
  double bottomSide = vertex_[0].y;
  for (int i = 1; i < 4; ++i)
  {
    if (leftSide > vertex_[i].x)
    {
      leftSide = vertex_[i].x;
    }
    if (rightSide < vertex_[i].x)
    {
      rightSide = vertex_[i].x;
    }
    if (topSide < vertex_[i].y)
    {
      topSide = vertex_[i].y;
    }
    if (bottomSide > vertex_[i].y)
    {
      bottomSide = vertex_[i].y;
    }
  }
  return {rightSide - leftSide, topSide - bottomSide, {(rightSide + leftSide) / 2, (bottomSide + topSide) / 2}};
}

std::string spodeneyko::Rectangle::getName() const noexcept
{
  return "Rectangle";
}

void spodeneyko::Rectangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling.");
  }
  rect_.width *= factor;
  rect_.height *= factor;
  vertex_[0] = {rect_.pos.x - rect_.width / 2, rect_.pos.y + rect_.height / 2};
  vertex_[1] = {rect_.pos.x + rect_.width / 2, rect_.pos.y + rect_.height / 2};
  vertex_[2] = {rect_.pos.x + rect_.width / 2, rect_.pos.y - rect_.height / 2};
  vertex_[3] = {rect_.pos.x - rect_.width / 2, rect_.pos.y - rect_.height / 2};
}

void spodeneyko::Rectangle::move(const point_t & point) noexcept
{
  rect_.pos = point;
}

void spodeneyko::Rectangle::move(const double dx, const double dy) noexcept
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
  for (int i = 0; i < 4; ++i)
  {
    vertex_[i].x += dx;
    vertex_[i].y += dy;
  }
}

void spodeneyko::Rectangle::rotate(const double angle) noexcept
{
  const double cosA = cos(angle * M_PI / 180);
  const double sinA = sin(angle * M_PI / 180);
  vertex_[0] = {rect_.pos.x + (vertex_[0].x - rect_.pos.x) * cosA - (vertex_[0].y - rect_.pos.y) * sinA,
      rect_.pos.y + (vertex_[0].x - rect_.pos.x) * sinA + (vertex_[0].y - rect_.pos.y) * cosA};
  vertex_[1] = {rect_.pos.x + (vertex_[1].x - rect_.pos.x) * cosA - (vertex_[1].y - rect_.pos.y) * sinA,
      rect_.pos.y + (vertex_[1].x - rect_.pos.x) * sinA + (vertex_[1].y - rect_.pos.y) * cosA};
  vertex_[2] = {rect_.pos.x + (vertex_[2].x - rect_.pos.x) * cosA - (vertex_[2].y - rect_.pos.y) * sinA,
      rect_.pos.y + (vertex_[2].x - rect_.pos.x) * sinA + (vertex_[2].y - rect_.pos.y) * cosA};
  vertex_[3] = {rect_.pos.x + (vertex_[3].x - rect_.pos.x) * cosA - (vertex_[3].y - rect_.pos.y) * sinA,
      rect_.pos.y + (vertex_[3].x - rect_.pos.x) * sinA + (vertex_[3].y - rect_.pos.y) * cosA};
}
