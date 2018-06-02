#include "composite-shape.hpp"

#include <memory>
#include <stdexcept>

pichugina::CompositeShape::CompositeShape(std::shared_ptr <pichugina::Shape> shape_n):
  parts_(nullptr),
  size_(0)
{
  if (shape_n == nullptr)
  {
    throw std::invalid_argument("Null pointer!!");
  }
  addShape(shape_n);
}

pichugina::CompositeShape::CompositeShape(const pichugina::CompositeShape & copy):
  parts_(new std::shared_ptr <pichugina::Shape> [copy.size_]),
  size_(copy.size_)
  {
    for (int i = 0; i < size_; ++i)
    {
      parts_[i] = copy.parts_[i];
    }
  }

pichugina::CompositeShape & pichugina::CompositeShape::operator=(const pichugina::CompositeShape & copy)
{
  if (this != & copy)
  {
    std::unique_ptr< std::shared_ptr< pichugina::Shape >[] > new_parts_(new std::shared_ptr< pichugina::Shape >[copy.size_]);
    size_ = copy.size_;
    for (int i = 0; i < size_; ++i)
    {
      new_parts_[i] = copy.parts_[i];
    }
    parts_.swap(new_parts_);
  }
  return *this;
}


pichugina::CompositeShape & pichugina::CompositeShape::operator=(pichugina::CompositeShape && move)
{
  if (this != & move)
  {
    parts_.swap(move.parts_);
    size_ = move.size_;
    move.parts_.reset();
    move.size_ = 0;
  }
  return *this;
}



double pichugina::CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += parts_[i]->getArea();
  }
  return area;
}

pichugina::rectangle_t pichugina::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return{{0, 0}, 0, 0};
  }
  else
  {
    pichugina::rectangle_t frameRect = parts_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2;
    double right = frameRect.pos.x + frameRect.width / 2;
    double bottom = frameRect.pos.y - frameRect.height / 2;
    double top = frameRect.pos.y +frameRect.height / 2;

    for (int i = 1; i < size_; ++i)
    {
      frameRect = parts_[i]->getFrameRect();
      double new_left = frameRect.pos.x - frameRect.width / 2;
      double new_right = frameRect.pos.x + frameRect.width / 2;
      double new_bottom = frameRect.pos.y - frameRect.height / 2;
      double new_top = frameRect.pos.y +frameRect.height / 2;

      if (new_left < left)
      {
        left = new_left;
      }
      if (new_right > right)
      {
        right = new_right;
      }
      if (new_bottom < bottom)
      {
        bottom = new_bottom;
      }
      if (new_top > top)
      {
        top = new_top;
      }
    }
    return{{((left + right) / 2), ((top + bottom) / 2)}, (right - left), (top - bottom)};
  }
}

void pichugina::CompositeShape::move(const pichugina::point_t & new_centre)
{
  const pichugina::point_t currentCentre = getFrameRect().pos;
  move(new_centre.x - currentCentre.x, new_centre.y - currentCentre.y);
}

void pichugina::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < size_; ++i)
  {
    parts_[i]->move(dx, dy);
  }
}

void pichugina::CompositeShape::scale(const double factor)
{
  if (factor < 0)
  {
    throw std::invalid_argument("Invalid factor!!");
  }
  const pichugina::point_t currentCentre = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const pichugina::point_t shapeCentre = parts_[i]->getFrameRect().pos;
    parts_[i]->move((factor - 1) * (shapeCentre.x - currentCentre.x), (factor - 1) * (shapeCentre.y - currentCentre.y));
    parts_[i]->scale(factor);
  }
}

void pichugina::CompositeShape::addShape(const std::shared_ptr <pichugina::Shape> shape_n)
{
  if (shape_n == nullptr)
  {
    throw std::invalid_argument("Null pointer!!");
  }
  for (int i = 0; i < size_; ++i)
  {
    if (shape_n == parts_[i])
    {
      throw std::invalid_argument("This part is already in Composite Shape!!");
    }
  }
  std::unique_ptr <std::shared_ptr <pichugina::Shape>[] > new_parts(new std::shared_ptr <pichugina::Shape> [size_ + 1]);
  for (int i =0; i < size_; ++i)
  {
    new_parts[i] = parts_[i];
  }
  new_parts[size_++] = shape_n;
  parts_.swap(new_parts);
}

std::shared_ptr < pichugina::Shape > pichugina::CompositeShape::getShape(int const shapeNumber) const
{
  return parts_[shapeNumber];
}

void pichugina::CompositeShape::removeShape(const int shapeNumber)
{
  if (size_ == 0)
  {
    throw std::out_of_range("Composite Shape is empty!!");
  }
  else
  {
    if ((shapeNumber <= 0) || (shapeNumber >= size_))
    {
      throw std::out_of_range("Invalid number of shape!!");
    }
  }
  if (size_ == 1)
  {
    deleteShapes();
  }
  else
  {
    std::unique_ptr <std::shared_ptr <pichugina::Shape>[] > new_parts(new std::shared_ptr <pichugina::Shape> [size_ - 1]);
    for (int i =0; i < (shapeNumber - 1); ++i)
    {
      new_parts[i] = parts_[i];
    }
    for (int i = shapeNumber; i < size_; ++i)
    {
      new_parts[i-1] = parts_[i];
    }
    parts_.swap(new_parts);
    --size_;
  }
}

void pichugina::CompositeShape::deleteShapes()
{
  parts_.reset();
  parts_ = nullptr;
  size_ = 0;
}

int pichugina::CompositeShape::getSize() const
{
  return size_;
}
