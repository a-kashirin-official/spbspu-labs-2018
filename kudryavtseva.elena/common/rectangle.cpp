#include "rectangle.hpp"
#include <iostream>
#include <cmath>

kudryavtseva::Rectangle::Rectangle(const kudryavtseva::point_t &rectCenter, const double w, const double h):
centerRec_(rectCenter),
width_(w),
height_(h)
{
  if ((w < 0) || (h < 0))
  {
    throw std::invalid_argument("Error. Invalid values.");
  }
  p[0] = {centerRec_.x + width_/2.0, centerRec_.y + height_/2.0};
  p[1] = {centerRec_.x + width_/2.0, centerRec_.y - height_/2.0};
  p[2] = {centerRec_.x - width_/2.0, centerRec_.y - height_/2.0};
  p[3] = {centerRec_.x - width_/2.0, centerRec_.y + height_/2.0};
}

double kudryavtseva::Rectangle::getArea() const
{
  return width_*height_;
}

kudryavtseva::rectangle_t kudryavtseva::Rectangle::getFrameRect() const
{
  double xMin = p[0].x;
  for (int i = 1; i<4; i++)
  {
    if (p[i].x < xMin )
    {
      xMin = p[i].x;
    }
  }
  double xMax = p[0].x;
  for (int i = 1; i<4; i++)
  {
    if (p[i].x > xMax )
    {
      xMax = p[i].x;
    }
  }
  double yMin = p[0].y;
  for (int i = 1; i<4; i++)
  {
    if (p[i].y < yMin )
    {
      yMin = p[i].y;
    }
  }
  double yMax = p[0].y;
  for (int i = 1; i<4; i++)
  {
    if (p[i].y > yMax )
    {
      yMax = p[i].y;
    }
  }
  return kudryavtseva::rectangle_t {(xMax - xMin), (yMax - yMin), {xMin+(xMax - xMin)/2.0, yMin+(yMax-yMin)/2.0}};
}

void kudryavtseva::Rectangle::move(double dx, double dy)
{
  centerRec_.x +=dx;
  centerRec_.y +=dy;
}

void kudryavtseva::Rectangle::move(const kudryavtseva::point_t &center)
{
 centerRec_ = center;
}

void kudryavtseva::Rectangle::scale(const double k)
{
    if (k < 0.0)
    {
    throw std::invalid_argument("Error. Invalid coefficient.");
    }
    width_*=k;
    height_*=k;
    std::cout << "Width and height after scaling with coefficient " << k << " : " << width_ << "  " << height_ << std::endl;
}

void kudryavtseva::Rectangle::rotate(double angle)
{
  angle = angle*M_PI/180.0;

  p[0] = {getPos().x + (p[0].x - getPos().x)*std::cos(angle) - (p[0].y - getPos().y)*std::sin(angle),
            getPos().y + (p[0].x - getPos().x)*std::sin(angle) + (p[0].y - getPos().y)*std::cos(angle)};
  p[1] = {getPos().x + (p[1].x - getPos().x)*std::cos(angle) - (p[1].y - getPos().y)*std::sin(angle),
          getPos().y + (p[1].x - getPos().x)*std::sin(angle) + (p[1].y - getPos().y)*std::cos(angle)};
  p[2] = {getPos().x + (p[2].x - getPos().x)*std::cos(angle) - (p[2].y - getPos().y)*std::sin(angle),
            getPos().y + (p[2].x - getPos().x)*std::sin(angle) + (p[2].y - getPos().y)*std::cos(angle)};
  p[3] = {getPos().x + (p[3].x - getPos().x)*std::cos(angle) - (p[3].y - getPos().y)*std::sin(angle),
            getPos().y + (p[3].x - getPos().x)*std::sin(angle) + (p[3].y - getPos().y)*std::cos(angle)};
}

kudryavtseva::point_t kudryavtseva::Rectangle::getPos() const
{
  return centerRec_;
}

void kudryavtseva::Rectangle::printf() const
{
  std::cout << "___FOR THE RECTANGLE___" << std::endl;
  std::cout << "Width and height for the rectangle: " << getFrameRect().width << "  " << getFrameRect().height << std::endl;
  std::cout << "Coordinates of the center: " << getPos().x << "  " << getPos().y << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  std::cout << "\n" << std::endl;
}

double kudryavtseva::Rectangle::getHeight() const
{
  return height_;
}

double kudryavtseva::Rectangle::getWidth() const
{
  return width_;
}

