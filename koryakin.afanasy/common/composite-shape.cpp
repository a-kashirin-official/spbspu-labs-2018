#include "composite-shape.hpp"

#include <stdexcept>

using namespace koryakin;

koryakin::CompositeShape::CompositeShape(Shape * newShape):
  list_(nullptr),
  count_(0)
{
  if (!newShape)
  {
    throw std::invalid_argument("Invalid Pointer");
  }
  addShape(newShape);
}

koryakin::CompositeShape::~CompositeShape()
{
  this->clear();
}

double koryakin::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < count_; ++i)
  {
    area += list_[i]->getArea();
  }
  return area;
}

rectangle_t koryakin::CompositeShape::getFrameRect() const noexcept
{
  if (count_ <= 0) 
  {
    return {{0, 0}, 0 , 0};
  } 
  else
  {
    rectangle_t shapeFrameRect = list_[0]->getFrameRect();
    double left = shapeFrameRect.pos.x - shapeFrameRect.width / 2;
    double right = shapeFrameRect.pos.x + shapeFrameRect.width / 2;
    double top = shapeFrameRect.pos.y + shapeFrameRect.height / 2;
    double bottom = shapeFrameRect.pos.y - shapeFrameRect.height / 2;

    for (int i = 1; i < count_; i++) 
    {
      shapeFrameRect = list_[i]->getFrameRect();
      double iLeft = shapeFrameRect.pos.x - shapeFrameRect.width / 2;
      double iRight = shapeFrameRect.pos.x + shapeFrameRect.width / 2;
      double iTop = shapeFrameRect.pos.y + shapeFrameRect.height / 2;
      double iBottom = shapeFrameRect.pos.y - shapeFrameRect.height / 2;
      if (iLeft < left) 
      {
        left = iLeft;
      }
      if (iRight > right)
      {
        right = iRight;
      }
      if (iTop > top)
      {
        top = iTop;
      }
      if (iBottom < bottom)
      {
        bottom = iBottom;
      }
    }
    return {{(left + (right - left) / 2), (bottom + (top - bottom) / 2)}, (right - left), (top - bottom)};
  }
}

void koryakin::CompositeShape::move(const point_t & newPos) noexcept
{
  const point_t curPos = getFrameRect().pos; 
  move(newPos.x - curPos.x, newPos.y - curPos.y);
}

void koryakin::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < count_; i++)
  {
    list_[i]->move(dx, dy);
  }
}

void koryakin::CompositeShape::scale(const double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }

  const point_t curPos = getFrameRect().pos;
  for (int i = 0; i < count_; i++)
  {
    const point_t shapePos = list_[i]->getFrameRect().pos;
    list_[i]->move({curPos.x + factor * (shapePos.x - curPos.x),
                      curPos.y + factor * (shapePos.y - curPos.y)});
    list_[i]->scale(factor);
  }
}

int koryakin::CompositeShape::getCount() const noexcept
{
  return count_;
}

void koryakin::CompositeShape::addShape(Shape * shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid Pointer");
  }
  for (int i = 0; i < count_; ++i)
  {
    if (list_[i] == shape)
    {
      throw std::invalid_argument("Can not add this Shape");
    }
  }
  Shape ** temp = new Shape * [count_ + 1];
  for (int i = 0; i < count_; ++i)
  {
    temp[i] = list_[i];
  }
  temp[count_++] = shape;
  delete [] list_;
  list_ = temp;
}

void koryakin::CompositeShape::removeShape(const int index)
{
  if (count_ <= 0)
  {
    throw std::out_of_range("List is Empty");
  }
  if (index >= count_)
  {
    throw std::out_of_range("Index out of range");
  }
  if ((count_ == 1) && (index == 0))
  {
    clear();
    return;
  }
  Shape ** temp = new Shape * [count_ - 1];
  for (int i = 0; i < index; ++i)
  {
    temp[i] = list_[i];
  }
  for (int i = index; i < count_ - 1; ++i)
  {
    temp[i] = list_[i + 1];
  }
  delete [] list_;
  list_ = temp;
  count_--;
}

void koryakin::CompositeShape::clear()
{
  delete [] list_;
  list_ = nullptr;
  count_ = 0;
}

CompositeShape & koryakin::CompositeShape::operator=(const CompositeShape & rhs) noexcept
{
  if (this != &rhs)
  {
    delete [] list_;
    list_ = new Shape * [rhs.count_];
    for (int i = 0; i < rhs.getCount(); ++i)
    {
      list_[i] = rhs.list_[i];
    }
    count_ = rhs.count_;
  }
  return *this;
}

Shape * koryakin::CompositeShape::operator[](const int index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index out of range");
  }
  return list_[index];
}
