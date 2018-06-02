#include "composite-shape.hpp"
#include <stdexcept>
#include <cmath>

sibikin::CompositeShape::CompositeShape():
  count_(0),
  arr_(nullptr),
  pos_({0.0, 0.0})
{}

sibikin::CompositeShape::CompositeShape(Shape * newShape):
  count_(1),
  arr_(new Shape*[1]),
  pos_(newShape->getFrameRect().pos)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Null reference!");
  }
  arr_[0] = newShape;
}

sibikin::CompositeShape::CompositeShape(const CompositeShape & comp):
  count_(comp.getSize()),
  arr_(new Shape*[count_]),
  pos_(comp.getFrameRect().pos)
{
  for (size_t i = 0; i < count_; ++i)
  {
    arr_[i] = comp.arr_[i];
  }
}

sibikin::CompositeShape::CompositeShape(CompositeShape &&comp):
  count_(comp.getSize()),
  arr_(comp.arr_),
  pos_(comp.getFrameRect().pos)
{
  comp.count_ = 0;
  comp.pos_ = {0.0, 0.0};
  comp.arr_ = nullptr;
}

sibikin::CompositeShape::~CompositeShape()
{
  delete[] arr_;
  arr_ = nullptr;
}

sibikin::CompositeShape& sibikin::CompositeShape::operator =(const CompositeShape &comp)
{
  if (this != & comp)
  {
    pos_ = comp.getFrameRect().pos;
    count_ = comp.count_;
    Shape ** newComp = new Shape*[count_];
    delete[] arr_;
    arr_ = newComp;
    for (size_t i = 0; i < count_; i++)
    {
      arr_[i] = comp.arr_[i];
    }
  }
  return *this;
}

sibikin::CompositeShape& sibikin::CompositeShape::operator =(CompositeShape &&comp)
{
  if (this != &comp)
  {
    pos_ = comp.getFrameRect().pos;
    delete[] arr_;
    arr_= comp.arr_;
    count_= comp.count_;

    comp.arr_= nullptr;
    comp.count_= 0;
    comp.pos_ = {0,0};
  }
  return *this;
}

sibikin::Shape& sibikin::CompositeShape::operator [](const size_t index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("out of range!");
  }
  return *arr_[index];

}

void sibikin::CompositeShape::addShape(Shape *newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Null reference!");
  }
  Shape **temp = new Shape *[count_ + 1];
  for ( size_t i = 0; i < count_; i++)
  {
    temp[i] = arr_[i];
  }
  delete[] arr_;
  temp[count_] = newShape;
  count_++;
  arr_ = temp;
  pos_ = getFrameRect().pos;
}

void sibikin::CompositeShape::deleteShape(const size_t index)
{
  if ((index > count_) || (index < 1))
  {
    throw std::invalid_argument("Incorrect index!");
  }
  arr_[index - 1] = nullptr;
  count_--;

  if (count_ != 0)
  {
    Shape **new_array = new Shape *[count_];
    size_t j = 0;
    for (size_t i = 0; i < count_; i++)
    {
      if (arr_[i] != nullptr)
      {
        new_array[i] = arr_[i + j];
      }
      else
      {
        new_array[i] = arr_[i + 1];
        j++;
      }
    }
    delete[] arr_;
    arr_ = new_array;
    pos_ = this->getFrameRect().pos;
  }
}

size_t sibikin::CompositeShape::getSize() const
{
  return count_;
}

sibikin::point_t sibikin::CompositeShape::getPos() const
{
  return pos_;
}

double sibikin::CompositeShape::getArea() const
{
  double result = 0;
  for (size_t i = 0; i < count_; i++)
  {
    result += arr_[i]->getArea();
  }
  return result;
}

sibikin::rectangle_t sibikin::CompositeShape::getFrameRect() const
{
  rectangle_t temp = arr_[0]->getFrameRect();
  double top = temp.pos.y + temp.height / 2,
         bottom = temp.pos.y - temp.height / 2,
         left = temp.pos.x - temp.width / 2,
         right = temp.pos.x + temp.width / 2;
  for (size_t i = 1; i < count_; i++)
  {
    temp = arr_[i]->getFrameRect();
    top = std::max(top, temp.pos.y + temp.height / 2);
    bottom = std::min(bottom, temp.pos.y - temp.height / 2);
    left = std::min(left, temp.pos.x - temp.width / 2);
    right = std::max(right, temp.pos.x + temp.width / 2);
  }
  return {right - left, top - bottom, { (right + left) / 2, (top + bottom) / 2 } };
}

void sibikin::CompositeShape::move(const point_t & newCenter)
{
  for (size_t i = 0; i < count_; i++)
  {
    arr_[i]->move(newCenter.x - pos_.x, newCenter.y - pos_.y);
  }
  pos_ = newCenter;
}

void sibikin::CompositeShape::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
  for ( size_t i = 0; i < count_; i++)
  {
    arr_[i]->move(dx, dy);
  }
}

void sibikin::CompositeShape::scale(const double coef)
{
  if (coef <= 0.0)
  {
    throw std::invalid_argument("Coef must be > 0");
  }

  for (size_t i = 0; i< count_; i++)
  {
    arr_[i]->scale(coef);
    arr_[i]->move((arr_[i]->getFrameRect().pos.x - pos_.x)*(coef - 1), (arr_[i]->getFrameRect().pos.y- pos_.y)*(coef - 1));
  }
}

void sibikin::CompositeShape::rotate(const double phi)
{
  point_t pos = getPos();
  double radPhi = (phi*M_PI) / 180.0;
  for (size_t i = 0; i < count_; i++)
  {
    arr_[i]->move({
      pos.x + (arr_[i]->getPos().x - pos.x) * cos(radPhi) - (arr_[i]->getPos().y - pos.y) * sin(radPhi),
      pos.y + (arr_[i]->getPos().y - pos.y) * cos(radPhi) + (arr_[i]->getPos().x - pos.x) * sin(radPhi)
    });
    arr_[i]->rotate(phi);
  }
}

