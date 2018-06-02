#include "rectangle.hpp"
#include <stdexcept>

using namespace vlasov;

vlasov::Rectangle::Rectangle(const rectangle_t widthHeightPos):
  width_(widthHeightPos.width),
  height_(widthHeightPos.height),
  center_(widthHeightPos.pos)
{
  if (width_ < 0.0 || height_ < 0.0)
  {
    throw std::invalid_argument("Check that width/height are positive numbers");
  }
};

double vlasov::Rectangle::getArea() const
{
  return height_ * width_;
};

rectangle_t vlasov::Rectangle::getFrameRect() const
{
  return {height_,width_,{center_.x,center_.y}};
};

void vlasov::Rectangle::move(const point_t &poss)
{
  center_=poss;
};

void vlasov::Rectangle::move(const double xOffset, const double yOffset)
{
  center_.x += xOffset;
  center_.y += yOffset;
};

void vlasov::Rectangle::scale(double coef_)
{
  if (coef_ > 0.0) {
    width_ *= coef_;
    height_ *= coef_;
  } else throw std::invalid_argument("Check that scaling number is >0");
};
