#include <iostream>
#include <stdexcept>
#include <memory>
#include "composite-shape.hpp"

using namespace rebrin;

CompositeShape::CompositeShape(std::shared_ptr< rebrin::Shape > newShape) :
  list_(nullptr),
  count_(0)
{
  if (newShape == nullptr) {
    throw std::invalid_argument("New shape is empty");
  }
  addShape(newShape);
}

CompositeShape::CompositeShape(const rebrin::CompositeShape & composite_shape)
{
  list_ = std::unique_ptr <std::shared_ptr <Shape> []>(new std::shared_ptr <Shape> [composite_shape.count_]);
  count_ = composite_shape.count_;
  for (int i = 0; i < count_; i++)
  {
    list_[i] = composite_shape.list_[i];
  }
}

CompositeShape & CompositeShape::operator= (const CompositeShape & composite_shape)
{
  if (this != & composite_shape)
  {
    list_.reset(new std::shared_ptr <rebrin::Shape>[composite_shape.count_]);
    count_ = composite_shape.count_;
    for (int i = 0; i < count_; i++)
    {
      list_[i] = composite_shape.list_[i];
    }
  }
  return * this;
}

double CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < count_; i++) {
    area += list_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    return {0.0, 0.0, {0.0, 0.0}};
  }

  point_t pos_left, pos_right;
  pos_left.x = list_[0]->getFrameRect().pos.x - (list_[0]->getFrameRect().width / 2.0);
  pos_left.y = list_[0]->getFrameRect().pos.y + (list_[0]->getFrameRect().height / 2.0);

  pos_right.x = list_[0]->getFrameRect().pos.x + (list_[0]->getFrameRect().width / 2.0);
  pos_right.y = list_[0]->getFrameRect().pos.y - (list_[0]->getFrameRect().height / 2.0);

  double current;
  for (int i = 1; i < count_; i++) {
    current = list_[i]->getFrameRect().pos.x - (list_[i]->getFrameRect().width / 2.0);
    if (current < pos_left.x) {
      pos_left.x = current;
    }
    current = list_[i]->getFrameRect().pos.y + (list_[i]->getFrameRect().height / 2.0);
    if (current > pos_left.y) {
      pos_left.y = current;
    }

    current = list_[i]->getFrameRect().pos.x + (list_[i]->getFrameRect().width / 2.0);
    if (current > pos_right.x) {
      pos_right.x = current;
    }
    current = list_[i]->getFrameRect().pos.y - (list_[i]->getFrameRect().height / 2.0);
    if (current < pos_right.y) {
      pos_right.y = current;
    }
  }

  rectangle_t frameRect;
  frameRect.width = pos_right.x - pos_left.x;
  frameRect.height = pos_left.y - pos_right.y;
  frameRect.pos.x = (pos_right.x + pos_left.x) / 2.0;
  frameRect.pos.y = (pos_left.y + pos_right.y) / 2.0;

  return frameRect;
}

void CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < count_; i++) {
    list_[i]->move(dx, dy);
  }
}

void CompositeShape::move(const point_t & newPos)
{
  double dx = newPos.x - getFrameRect().pos.x;
  double dy = newPos.y - getFrameRect().pos.y;
  move(dx, dy);
}

void CompositeShape::scale(const double factor)
{
  double dx, dy;
  point_t compositeCenter = getFrameRect().pos;
  for (int i = 0; i < count_; i++) {
    dx = list_[i]->getFrameRect().pos.x - compositeCenter.x;
    dy = list_[i]->getFrameRect().pos.y - compositeCenter.y;

    point_t newPos;
    newPos.x = compositeCenter.x + factor*dx;
    newPos.y = compositeCenter.y + factor*dy;
    list_[i]->move(newPos);

    list_[i]->scale(factor);
  }
}

void CompositeShape::addShape(const std::shared_ptr< rebrin::Shape > newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("New Shape is empty");
  }
  std::unique_ptr < std::shared_ptr < rebrin::Shape >[] > tempArray
    (new std::shared_ptr < rebrin::Shape > [count_ + 1]);

  for (int i = 0; i < count_; i++) {
    tempArray[i] = list_[i];
  }
  tempArray[count_] = newShape;
  count_++;
  list_.swap(tempArray);
}

void CompositeShape::removeShape(const int index)
{
  if (index >= count_ || index < 0)
  {
    throw std::invalid_argument("Bad index");
  }
  if (count_ == 1)
  {
    clear();
  }
  else
    {
    std::unique_ptr < std::shared_ptr < rebrin::Shape >[] > tempArray
      (new std::shared_ptr < rebrin::Shape > [count_ - 1]);
    for (int i = 0; i < index; i++)
    {
      tempArray[i] = list_[i];
    }
    for (int i = index; i < count_ - 1; i++)
    {
      tempArray[i] = list_[i+1];
    }
    list_.swap(tempArray);
    count_--;
  }
}

void CompositeShape::clear()
{
  list_.reset();
  list_ = nullptr;
  count_ = 0;
}
