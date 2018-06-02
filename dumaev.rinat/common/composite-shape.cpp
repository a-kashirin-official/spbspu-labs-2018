#include "composite-shape.hpp"
#include <memory>
#include <stdexcept>
#include <cmath>

using namespace dumaev;

CompositeShape::CompositeShape(const std::shared_ptr < Shape > shape):
  shapes_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid shape");
  }
  addShape(shape);
}

CompositeShape::CompositeShape(const CompositeShape &compositeShape)
  {
  shapes_ = std::unique_ptr < std::shared_ptr < Shape > [] > (new std::shared_ptr < Shape > [compositeShape.size_]);
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i] = compositeShape.shapes_[i];
  }
}

CompositeShape &CompositeShape::operator = (const CompositeShape &compositeShape)
{
  if (this != &compositeShape)
  {
    shapes_.reset(new std::shared_ptr < Shape > [compositeShape.size_]);
    size_ = compositeShape.size_;
    angle_ = compositeShape.angle_;
    for (int i = 0; i < size_; ++i)
    {
      shapes_[i] = compositeShape.shapes_[i];
    }
  }
  return * this;
}

void CompositeShape::addShape(const std::shared_ptr < Shape > shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid shape");
  }
  std::unique_ptr < std::shared_ptr < Shape > [] > newShapes (new std::shared_ptr < Shape > [size_ + 1]);
  for (int i = 0; i < size_; ++i)
  {
    newShapes[i] = shapes_[i];
  }
  newShapes[size_++] = shape;
  shapes_.swap(newShapes);
}

double CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return {{0.0, 0.0}, 0.0 , 0.0};
  }
  else
  {
    rectangle_t frameRect = shapes_[0]->getFrameRect();
    double minX = frameRect.pos.x - frameRect.width / 2;
    double maxX = frameRect.pos.x + frameRect.width / 2;
    double minY = frameRect.pos.y - frameRect.height / 2;
    double maxY = frameRect.pos.y + frameRect.height / 2;

    for (int i = 0; i < size_; ++i)
    {
      double newMinX = frameRect.pos.x - frameRect.width / 2;
      double newMaxX = frameRect.pos.x + frameRect.width / 2;
      double newMinY = frameRect.pos.y - frameRect.height / 2;
      double newMaxY = frameRect.pos.y + frameRect.height / 2;

      if (newMinX < minX)
      {
        minX = newMinX;
      }
      if (newMaxX > maxX)
      {
        maxX = newMaxX;
      }
      if (newMinY < minY)
      {
        minY = newMinY;
      }
      if (newMaxY > maxY)
      {
        maxY = newMaxY;
      }
    }
    return {{(maxX + minX) /2, (maxY + minY) /2}, maxX - minX, maxY - minY};
  }
}

void CompositeShape::move(const point_t &point) noexcept
{
  point_t centre = getFrameRect().pos;
  move(point.x - centre.x, point.y - centre.y);
}

void CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(const double coefficient)
{
  if (coefficient < 0)
  {
    throw std::invalid_argument("Coefficient must be positive or zero");
  }
  point_t centre = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i]->scale(coefficient);
    shapes_[i]->move({(shapes_[i]->getPos().x - centre.x) * coefficient + centre.x,
                      (shapes_[i]->getPos().y - centre.y) * coefficient + centre.y});
  }
}

point_t CompositeShape::getPos() const noexcept
{
  return getFrameRect().pos;
}

void CompositeShape::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
  const double sine = sin(angle * M_PI / 180);
  const double cosine = cos(angle * M_PI / 180);
  const point_t centre = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const point_t shapePos = shapes_[i]->getFrameRect().pos;
    shapes_[i]->move({(shapePos.x - centre.x) * cosine - (shapePos.y - centre.y) * sine + centre.x,
                        (shapePos.y - centre.y) * cosine + (shapePos.x - centre.x) * sine + centre.y});
    shapes_[i]->rotate(angle);
  }
}
