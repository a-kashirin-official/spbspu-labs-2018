#include "rectangle.hpp"
#include "base-types.hpp"
#include <iostream>
#include <stdexcept>
#include <math.h>


shapiev::Rectangle::Rectangle (const double Nwidth,const double Nheight,const point_t & center):
  rect_({Nwidth, Nheight, center}),
  angle_(0.0)
{
  if (Nwidth < 0.0 || Nheight < 0.0) {
    throw std::invalid_argument("Height and width must be nonnegative");
  }
}

double shapiev::Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

shapiev::rectangle_t shapiev::Rectangle::getFrameRect() const
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  double width = rect_.height * abs(sine) + rect_.width * abs(cosine);
  double height = rect_.height * abs(cosine) + rect_.width * abs(sine);
  return { width, height, rect_.pos };
}

void shapiev::Rectangle::move( const point_t & resPoint)
{
  rect_.pos = resPoint;
}

void shapiev::Rectangle::move(const double dx,const double dy)
{
  rect_.pos.x+= dx;
  rect_.pos.y+= dy;
}

void shapiev::Rectangle::scale(double ratio)
{
  if (ratio < 0.0) {
  throw std::invalid_argument("Ratio must be positive");
  }
  rect_.height *= ratio;
  rect_.width *= ratio;
}

void shapiev::Rectangle::printRect() const
{
  std::cout << "Rectangle has width - " << rect_.width <<", height - " << rect_.height << std::endl;
  std::cout << "  Center is in (" << rect_.pos.x << ", " << rect_.pos.y << ')' << std::endl;
}

double shapiev::Rectangle::getHeight() const
{
  return rect_.height;
}

double shapiev::Rectangle::getWidth() const
{
  return rect_.width;
}

shapiev::point_t shapiev::Rectangle::getPos() const
{
  return rect_.pos;
}

void shapiev::Rectangle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}

