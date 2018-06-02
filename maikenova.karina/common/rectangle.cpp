#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>

maikenova::Rectangle::Rectangle(const point_t & center, const double w, const double h):
  myRec_{w, h, center},
  angle_(0)
{
  if ((w < 0.0) || (h < 0.0))
  {
    throw std::invalid_argument("Width and height must not be negative.");
  }
}

double maikenova::Rectangle::getArea() const
{
  return myRec_.width * myRec_.height;
}

maikenova::rectangle_t maikenova::Rectangle::getFrameRect() const
{

  const double phi = angle_*M_PI/180;
  const double width = myRec_.height * fabs(sin(phi)) + myRec_.width * fabs(cos(phi));
  const double height = myRec_.height  * fabs(cos(phi)) + myRec_.width * fabs(sin(phi));

  return {width, height, myRec_.pos};
}

void maikenova::Rectangle::move(const point_t & newPos)
{
  myRec_.pos = newPos;
}

void maikenova::Rectangle::move(const double dx, const double dy)
{
  myRec_.pos.x += dx;
  myRec_.pos.y += dy;
}
void maikenova::Rectangle::scale(const double ratio)
{
  if (ratio < 0)
  {
    throw std::invalid_argument("Ratio must not be negative.");
  }
  myRec_.width *= ratio;
  myRec_.height *= ratio;
}

maikenova::point_t maikenova::Rectangle::getPos() const
{
  return myRec_.pos;
}

void maikenova::Rectangle::rotate(double phi)
{
  angle_ += phi;
}

