#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>

using namespace ivanov;
CompositeShape::CompositeShape(const std::shared_ptr<Shape> &shapeElement):
  shapeList_(new std::shared_ptr<Shape>[1]),
  shapeAmount_(0)
{
  if (shapeElement == nullptr)
  {
    //shapeList_.reset();
    throw std::invalid_argument("Error. Object does not exist.");
  }
  shapeList_[0] = shapeElement;
  shapeAmount_++;
}

CompositeShape::CompositeShape(const CompositeShape &composite_shape):
  shapeAmount_(composite_shape.shapeAmount_)
{
  std::unique_ptr <std::shared_ptr<Shape>[]> shapes_copy(new std::shared_ptr<Shape>[shapeAmount_]);

  for (size_t i = 0; i < shapeAmount_; i++)
  {
    shapes_copy[i] = composite_shape.shapeList_[i];
  }

   shapeList_.swap(shapes_copy);
}

CompositeShape & CompositeShape::operator=(const CompositeShape &composite_shape)
{
  if (this != &composite_shape)
  {
    shapeAmount_ = composite_shape.shapeAmount_;
    std::unique_ptr <std::shared_ptr<Shape>[]> shapes_copy(new std::shared_ptr<Shape>[shapeAmount_]);

    for (size_t i = 0; i < shapeAmount_; i++)
    {
      shapes_copy[i] = composite_shape.shapeList_[i];
    }

    shapeList_.swap(shapes_copy);
  }

  return *this;
}

void ivanov::CompositeShape::addShape(const std::shared_ptr<Shape> &shapeElement)
{
  if (shapeElement == nullptr)
  {
    throw std::invalid_argument("Error. Object does not exist.");
  }
  std::unique_ptr <std::shared_ptr<Shape>[]> new_arr(new std::shared_ptr<Shape>[shapeAmount_ + 1]);
  for (size_t i = 0; i < shapeAmount_; i++)
  {
    new_arr[i] = shapeList_[i];
  }
  new_arr[shapeAmount_] = shapeElement;
  shapeAmount_++;
  shapeList_.swap(new_arr);
}

void ivanov::CompositeShape::removeShape(const size_t index)
{
  if (shapeAmount_ <= 0)
  {
    throw std::out_of_range("Error. List of shapes is empty.");
  }
  if (index >= shapeAmount_)
  {
    throw std::out_of_range("Error. Index is out of range.");
  }
  if ((shapeAmount_ == 1) && (index == 0))
  {
    shapeList_.reset();
    shapeAmount_ = 0;
    return;
  }
  std::unique_ptr <std::shared_ptr<Shape>[]> new_arr(new std::shared_ptr<Shape>[shapeAmount_ - 1]);
  for (size_t i = 0; i < index; i++)
  {
    new_arr[i] = shapeList_[i];
  }
  for (size_t i = index; i < shapeAmount_ - 1; ++i)
  {
    new_arr[i] = shapeList_[i + 1];
  }
  shapeList_.swap(new_arr);
  shapeAmount_--;
}


double ivanov::CompositeShape::getArea() const noexcept
{
  double totalArea = 0.0;
  for (size_t i = 0; i < shapeAmount_; i++)
  {
    totalArea += shapeList_[i] -> getArea();
  }
  return totalArea;
}

ivanov::rectangle_t ivanov::CompositeShape::getFrameRect() const noexcept
{
  rectangle_t frameRect = shapeList_[0] -> getFrameRect();
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;
  for (size_t i = 1; i < shapeAmount_; i++)
  {
    frameRect = shapeList_[i] -> getFrameRect();
    if (maxX < frameRect.pos.x + frameRect.width / 2)
    {
      maxX = frameRect.pos.x + frameRect.width / 2;
    }
    if (minX > frameRect.pos.x - frameRect.width / 2)
    {
      minX = frameRect.pos.x - frameRect.width / 2;
    }
    if (maxY < frameRect.pos.y + frameRect.height / 2)
    {
      maxY = frameRect.pos.y + frameRect.height / 2;
    }
    if (minY > frameRect.pos.y - frameRect.height / 2)
    {
      minY = frameRect.pos.y - frameRect.height / 2;
    }
  }
  return {{(maxX + minX) / 2, (maxY + minY) / 2}, maxX - minX, maxY - minY};
}

void CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling.");
  }
  point_t comp_shapePos = getFrameRect().pos;
  for (size_t i = 0; i < shapeAmount_; i++)
  {
    point_t shapePos = shapeList_[i] -> getFrameRect().pos;
    shapeList_[i] -> move((factor - 1) * (shapePos.x - comp_shapePos.x), (factor - 1) * (shapePos.y - comp_shapePos.y));
    shapeList_[i] -> scale(factor);
  }
}

void CompositeShape::move(const point_t & pos) noexcept
{
  move(pos.x - getFrameRect().pos.x, pos.y - getFrameRect().pos.y);
}

void CompositeShape::move(const double dx, const double dy) noexcept
{
  for (size_t i = 0; i < shapeAmount_; i++)
  {
    shapeList_[i] -> move(dx, dy);
  }
}
