#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t & set_coordinate_size) :
  coordinate_size_(set_coordinate_size)
{
  if (coordinate_size_.height < 0.0)
  {
    throw std::invalid_argument(" error, height can't be < 0 ");
  }

  if (coordinate_size_.width < 0.0)
  {
    throw std::invalid_argument(" error, weigth can't be < 0 ");
  }
}

double Rectangle::getArea() const
{
  return coordinate_size_.width * coordinate_size_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return coordinate_size_;
}

void Rectangle::move(const point_t & new_center)
{
  coordinate_size_.pos = new_center;
}

void Rectangle::move(const double dx, const double dy)
{
  coordinate_size_.pos.x += dx;
  coordinate_size_.pos.y += dy;
}
