#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t & center, const double w, const double h):
  myRec_{w, h, center}
{
  if ((w < 0.0) || (h < 0.0))
  {
    throw std::invalid_argument("Width and height must be greater than 0.");
  }
}

double Rectangle::getArea() const
{
  return myRec_.width * myRec_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return myRec_;
}

void Rectangle::move(const point_t & newPos)
{
  myRec_.pos = newPos;
}

void Rectangle::move(const double dx, const double dy)
{
  myRec_.pos.x += dx;
  myRec_.pos.y += dy;
}
