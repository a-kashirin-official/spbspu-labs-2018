#include <iostream>
#include <cmath>
#include "rectangle.hpp"

using namespace golyshev;

golyshev::Rectangle::Rectangle(const double width, const double height, const point_t &poss) :
  width_(width),
  height_(height),
  center_(poss),
  coordinates({{poss.x - width / 2, poss.y + height / 2}, {poss.x + width / 2, poss.y + height / 2},
               {poss.x + width / 2, poss.y - height / 2}, {poss.x - width / 2, poss.y - height / 2}})
{
  if (width < 0 || height < 0) {
    throw std::invalid_argument("Width and height of the rectangle must be > 0!");
  }
}

double golyshev::Rectangle::getArea() const
{
  return width_ * height_;
}

golyshev::rectangle_t golyshev::Rectangle::getFrameRect() const
{
  double sum_x = 0;
  double sum_y = 0;
  for (size_t i = 0; i < 4; i++) {
    sum_x += coordinates[i].x;
    sum_y += coordinates[i].y;
  }
  point_t centre = {sum_x / 4, sum_y / 4};
  double heigth = sqrt((coordinates[0].x - coordinates[3].x) * (coordinates[0].x - coordinates[3].x) +
                       (coordinates[0].y - coordinates[3].y) * (coordinates[0].y - coordinates[3].y));
  double width = sqrt((coordinates[0].x - coordinates[1].x) * (coordinates[0].x - coordinates[1].x) +
                      (coordinates[0].y - coordinates[1].y) * (coordinates[0].y - coordinates[1].y));
  return {width, heigth, centre};
}

void golyshev::Rectangle::move(const point_t &poss)
{
  move(center_.x - poss.x, center_.y - poss.y);
}

void golyshev::Rectangle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
  for (size_t i = 0; i < 4; i++) {
    coordinates[i] = {coordinates[i].x + Ox,
                      coordinates[i].y + Oy};
  }
}

void golyshev::Rectangle::scale(double coeff)
{
  if (coeff < 0) {
    throw std::invalid_argument("Scale coefficient of the rectangle must be > 0!");
  }
  width_ *= coeff;
  height_ *= coeff;
  for (size_t i = 0; i < 4; i++) {
    coordinates[i] = {center_.x + (coordinates[i].x - center_.x) * coeff,
                      center_.y + (coordinates[i].y - center_.y) * coeff};
  }
}

void golyshev::Rectangle::rotate(const double angle)
{
  for (size_t i = 0; i < 4; i++) {
    coordinates[i] = {center_.x + (coordinates[i].x - center_.x) * cos((angle * M_PI) / 180) -
                      (coordinates[i].y - center_.y) * sin((angle * M_PI) / 180),
                      center_.y + (coordinates[i].y - center_.y) * cos((angle * M_PI) / 180) +
                      (coordinates[i].x - center_.x) * sin((angle * M_PI) / 180)};
  }

}

void golyshev::Rectangle::OutInf() const
{
  std::cout << "Center( " << center_.x << " ; " << center_.y << " )" << std::endl;
  std::cout << "Width:  " << getFrameRect().width << std::endl;
  std::cout << "Height: " << getFrameRect().height << std::endl;
  std::cout << "Area:   " << getArea() << std::endl;
  std::cout << "_____________________ " << std::endl;
}
