#include "composite-shape.hpp"
#include <algorithm>
#include <stdexcept>

using namespace sergeev;

CompositeShape::CompositeShape():
  size_(0),
  items_(nullptr)
{}

CompositeShape::CompositeShape(const CompositeShape & rhs):
  size_(rhs.size_),
  items_(std::make_unique< item_type[] >(rhs.size_))
{
  std::copy(rhs.items_.get(), rhs.items_.get() + size_, items_.get());
}

CompositeShape::CompositeShape(CompositeShape && rhs):
  size_(rhs.size_),
  items_(std::move(rhs.items_))
{
  rhs.size_ = 0;
}

CompositeShape & CompositeShape::operator=(const CompositeShape & rhs)
{
  if(this == &rhs)
  {
    return *this;
  }

  items_ = std::make_unique< item_type[] >(rhs.size_);
  size_ = rhs.size_;
  std::copy(rhs.items_.get(), rhs.items_.get() + size_, items_.get());
  return *this;
}

CompositeShape & CompositeShape::operator=(CompositeShape && rhs)
{
  items_ = std::move(rhs.items_);
  size_ = rhs.size_;
  rhs.size_ = 0;
  return *this;
}

CompositeShape::item_type & CompositeShape::operator[](int index)
{
  checkIndex(index);
  return items_[index];
}

double CompositeShape::getArea() const
{
  double result = 0.0;
  for(int i = 0; i < size_; i++)
  {
    result += items_[i]->getArea();
  }
  return result;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if(size_ == 0)
  {
    rectangle_t zero = {{0.0,0.0},0.0,0.0};
    return zero;
  }

  rectangle_t rect = items_[0]->getFrameRect();
  double left,top,right,bottom;
  left = rect.pos.x - (rect.width / 2);
  top = rect.pos.y + (rect.height / 2);
  right = rect.pos.x + (rect.width / 2);
  bottom = rect.pos.y - (rect.height / 2);

  for(int i = 1; i < size_; i++)
  {
    rect = items_[i]->getFrameRect();
    left = std::min(left, rect.pos.x - (rect.width / 2));
    top = std::max(top, rect.pos.y + (rect.height / 2));
    right = std::max(right, rect.pos.x + (rect.width / 2));
    bottom = std::min(bottom, rect.pos.y - (rect.height / 2));
  }

  return {{left + ((right - left) / 2), bottom + ((top - bottom) / 2)}, right - left, top - bottom};
}

void CompositeShape::move(const point_t & point)
{
  point_t center = getFrameRect().pos;
  move(point.x - center.x, point.y - center.y);
}

void CompositeShape::move(double dx, double dy)
{
  for(int i = 0; i < size_; i++)
  {
    items_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(double factor)
{
  if(factor < 0.0)
  {
    throw std::invalid_argument("Wrong scaling factor!");
  }
  point_t shape_pos = getFrameRect().pos;
  point_t item_pos{0.0,0.0};
  for(int i = 0; i < size_; i++)
  {
    item_pos = items_[i]->getFrameRect().pos;
    items_[i]->move({shape_pos.x + factor * (item_pos.x - shape_pos.x),shape_pos.y + factor * (item_pos.y - shape_pos.y)});
    items_[i]->scale(factor);
  }
}

void CompositeShape::rotate(double angle)
{
  point_t compositeCenter = getFrameRect().pos;

  for_each(items_.get(), items_.get() + size_, 
    [&compositeCenter, angle] (item_type & shape) {
      point_t elementVector = shape->getFrameRect().pos;
      elementVector = { elementVector.x - compositeCenter.x, elementVector.y - compositeCenter.y };
      elementVector.rotate(angle);
      shape->move({ elementVector.x + compositeCenter.x, elementVector.y + compositeCenter.y });
      shape->rotate(angle);
  });
}

Matrix CompositeShape::devide() const
{
  Matrix matrix;
  for_each(items_.get(), items_.get() + size_, [&matrix] (const item_type & shape) {
    matrix.add(shape);
  });
  return matrix;
}

void CompositeShape::add(const item_type & shape)
{
  std::unique_ptr< item_type[] > newList (std::make_unique< item_type[] >(size_ + 1));
  std::swap_ranges(items_.get(), items_.get() + size_, newList.get());
  newList[size_++] = shape;
  items_ = std::move(newList);
}

void CompositeShape::dispose(int index)
{
  checkIndex(index);
  std::unique_ptr< item_type[] > newList(std::make_unique< item_type[] >(--size_));
  std::swap_ranges(items_.get(), items_.get() + index, newList.get());
  std::swap_ranges(items_.get() + index + 1, items_.get() + size_ + 1, newList.get() + index);
  items_ = std::move(newList);
}

void CompositeShape::clean()
{
  items_.reset(nullptr);
  size_ = 0;
}

int CompositeShape::getListSize() const
{
  return size_;
}

void CompositeShape::checkIndex(int index)
{
  if((index < 0) || (index >= size_))
  {
    throw std::out_of_range("Wrong Index of items of CompositeShape!");
  }
}
