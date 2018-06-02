#include "rectangle.hpp"



dudina::Rectangle::Rectangle(const point_t & pos, const double width, const double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width_ < 0.0)
  {
    throw std::invalid_argument("Width must be > 0");
  }
  if (height_ < 0.0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
}



double dudina::Rectangle::getArea() const
{
  return width_ * height_;
}

dudina::rectangle_t dudina::Rectangle::getFrameRect() const
{
  return { height_,width_,{ pos_.x,pos_.y} };
}

void dudina::Rectangle::move(const point_t & pos)
{
  pos_= pos;
}

void dudina::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void dudina::Rectangle::scale(const double coeff)
{
  if (coeff < 0.0)
  {
    throw std::invalid_argument("Scale coefficient must be > 0");
  }

  width_ *= coeff;
  height_ *= coeff;
}


void dudina::Rectangle::printInformation()
{
  std::cout << "Height of rectangle: " << height_ << std::endl;
  std::cout << "Width of rectangle: " << width_ << std::endl;
  std::cout << "Center of rectangle: {" << pos_.x << "," << pos_.y << "}" << std::endl;
}

