#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace stankeviciute;

Circle::Circle(const point_t &pos, double radius):
  pos_(pos),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("invalid_radius");
  }
}

bool stankeviciute::operator==(const Circle &circle_1, const Circle &circle_2)
{
  if (circle_1.pos_.x == circle_2.pos_.x &&
    circle_1.pos_.y == circle_2.pos_.y &&
    circle_1.radius_ == circle_2.radius_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

double Circle::getRadius() const
{
  return radius_;
}

std::string Circle::getName() const
{
  return "circle";
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::printFeatures() const
{
  std::cout << "x: " << pos_.x << "\n"
    << "y: " << pos_.y << "\n"
    << "radius: " << radius_ << "\n";
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}

void Circle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("invalid_scale");
  }
  
  radius_ *= k;
}
