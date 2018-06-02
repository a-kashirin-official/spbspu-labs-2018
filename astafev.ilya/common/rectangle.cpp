
#include "rectangle.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

astafev::Rectangle::Rectangle(const point_t &centre, double width, double height) :
  centre_(centre),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if (height_ < 0.0) 
  {
    throw std::invalid_argument("error, height can't be <0 ");
  }
  if (width_ < 0.0) 
  {
    throw std::invalid_argument("error, widht can't be <0 ");
  }
}

double astafev::Rectangle::getArea() const noexcept
{
  return width_*height_;
}

astafev::rectangle_t astafev::Rectangle::getFrameRect() const noexcept
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = height_ * fabs(sine) + width_ * fabs(cosine);
  const double height = height_ * fabs(cosine) + width_ * fabs(sine);
  return {centre_, width, height};
}

void astafev::Rectangle::scale(double koeficent)
{
  if (koeficent <= 0.0) 
  {
    throw std::invalid_argument("error, koeficent can't be <=0 ");
  }
  width_ *= koeficent;
  height_ *= koeficent;
}

void astafev::Rectangle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void astafev::Rectangle::move(const point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

void astafev::Rectangle::printInfo() const noexcept
{
  std::cout << "Rectangle:  " << "  Width - " << width_ << ";  Height - " << height_ << ";"<<std::endl;
  std::cout << "  Center - x = " << centre_.x << ", y = " << centre_.y << ";"<<std::endl;

}

void astafev::Rectangle::rotate(const double degrees) noexcept
{
  angle_+=degrees;
}

size_t astafev::Rectangle::getSize() const noexcept
{
  return 1;
}
