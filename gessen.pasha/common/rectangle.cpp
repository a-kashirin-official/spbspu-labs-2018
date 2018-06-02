#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace gessen;

Rectangle::Rectangle(const point_t & angle,const double width,const double height):
  shapeAnglePos_
  {
    {angle.x - width / 2.0, angle.y + height / 2.0},
    {angle.x + width / 2.0, angle.y + height / 2.0},
    {angle.x + width / 2.0, angle.y - height / 2.0},
    {angle.x - width / 2.0, angle.y - height / 2.0}
  },
  width_(width),
  height_(height)
{
  if((width_ < 0.0) || (height_ < 0.0))
  {
    throw std::invalid_argument("Error. Width and height must be equal or greater than zero");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  point_t angle_ = {(shapeAnglePos_[0].x + shapeAnglePos_[2].x) / 2, (shapeAnglePos_[0].y + shapeAnglePos_[2].y) / 2};
  point_t topLeft = angle_;
  point_t bottomRight = angle_;

  for (size_t i = 0; i < 4; i ++)
  {
    if (shapeAnglePos_[i].x < topLeft.x)
    {
      topLeft.x = shapeAnglePos_[i].x;
    }
    if (shapeAnglePos_[i].y > topLeft.y)
    {
      topLeft.y = shapeAnglePos_[i].y;
    }
    if (shapeAnglePos_[i].x > bottomRight.x)
    {
      bottomRight.x = shapeAnglePos_[i].x;
    }
    if (shapeAnglePos_[i].y < bottomRight.y)
    {
      bottomRight.y = shapeAnglePos_[i].y;
    }
  }
  return {angle_, bottomRight.x - topLeft.x, topLeft.y - bottomRight.y};
}


void Rectangle::move(const point_t & newPoint)
{
  point_t point = getFrameRect().pos;
  move(newPoint.x - point.x, newPoint.y - point.y);
}

void Rectangle::move(const double dx, const double dy)
{
  for (size_t i = 0; i < 4; ++i)
  {
    shapeAnglePos_[i].x += dx;
    shapeAnglePos_[i].y += dy;
  }
}

void Rectangle::scale(const double ScaleCoefficient)
{
  if (ScaleCoefficient < 0.0)
  {
    throw std::invalid_argument("Error. Scale coefficient must be equal or greater than zero");
  }
  width_ *= ScaleCoefficient;
  height_ *= ScaleCoefficient;
}

void Rectangle::rotate(const double angleRotate)
{
  double msin = sin(angleRotate * M_PI / 180);
  double mcos = cos(angleRotate * M_PI / 180);
  point_t center = getFrameRect().pos;
  for (size_t i = 0; i < 4; i++)
  {
    shapeAnglePos_[i] = {center.x + (shapeAnglePos_[i].x - center.x) * mcos - (shapeAnglePos_[i].y - center.y) * msin,
      center.y + (shapeAnglePos_[i].y - center.y) * mcos + (shapeAnglePos_[i].x - center.x) * msin};
  }
}

void Rectangle::printShapeName() const
{
  std::cout << "Rectangle" << std::endl;
  std::cout << "width:" << getFrameRect().width << std::endl;
  std::cout << "height:" << getFrameRect().height << std::endl;
  std::cout << "Area:" << getArea() << std::endl;
  std::cout << "pos(x):" << getFrameRect().pos.x << std::endl;
  std::cout << "pos(y):" << getFrameRect().pos.y << std::endl;
}

