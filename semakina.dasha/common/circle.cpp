#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

using namespace semakina;

Circle::Circle(const point_t & center, const double radius):
  pos_(center),
  radius_(radius),
  degree_(0)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Invalid circle's radius");
  }
}

void Circle::move(const point_t & pos) noexcept
{
  pos_ = pos;
}

void Circle::move(const double dx, const double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

double Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {2 * radius_, 2 * radius_, pos_};
}

void Circle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  radius_ *= coefficient;
}

void Circle::rotate(const double degree) noexcept
{
  degree_ += degree;
}
