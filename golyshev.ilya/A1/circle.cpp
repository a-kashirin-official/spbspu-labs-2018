#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(double rad, const point_t &poss) :
  radius_(rad),
  center_(poss)
{
  if (rad < 0) {
    std::cerr << "Radius of the circle must be > 0!" << std::endl;
  }
  radius_ = rad;
  center_ = poss;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t &poss)
{
  center_ = poss;
}

void Circle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void Circle::OutInf() const
{
  std::cout << "Center( " << center_.x << " ; " << center_.y << " )" << std::endl;
  std::cout << "Width:  " << getFrameRect().width << std::endl;
  std::cout << "Height: " << getFrameRect().height << std::endl;
  std::cout << "Area:   " << getArea() << std::endl;
  std::cout << "_____________________ " << std::endl;
}
