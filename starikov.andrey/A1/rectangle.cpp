#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t modelRect):
modelRect_(modelRect)
{
  if ((modelRect_.height < 0) || (modelRect_.width < 0))
  {
    std::cerr << "Warning! Incorrect values..." << std::endl;
  }
  constCentre_ = modelRect_.pos;
}
double Rectangle::getArea() const
{
  return (modelRect_.width * modelRect_.height);
}
rectangle_t Rectangle::getFrameRect() const
{
  return modelRect_;
}
void Rectangle::move(const point_t &centre)
{
  modelRect_.pos = constCentre_;
  modelRect_.pos = centre;
}
void Rectangle::move(const double offsetAxisX, const double offsetAxisY)
{
  modelRect_.pos = constCentre_;
  modelRect_.pos.x += offsetAxisX;
  modelRect_.pos.y += offsetAxisY;
}
