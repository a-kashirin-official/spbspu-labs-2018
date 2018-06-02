//
//  rectangle.cpp
//  
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//
#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

timoshenskiy::Rectangle::Rectangle(const point_t &pos, const double rectangle_width, const double rectangle_height):
  pos_(pos),
  peaks_{{pos.x - rectangle_width / 2, pos.y - rectangle_height / 2},
         {pos.x - rectangle_width / 2, pos.y + rectangle_height / 2},
         {pos.x + rectangle_width / 2, pos.y + rectangle_height / 2},
         {pos.x + rectangle_width / 2, pos.y - rectangle_height / 2}},
  angle_(0.0)
{
  if ((rectangle_width < 0.0) || (rectangle_height < 0.0))
  {
    throw std::invalid_argument("ERROR. Invalid height or width of rectangle");
  }
}

double timoshenskiy::Rectangle::getArea() const
{
  return (getDistance(peaks_[0], peaks_[1]) * getDistance(peaks_[1], peaks_[2]));
}

timoshenskiy::rectangle_t timoshenskiy::Rectangle::getFrameRect() const
{
  double maxX = peaks_[0].x;
  double maxY = peaks_[0].y;
  double minX = peaks_[0].x;
  double minY = peaks_[0].y;

  for (int i = 1; i < 4; i++)
  {
    maxX = (peaks_[i].x > maxX) ? peaks_[i].x : maxX;
    maxY = (peaks_[i].y > maxY) ? peaks_[i].y : maxY;
    minX = (peaks_[i].x < minX) ? peaks_[i].x : minX;
    minY = (peaks_[i].y < minY) ? peaks_[i].y : minY;

  }
  return{maxX - minX, maxY - minY, {maxX - (maxX - minX) / 2, maxY - (maxY - minY) / 2 }};
}

void timoshenskiy::Rectangle::move( const double  dx, const double dy)
{
  for (int i = 0; i < 4; i++)
  {
    peaks_[i].x += dx;
    peaks_[i].y += dy;
  }
  getPos();
}

void timoshenskiy::Rectangle::move(const point_t &posit)
{
  double dx = posit.x - pos_.x;
  double dy = posit.y - pos_.y;
  move(dx, dy);
}

void timoshenskiy::Rectangle::scale(double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument ("ERROR. Multiplier shouldn't be negative");
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      peaks_[i].x = pos_.x + (peaks_[i].x - pos_.x) * multiplier;
      peaks_[i].y = pos_.y + (peaks_[i].y - pos_.y) * multiplier;
    }
  }
}

void timoshenskiy::Rectangle::rotate(double degrees)
{
  double rad = degrees * M_PI / 180;
  const double x = pos_.x;
  const double y = pos_.y;

  angle_ += degrees;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }

  for (int i = 0; i < 4; i++)
  {
    const double dx = peaks_[i].x;
    const double dy = peaks_[i].y;

    peaks_[i].x = x + (dx - x) * cos(rad) - (dy - y) * sin(rad);
    peaks_[i].y = y + (dx - x) * sin(rad) + (dy - y) * cos(rad);
  }
}

double timoshenskiy::Rectangle::getDistance(const point_t &point1, const point_t &point2) const
{
  return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

void timoshenskiy::Rectangle::getPos()
{
  pos_.x = (peaks_[2].x + peaks_[0].x) / 2;
  pos_.y = (peaks_[2].y + peaks_[0].y) / 2;
}

std::string timoshenskiy::Rectangle::printPeaks() const
{
  std::stringstream peak;
  for (int i = 0; i < 4; i++)
  {
    peak << i << "(" << peaks_[i].x << ", " << peaks_[i].y << ")" <<std::endl;
  }
  return peak.str();
}

std::string timoshenskiy::Rectangle::printInformation() const
{
  std::stringstream info;
  info << "\t Width: " << getDistance(peaks_[1], peaks_[2]) << "\n"
  << "\t Height: " <<getDistance(peaks_[0], peaks_[1]) << "\n"
  << "\t Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "\t Area: " << getArea() << "\n"
  << "\t Angle: " << angle_ << "\n" << "\n";
  
  info << "Rectangle around rectangle: " << "\n"
  << "\t Width: " << getFrameRect().width << "\n"
  << "\t Height: " << getFrameRect().height << "\n"
  << "\t Center: "<< "(" << getFrameRect().pos.x << ","
  << getFrameRect().pos.y << ")" << "\n"
  << "________________________" << "\n";
 
  return info.str();
}
