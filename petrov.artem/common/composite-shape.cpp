#include "composite-shape.hpp"

#include <memory>
#include <stdexcept>
#include <math.h>

petrov::CompositeShape::CompositeShape(std::shared_ptr< petrov::Shape > shape):
  elements_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  addShape(shape);
}

petrov::CompositeShape::CompositeShape(const petrov::CompositeShape & compositeShape):
  elements_(new std::shared_ptr< petrov::Shape >[compositeShape.size_]),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  for (int i = 0; i < size_; ++i)
  {
    elements_[i] = compositeShape.elements_[i];
  }
}

petrov::CompositeShape::~CompositeShape()
{
  deleteShapes();
}

petrov::CompositeShape & petrov::CompositeShape::operator=(const petrov::CompositeShape & compositeShape)
{
  if (this != & compositeShape)
  {
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > newElements(new std::shared_ptr< petrov::Shape >[size_]);
    for (int i = 0; i < size_; ++i)
    {
      newElements[i] = compositeShape.elements_[i];
    }
    elements_.swap(newElements);
  }
  return *this;
}

double petrov::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += elements_[i]->getArea();
  }
  return area;
}

petrov::rectangle_t petrov::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return{{0, 0}, 0, 0};
  }
  else
  {
    petrov::rectangle_t frameRect = elements_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2.0;
    double right = frameRect.pos.x + frameRect.width / 2.0;
    double bottom = frameRect.pos.y - frameRect.height / 2.0;
    double top = frameRect.pos.y + frameRect.height / 2.0;

    for (int i = 1; i < size_; ++i)
    {
      frameRect = elements_[i]->getFrameRect();
      double newLeft = frameRect.pos.x - frameRect.width / 2.0;
      double newRight = frameRect.pos.x + frameRect.width / 2.0;
      double newBottom = frameRect.pos.y - frameRect.height / 2.0;
      double newTop = frameRect.pos.y + frameRect.height / 2.0;

      if (newLeft < left)
      {
        left = newLeft;
      }
      if (newRight > right)
      {
        right = newRight;
      }
      if (newBottom < bottom)
      {
        bottom = newBottom;
      }
      if (newTop > top)
      {
        top = newTop;
      }
    }
    return{{((left + right) / 2.0), ((top + bottom) / 2.0)}, (right - left), (top - bottom)};
  }
}

void petrov::CompositeShape::move(const petrov::point_t & pos) noexcept
{
  const petrov::point_t currPos = getFrameRect().pos;
  move(pos.x - currPos.x, pos.y - currPos.y);
}

void petrov::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < size_; ++i)
  {
    elements_[i]->move(dx, dy);
  }
}

void petrov::CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  const petrov::point_t currPos = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const petrov::point_t shapePos = elements_[i]->getFrameRect().pos;
    elements_[i]->move((factor - 1) * (shapePos.x - currPos.x), (factor - 1) * (shapePos.y - currPos.y));
    elements_[i]->scale(factor);
  }
}

void petrov::CompositeShape::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
  const double sine = sin(angle * M_PI / 180);
  const double cosine = cos(angle * M_PI / 180);
  const petrov::point_t currPos = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const petrov::point_t shapePos = elements_[i]->getFrameRect().pos;
    elements_[i]->move({(shapePos.x - currPos.x) * cosine - (shapePos.y - currPos.y) * sine + currPos.x,
      (shapePos.y - currPos.y) * cosine + (shapePos.x - currPos.x) * sine + currPos.y});
    elements_[i]->rotate(angle);
  }
}

void petrov::CompositeShape::addShape(const std::shared_ptr< petrov::Shape > shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null pointer");
  }
  for (int i = 0; i < size_; ++i)
  {
    if (shape == elements_[i])
    {
      throw std::invalid_argument("This shape is already added in Composite Shape");
    }
  }
  std::unique_ptr< std::shared_ptr< petrov::Shape >[] > newElements(new std::shared_ptr< petrov::Shape >[size_ + 1]);
  for (int i = 0; i < size_; ++i)
  {
    newElements[i] = elements_[i];
  }
  newElements[size_++] = shape;
  elements_.swap(newElements);
}

void petrov::CompositeShape::removeShape(const int shapeNumber)
{
  if (size_ == 0)
  {
    throw std::out_of_range("Composite Shape is empty");
  }
  else
  {
    if ((shapeNumber <= 0) || (shapeNumber >= size_))
    {
      throw std::out_of_range("Invalid shape number");
    }
  }
  if (size_ == 1)
  {
    deleteShapes();
  }
  else
  {
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > newElements(new std::shared_ptr< petrov::Shape >[size_ - 1]);
    for (int i = 0; i < (shapeNumber - 1); ++i)
    {
      newElements[i] = elements_[i];
    }
    for (int i = shapeNumber; i < size_; ++i)
    {
      newElements[i-1] = elements_[i];
    }
    elements_.swap(newElements);
    --size_;
  }
}

void petrov::CompositeShape::deleteShapes() noexcept
{
  elements_.reset();
  elements_ = nullptr;
  size_ = 0;
}

int petrov::CompositeShape::getSize() const noexcept
{
  return size_;
}
