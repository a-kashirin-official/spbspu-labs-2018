#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>
using namespace babintseva;

Rectangle::Rectangle(const point_t &position, const double width, const double height):
    corners_{{position.x - width / 2, position.y + height / 2},
             {position.x + width / 2, position.y + height / 2},
             {position.x + width / 2, position.y - height / 2},
             {position.x - width / 2, position.y - height / 2}},

    width_(width),
    height_(height) {
  if (width < 0.0) {
    throw std::invalid_argument("Width must be >= 0!");
  }

  if (height < 0.0) {
    throw std::invalid_argument("Height must be >= 0!");
  }
}
bool babintseva::operator==(const Rectangle &rect1, const Rectangle &rect2)
{
  for (size_t i = 0; i < 4; i++)
  {
    if (rect1.corners_[i].x != rect2.corners_[i].x ||
        rect1.corners_[i].y != rect2.corners_[i].y)
    {
      return false;
    }
  }
  if (rect1.width_ == rect2.width_ &&
      rect1.height_ == rect2.height_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::string Rectangle::getName() const
{
  return "Rectangle";
}

double Rectangle::getArea() const
{
  return (width_ * height_);
}

rectangle_t Rectangle::getFrameRect() const
{
  point_t center = {(corners_[0].x + corners_[2].x) / 2, (corners_[0].y + corners_[2].y) / 2};

  point_t top_left = center;
  point_t bottom_right = center;

  for (size_t i = 0; i < 4; i++)
  {
    if (corners_[i].x < top_left.x)
    {
      top_left.x = corners_[i].x;
    }

    if (corners_[i].y > top_left.y)
    {
      top_left.y = corners_[i].y;
    }

    if (corners_[i].x > bottom_right.x)
    {
      bottom_right.x = corners_[i].x;
    }

    if (corners_[i].y < bottom_right.y)
    {
      bottom_right.y = corners_[i].y;
    }
  }

  return {center, bottom_right.x - top_left.x, top_left.y - bottom_right.y};
}

void Rectangle::move(const point_t &pos)
{
  point_t center = getFrameRect().pos;
  move(pos.x - center.x, pos.y - center.y);
}

void Rectangle::move(const double dx, const double dy)
{
  for (size_t i = 0; i < 4; i++)
  {
    corners_[i].x += dx;
    corners_[i].y += dy;
  }
}

void Rectangle::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Ratio can't be < 0!");
  }

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < 4; i++)
  {
    corners_[i] = {center.x + ratio * (corners_[i].x - center.x), center.y + ratio * (corners_[i].y - center.y)};
  }

  width_ *= ratio;
  height_ *= ratio;
}

void Rectangle::rotate(double angle)
{
  angle = angle * M_PI / 180;

  double angle_cos = cos(angle);
  double angle_sin = sin(angle);

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < 4; i++)
  {
    corners_[i] = {center.x + angle_cos * (corners_[i].x - center.x) - angle_sin * (corners_[i].y - center.y),
                   center.y + angle_cos * (corners_[i].y - center.y) + angle_sin * (corners_[i].x - center.x)};
  }
}

double Rectangle::getHeight()
{
  return height_;
}

double Rectangle::getWidth()
{
  return width_;
}

point_t Rectangle::getPos() const
{
  return getFrameRect().pos;
}
