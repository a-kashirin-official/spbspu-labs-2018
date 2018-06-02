#include "circle.hpp"
#include <cmath>
#include <iostream>

using namespace golyshev;

golyshev::Circle::Circle(double rad, const point_t &poss) :
  radius_(rad),
  center_(poss)
{
  if (rad < 0) {
    throw std::invalid_argument("Radius of the circle must be > 0!");
  }
}

double golyshev::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

golyshev::rectangle_t golyshev::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void golyshev::Circle::move(const point_t &poss)
{
  center_ = poss;
}

void golyshev::Circle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void golyshev::Circle::scale(double coeff)
{
  if (coeff < 0) {
    throw std::invalid_argument("Scale coefficient of the circle must be > 0!");
  }
  radius_ *= coeff;
}

void golyshev::Circle::OutInf() const
{
  std::cout << "Center( " << center_.x << " ; " << center_.y << " )" << std::endl;
  std::cout << "Width:  " << getFrameRect().width << std::endl;
  std::cout << "Height: " << getFrameRect().height << std::endl;
  std::cout << "Area:   " << getArea() << std::endl;
  std::cout << "_____________________ " << std::endl;
}

void golyshev::Circle::rotate(const double /*angle*/)
{

}
