#include "composite-shape.hpp"

#include <math.h>
#include <stdexcept>

using namespace hvetsckovich;

hvetsckovich::CompositeShape::CompositeShape(const std::shared_ptr<Shape> shape):
  items_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null pointer exception");
  }

  addShape(shape);
}

hvetsckovich::CompositeShape::CompositeShape(const CompositeShape & compShape):
  items_(new std::shared_ptr<Shape>[compShape.size_]),
  size_(compShape.size_),
  angle_(compShape.angle_)
{
  for (int i = 0; i < size_; i++)
  {
    items_[i] = compShape.items_[i];
  }
}

hvetsckovich::CompositeShape::CompositeShape(CompositeShape && compShape):
  size_(compShape.size_),
  angle_(compShape.angle_)
{
  items_ = std::move(compShape.items_);

  compShape.items_ = nullptr;
  compShape.size_ = 0;
  compShape.angle_ = 0.0;
}

hvetsckovich::CompositeShape::~CompositeShape()
{
  deleteAllShapes();
}

CompositeShape & hvetsckovich::CompositeShape::operator=(const CompositeShape & compShape)
{
  if (this != &compShape)
  {
    size_ = compShape.size_;
    angle_ = compShape.angle_;
    items_.reset(new std::shared_ptr<Shape>[size_]);

    for (int i = 0; i < size_; i++)
    {
      items_[i] = compShape.items_[i];
    }
  }

  return * this;
}

CompositeShape & hvetsckovich::CompositeShape::operator=(CompositeShape && compShape)
{
  if (this != &compShape)
  {
    size_ = compShape.size_;
    angle_ = compShape.angle_;
    items_.reset(new std::shared_ptr<Shape>[size_]);
    items_ = std::move(compShape.items_);

    compShape.items_ = nullptr;
    compShape.size_ = 0;
    compShape.angle_ = 0.0;
  }

  return * this;
}

const std::shared_ptr<Shape> & hvetsckovich::CompositeShape::operator[](int index) const
{
  if ((index < 0) || (index >= size_))
  {
    throw std::invalid_argument("Index is out of bounds");
  }

  return items_[index];
}

point_t hvetsckovich::CompositeShape::getPos() const
{
  return getFrameRect().pos;
}

double hvetsckovich::CompositeShape::getArea() const
{
  double area = 0.0;

  for (int i = 0; i < size_; i++)
  {
    area += items_[i]->getArea();
  }

  return area;
}

rectangle_t hvetsckovich::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return { { 0.0, 0.0 }, 0.0, 0.0 };
  }
  else
  {
    rectangle_t shape = items_[0]->getFrameRect();

    double left = shape.pos.x - shape.width / 2;
    double right = shape.pos.x + shape.width / 2;
    double bottom = shape.pos.y - shape.height / 2;
    double top = shape.pos.y + shape.height / 2;

    for (int i = 1; i < size_; i++)
    {
      rectangle_t currShape = items_[i]->getFrameRect();
      double currLeft = currShape.pos.x - currShape.width / 2;
      double currRight = currShape.pos.x + currShape.width / 2;
      double currBottom = currShape.pos.y - currShape.height / 2;
      double currTop = currShape.pos.y + currShape.height / 2;

      if (currLeft < left)
      {
        left = currLeft;
      }
      if (currRight > right)
      {
        right = currRight;
      }
      if (currBottom < bottom)
      {
        bottom = currBottom;
      }
      if (currTop > top)
      {
        top = currTop;
      }
    }

    double width = right - left;
    double height = top - bottom;
    point_t pos = { (left + width / 2), (bottom + height / 2) };

    return { pos, width, height };
  }
}

void hvetsckovich::CompositeShape::move(const point_t & pos)
{
  const point_t currPos = getFrameRect().pos;

  move(pos.x - currPos.x, pos.y - currPos.y);
}

void hvetsckovich::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < size_; i++)
  {
    items_[i]->move(dx, dy);
  }
}

void hvetsckovich::CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Factor must be non-negative");
  }

  const point_t currPos = getFrameRect().pos;
  for (int i = 0; i < size_; i++)
  {
    const point_t shapePos = items_[i]->getFrameRect().pos;
    items_[i]->move((factor - 1) * (shapePos.x - currPos.x), (factor - 1) * (shapePos.y - currPos.y));
    items_[i]->scale(factor);
  }
}

void hvetsckovich::CompositeShape::rotate(const double degrees)
{
  angle_ += degrees;
  
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }

  const double sina = sin(degrees * M_PI / 180.0); // degrees -> radians
  const double cosa = cos(degrees * M_PI / 180.0);

  const point_t center = this->getFrameRect().pos;
  for (int i = 0; i < size_; i++)
  {
    const point_t shapeCenter = items_[i]->getFrameRect().pos;

    items_[i]->move({ (shapeCenter.x - center.x) * cosa - (shapeCenter.y - center.y) * sina + center.x,
    (shapeCenter.y - center.y) * cosa + (shapeCenter.x - center.x) * sina + center.y });

    items_[i]->rotate(degrees);
  }
}

void hvetsckovich::CompositeShape::deleteAllShapes()
{
  items_.reset();
  items_ = nullptr;
  size_ = 0;
}

int hvetsckovich::CompositeShape::getSize() const
{
  return size_;
}

void hvetsckovich::CompositeShape::addShape(const std::shared_ptr<Shape> shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Null pointer exception");
  }

  for (int i = 0; i < size_; i++)
  {
    if (shape == items_[i])
    {
      throw std::invalid_argument("Duplicated shape error");
    }
  }

  std::unique_ptr< std::shared_ptr< Shape >[] > tmp (new std::shared_ptr< Shape >[size_ + 1]);
  for (int i = 0; i < size_; i++)
  {
    tmp[i] = items_[i];
  }

  tmp[size_++] = shape;

  items_.swap(tmp);
}

void hvetsckovich::CompositeShape::deleteShape(const int index)
{
  if (size_ == 0)
  {
    throw std::out_of_range("Empty shape exception");
  }

  if ((index <= 0) || (index >= size_))
  {
    throw std::out_of_range("Index out of range exception");
  }

  if (size_ == 1)
  {
    deleteAllShapes();
    return;
  }

  std::unique_ptr <std::shared_ptr <Shape>[]> tmp (new std::shared_ptr <Shape>[size_ - 1]);
  for (int i = 0; i < index; i++)
  {
    tmp[i] = items_[i];
  }
  for (int i = index; i < size_ - 1; i++)
  {
    tmp[i] = items_[i + 1];
  }

  items_.swap(tmp);
  size_--;
}
