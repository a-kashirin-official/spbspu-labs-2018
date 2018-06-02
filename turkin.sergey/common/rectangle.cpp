#include <iostream>
#include <cmath>
#include "rectangle.hpp"


turkin::Rectangle::Rectangle(const double width, const double height, const point_t &pos) :
  pnt_{{pos.x - width / 2, pos.y - height / 2},
       {pos.x - width / 2, pos.y + height / 2},
       {pos.x + width / 2, pos.y + height / 2},
       {pos.x + width / 2, pos.y - height / 2}}
{
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("Width and height of the rectangle must be > 0!");
  }
  width_ = width;
  height_ = height;
}


double turkin::Rectangle::getArea() const
{
  return width_ * height_;
}

turkin::rectangle_t turkin::Rectangle::getFrameRect() const
{
  return {width_, height_, {(pnt_[0].x + pnt_[2].x) / 2, (pnt_[0].y + pnt_[2].y) / 2}};
}

void turkin::Rectangle::move(const point_t &pos)
{
  move(pos.x - (pnt_[0].x + pnt_[2].x) / 2, pos.y - (pnt_[0].y + pnt_[2].y) / 2);
}

void turkin::Rectangle::move(double Ox, double Oy)
{
  for (auto &point : pnt_) {
    point.x += Ox;
    point.y += Oy;
  }
}

void turkin::Rectangle::printInfo()
{
  std::cout << "RECTANGLE:" << std::endl;
}

void turkin::Rectangle::scale(double k)
{
  double X = (pnt_[0].x + pnt_[2].x) / 2;
  double Y = (pnt_[0].y + pnt_[2].y) / 2;
  if (k < 0) {
    throw std::invalid_argument("K > 0!");
  }
  for (auto &point : pnt_) {
    point.x = X + (point.x - X) * k;
    point.y = Y + (point.y - Y) * k;
  }
  width_ *= k;
  height_ *= k;

}
  void turkin::Rectangle::rotate(double angle)
  {
    double radians = angle * M_PI / 180;
    double X = (pnt_[0].x + pnt_[2].x) / 2;
    double Y = (pnt_[0].y + pnt_[2].y) / 2;
    for (auto &point : pnt_) {
      point = {
        X + (point.x - X) * cos(radians) -
        (point.y - Y) * sin(radians),
        Y + (point.y - Y) * cos(radians) +
        (point.x - X) * sin(radians)
      };
    }
  }

turkin::point_t turkin::Rectangle::getCenter() const
{
  return {(pnt_[0].x + pnt_[2].x) / 2, (pnt_[0].y + pnt_[2].y) / 2};
}



