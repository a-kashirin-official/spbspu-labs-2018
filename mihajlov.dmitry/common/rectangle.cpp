#define _USE_MATH_DEFINES

#include "rectangle.hpp"
#include <iostream>
#include <cmath>

mihajlov::Rectangle::Rectangle(const point_t& centerPos, const double height, const double width):
  data_{centerPos, 0.0, 0.0},
  angle_(0.0)
{
  if ((height < 0.0) || (width < 0.0))
  {
    throw std::invalid_argument("Invalid height/width !");
  }
  data_.height = height;
  data_.width = width;
}

double mihajlov::Rectangle::getArea() const
{
  return (data_.height * data_.width);
}

mihajlov::rectangle_t mihajlov::Rectangle::getFrameRect() const
{
  double minX =
          data_.pos.x - (data_.width / 2) * cos(angle_ * M_PI / 180) - (data_.height / 2) * sin(angle_ * M_PI / 180);
  double minY =
          data_.pos.y - (data_.height / 2) * cos(angle_ * M_PI / 180) - (data_.width / 2) * sin(angle_ * M_PI / 180);
  double maxY =
          data_.pos.y + (data_.height / 2 ) * cos(angle_ * M_PI / 180) + (data_.width / 2) * sin(angle_ * M_PI / 180);
  double maxX =
          data_.pos.x + (data_.width / 2) * cos(angle_ * M_PI / 180) + (data_.height / 2) * sin(angle_ * M_PI / 180);

  double frameWidth = std::abs(maxX - minX);
  double frameHeight = std::abs(minY - maxY);

  return {data_.pos, frameHeight, frameWidth};

}

void mihajlov::Rectangle::move(const point_t& centerPos)
{
  data_.pos.x = centerPos.x;
  data_.pos.y = centerPos.y;
}

void mihajlov::Rectangle::move(const double shiftX, const double shiftY)
{
  data_.pos.x += shiftX;
  data_.pos.y += shiftY;
}

void mihajlov::Rectangle::getInfo() const
{
  std::cout << "Current Rectangle data_: " << std::endl;
  std::cout << "X = " << data_.pos.x << "; Y = " << data_.pos.y << ";" << std::endl;
  std::cout << "Height = " << data_.height << "; Width = " << data_.width << ";" << std::endl;
}

void mihajlov::Rectangle::printName() const
{
  std::cout << "Rectanlge ";
}

void mihajlov::Rectangle::scale(const double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument("Invalid multiplier!");
  }
  data_.height *= multiplier;
  data_.width *= multiplier;
}

void mihajlov::Rectangle::rotate(const double angle)
{
  angle_ += angle;
}
