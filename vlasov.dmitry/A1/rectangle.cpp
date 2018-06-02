#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t widthHeightPos):
  width_(widthHeightPos.width),
  height_(widthHeightPos.height),
  center_(widthHeightPos.pos)
{
  if (width_ < 0.0 || height_ < 0.0)
  {
    throw std::invalid_argument("Check that width/height are positive numbers");
  }
};

double Rectangle::getArea() const
{
  return height_ * width_;
};

rectangle_t Rectangle::getFrameRect() const
{
  return {height_,width_,{center_.x,center_.y}};
};

void Rectangle::move(const point_t &poss)
{
  center_=poss;
};

void Rectangle::move(const double xOffset, const double yOffset)
{
  center_.x += xOffset;
  center_.y += yOffset;
};
