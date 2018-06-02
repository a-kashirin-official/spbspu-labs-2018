#include "composite-shape.hpp"
#include <memory>
#include <stdexcept>
#include <math.h>

volkov::CompositeShape::CompositeShape(std::shared_ptr <volkov::Shape> shape_n):
  parts_(nullptr),
  size_(0)
{
  if (shape_n == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  addShape(shape_n);
}

volkov::CompositeShape::CompositeShape(const volkov::CompositeShape & copy):
  size_(copy.size_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> CopyParts_(new std::shared_ptr<Shape>[copy.size_]);
  for (int i = 0; i < size_; ++i)
  {
    CopyParts_[i] = copy.parts_[i];
  }
  parts_.swap(CopyParts_); 
}

volkov::CompositeShape & volkov::CompositeShape::operator=(const volkov::CompositeShape & copy)
{
  if (this == & copy)
  {
    return *this;
  }
  
  std::unique_ptr< std::shared_ptr< volkov::Shape >[] >new_parts(new std::shared_ptr< volkov::Shape >[copy.size_]);
  size_ = copy.size_;
  for (int i = 0; i < size_; ++i)
  {
    new_parts[i] = copy.parts_[i];
  }
  parts_.swap(new_parts);
  return *this;
}

volkov::CompositeShape & volkov::CompositeShape::operator=(volkov::CompositeShape && move)
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

double volkov::CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += parts_[i]->getArea();
  }
  return area;
}

volkov::rectangle_t volkov::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return{{0, 0}, 0, 0};
  }
  else
  {
    volkov::rectangle_t frameRect = parts_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2;
    double right = frameRect.pos.x + frameRect.width / 2;
    double bottom = frameRect.pos.y - frameRect.height / 2;
    double top = frameRect.pos.y +frameRect.height / 2;

    for (int i = 1; i < size_; ++i)
    {
      frameRect = parts_[i]->getFrameRect();
      double left_n = frameRect.pos.x - frameRect.width / 2;
      double right_n = frameRect.pos.x + frameRect.width / 2;
      double bottom_n = frameRect.pos.y - frameRect.height / 2;
      double top_n = frameRect.pos.y +frameRect.height / 2;

      if (left_n < left)
      {
        left = left_n;
      }
      if (right_n > right)
      {
        right = right_n;
      }
      if (bottom_n < bottom)
      {
        bottom = bottom_n;
      }
      if (top_n > top)
      {
        top = top_n;
      }
    }
    return{{((left + right) / 2), ((top + bottom) / 2)}, (right - left), (top - bottom)};
  }
}

void volkov::CompositeShape::move(const volkov::point_t & centre_n)
{
  const volkov::point_t currentCentre = getFrameRect().pos;
  move(centre_n.x - currentCentre.x, centre_n.y - currentCentre.y);
}

void volkov::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < size_; ++i)
  {
    parts_[i]->move(dx, dy);
  }
}

void volkov::CompositeShape::scale(const double f)
{
  if (f < 0)
  {
    throw std::invalid_argument("Invalid f");
  }
  const volkov::point_t currentCentre = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const volkov::point_t shapeCentre = parts_[i]->getFrameRect().pos;
    parts_[i]->move((f - 1) * (shapeCentre.x - currentCentre.x), (f - 1) * (shapeCentre.y - currentCentre.y));
    parts_[i]->scale(f);
  }
}

void volkov::CompositeShape::addShape(const std::shared_ptr <volkov::Shape> shape_n)
{
  if (shape_n == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  for (int i = 0; i < size_; ++i)
  {
    if (shape_n == parts_[i])
    {
      throw std::invalid_argument("This part is already in composite shape");
    }
  }
  std::unique_ptr <std::shared_ptr <volkov::Shape>[] > new_parts(new std::shared_ptr <volkov::Shape> [size_ + 1]);
  for (int i =0; i < size_; ++i)
  {
    new_parts[i] = parts_[i];
  }
  new_parts[size_++] = shape_n;
  parts_.swap(new_parts);
}

std::shared_ptr < volkov::Shape > volkov::CompositeShape::getShape(int const shN) const
{
  return parts_[shN];
}

void volkov::CompositeShape::removeShape(const int shN)
{
  if (size_ == 0)
  {
    throw std::out_of_range("Composite shape is empty");
  }
  else
  {
    if ((shN <= 0) || (shN >= size_))
    {
      throw std::out_of_range("Invalid number");
    }
  }
  if (size_ == 1)
  {
    deleteShapes();
  }
  else
  {
    std::unique_ptr <std::shared_ptr <volkov::Shape>[] > new_parts(new std::shared_ptr <volkov::Shape> [size_ - 1]);
    for (int i =0; i < (shN - 1); ++i)
    {
      new_parts[i] = parts_[i];
    }
    for (int i = shN; i < size_; ++i)
    {
      new_parts[i-1] = parts_[i];
    }
    parts_.swap(new_parts);
    --size_;
  }
}

void volkov::CompositeShape::deleteShapes()
{
  parts_.reset();
  parts_ = nullptr;
  size_ = 0;
}

int volkov::CompositeShape::getSize() const
{
  return size_;
}
