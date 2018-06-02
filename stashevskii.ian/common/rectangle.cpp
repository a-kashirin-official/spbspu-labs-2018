#include <iostream>
#include "rectangle.hpp"
#include <cmath>

using namespace stashevskii;

Rectangle::Rectangle(const double width, const double height, const point_t& point):
  width_(width),
  height_(height),
  pos(point),
  p_a_({pos.x - width/2, pos.y + height/2}),
  p_b_({pos.x + width/2, pos.y + height/2}),
  p_c_({pos.x + width/2, pos.y - height/2}),
  p_d_({pos.x - width/2, pos.y - height/2})
{
  if ((width < 0.0) || (height < 0.0))
  {
    throw std::invalid_argument ("Height and Width must be > 0!");
  }
}

rectangle_t Rectangle::getFrameRect() const
{
  return{ width_, height_, pos};
}

double Rectangle::getArea() const
{
  return(width_ * height_);
}

void Rectangle::move(const double dx, const double dy)
{
  pos.x += dx;
  pos.y += dy;
  p_a_.x += dx;
  p_a_.y += dy;
  p_b_.x += dx;
  p_b_.y += dy;
  p_c_.x += dx;
  p_c_.y += dy;
  p_d_.x += dx;
  p_d_.y += dy;
}

void Rectangle::move(const point_t &point)
{
  move(point.x-pos.x, point.y-pos.y);
}

void stashevskii::Rectangle::scale(double k)
{
  if (k < 0)
  {
    throw std::invalid_argument("Invalid scale argument");
  }
  else
  {
    width_ *= k;
    height_ *= k;
    p_a_.x = p_a_.x*k- pos.x*(k-1);
    p_a_.y = p_a_.y*k- pos.y*(k-1);
    p_b_.x = p_b_.x*k- pos.x*(k-1);
    p_b_.y = p_b_.y*k- pos.y*(k-1);
    p_c_.x = p_c_.x*k- pos.x*(k-1);
    p_c_.y = p_c_.y*k- pos.y*(k-1);
    p_d_.x = p_d_.x*k- pos.x*(k-1);
    p_d_.y = p_d_.y*k- pos.y*(k-1);
  }
}

void Rectangle::printf() const
{
  std::cout << "Rectangle:" << std::endl;
  std::cout << " Width: " << width_ << " Position:";
  std::cout << " x: " << pos.x << " y: " << pos.y << std::endl;
  std::cout << " Area: " << Rectangle::getArea() << std::endl;
}

point_t Rectangle::getPosition() const 
{
  return getFrameRect().pos;
}

void Rectangle::rotate(const double angle)
{
  const double dx = pos.x;
  const double dy = pos.y;
  move(-dx,-dy);

  p_a_= {cos(angle)*p_a_.x -sin(angle)*p_a_.y, cos(angle)*p_a_.y +sin(angle)*p_a_.x};
  p_b_= {cos(angle)*p_b_.x -sin(angle)*p_b_.y, cos(angle)*p_b_.y +sin(angle)*p_b_.x};
  p_c_= {cos(angle)*p_c_.x -sin(angle)*p_c_.y, cos(angle)*p_c_.y +sin(angle)*p_c_.x};
  p_d_= {cos(angle)*p_d_.x -sin(angle)*p_d_.y, cos(angle)*p_d_.y +sin(angle)*p_d_.x};
  move(dx,dy);
}
