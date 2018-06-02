#include "composite-shape.hpp"

#include <math.h>
#include <stdexcept>

using namespace styagov;

// Default empty constructor
styagov::CompositeShape::CompositeShape() noexcept:
  shapes_(nullptr),
  size_(0),
  angle_(0.0)
{

}

// Simple constructor that initializes the object.
styagov::CompositeShape::CompositeShape(const std::shared_ptr <styagov::Shape> shape):
  shapes_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Composite Shape: Null pointer was passed");
  }

  this->add(shape);
}

// Copy constructor
styagov::CompositeShape::CompositeShape(const styagov::CompositeShape & object) noexcept:
  shapes_(new std::shared_ptr <styagov::Shape>[object.size_]),
  size_(object.size_),
  angle_(object.angle_)
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] = object.shapes_[i];
  }
}

// Move constructor
styagov::CompositeShape::CompositeShape(styagov::CompositeShape && object) noexcept:
  size_(object.size_),
  angle_(object.angle_)
{
  shapes_ = std::move(object.shapes_);

  object.shapes_ = nullptr;
  object.size_ = 0;
  object.angle_ = 0.0;
}

styagov::CompositeShape::~CompositeShape()
{
  this->clearShapes();
}

// Copy assignment operator overloading
styagov::CompositeShape & styagov::CompositeShape::operator=(const styagov::CompositeShape & object)
{
  if (this == &object)
  {
    return * this;
  }

  shapes_.reset(new std::shared_ptr <styagov::Shape>[size_]);
  size_ = object.size_;
  angle_ = object.angle_;

  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] = object.shapes_[i];
  }

  return * this;
}

// Move assignment operator overloading
styagov::CompositeShape & styagov::CompositeShape::operator=(styagov::CompositeShape && object) noexcept
{
  if (this == &object)
  {
    return * this;
  }

  shapes_.reset(new std::shared_ptr< styagov::Shape >[size_]);
  shapes_ = std::move(object.shapes_);
  size_ = object.size_;
  angle_ = object.angle_;

  object.shapes_ = nullptr;
  object.size_ = 0;
  object.angle_ = 0.0;

  return * this;
}

// Addition operator overloading
styagov::CompositeShape styagov::CompositeShape::operator+(const CompositeShape & object) noexcept
{
  for (size_t i = 0; i < object.size_; i++)
  {
    this->add(object.shapes_[i]);
  }

  return * this;
}

// Index operator overloading
const std::shared_ptr<styagov::Shape> & styagov::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::invalid_argument("Composite Shape: Index is out of range");
  }

  return shapes_[index];
}

std::unique_ptr <std::shared_ptr <styagov::Shape>[]> styagov::CompositeShape::getShapes() const
{
  std::unique_ptr <std::shared_ptr <styagov::Shape>[]> shapes(new std::shared_ptr <styagov::Shape>[size_]);
  for (size_t i = 0; i < size_; i++)
  {
    shapes[i] = shapes_[i];
  }

  return shapes;
}

styagov::point_t styagov::CompositeShape::getPos() const noexcept
{
  return getFrameRect().pos;
}

double styagov::CompositeShape::getArea() const noexcept
{
  double shapesAreasSum = 0;

  for (size_t i = 0; i < size_; i++)
  {
    shapesAreasSum += shapes_[i]->getArea();
  }

  return shapesAreasSum;
}

styagov::rectangle_t styagov::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return { { 0.0, 0.0 }, 0.0, 0.0 };
  }

  styagov::rectangle_t shape = shapes_[0]->getFrameRect();

  double leftMost = shape.pos.x - shape.width / 2;
  double rightMost = shape.pos.x + shape.width / 2;
  double bottomMost = shape.pos.y - shape.height / 2;
  double topMost = shape.pos.y + shape.height / 2;

  for (size_t i = 1; i < size_; i++)
  {
    shape = shapes_[i]->getFrameRect();
    double left = shape.pos.x - shape.width / 2;
    double right = shape.pos.x + shape.width / 2;
    double bottom = shape.pos.y - shape.height / 2;
    double top = shape.pos.y + shape.height / 2;

    if (left < leftMost)
    {
      leftMost = left;
    }
    if (right > rightMost)
    {
      rightMost = right;
    }
    if (bottom < bottomMost)
    {
      bottomMost = bottom;
    }
    if (top > topMost)
    {
      topMost = top;
    }
  }

  double width = rightMost - leftMost;
  double height = topMost - bottomMost;
  styagov::point_t center = {(leftMost + width / 2), (bottomMost + height / 2)};

  return { center, width, height };
}

void styagov::CompositeShape::move(const styagov::point_t & pos) noexcept
{
  const styagov::point_t currentCenterPosition = this->getFrameRect().pos;
  this->move(pos.x - currentCenterPosition.x, pos.y - currentCenterPosition.y);
}

void styagov::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void styagov::CompositeShape::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Composite Shape: Ratio value must be non-negative");
  }

  const styagov::point_t currentCenterPosition = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    const styagov::point_t shapeCenterPosition = shapes_[i]->getFrameRect().pos;

    shapes_[i]->move(
      (ratio - 1) * (shapeCenterPosition.x - currentCenterPosition.x),
      (ratio - 1) * (shapeCenterPosition.y - currentCenterPosition.y)
    );

    shapes_[i]->scale(ratio);
  }
}

void styagov::CompositeShape::rotate(const double alpha) noexcept
{
  angle_ += alpha;
  
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }

  // translating degrees into radians
  const double sinAlpha = sin(alpha * M_PI / 180.0);
  const double cosAlpha = cos(alpha * M_PI / 180.0);

  const styagov::point_t center = this->getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    const styagov::point_t shapeCenter = shapes_[i]->getFrameRect().pos;

    shapes_[i]->move({
      (shapeCenter.x - center.x) * cosAlpha - (shapeCenter.y - center.y) * sinAlpha + center.x,
      (shapeCenter.y - center.y) * cosAlpha + (shapeCenter.x - center.x) * sinAlpha + center.y
    });

    shapes_[i]->rotate(alpha);
  }
}

void styagov::CompositeShape::clearShapes() noexcept
{
  shapes_.reset();
  shapes_ = nullptr;
  size_ = 0;
}

size_t styagov::CompositeShape::getSize() const noexcept
{
  return size_;
}

void styagov::CompositeShape::add(const std::shared_ptr <styagov::Shape> shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Composite Shape: Null pointer was passed");
  }

  for (size_t i = 0; i < size_; i++)
  {
    if (shape == shapes_[i])
    {
      throw std::invalid_argument("Composite Shape: Duplicate shape error");
    }
  }

  std::unique_ptr <std::shared_ptr <styagov::Shape>[]> tmp (new std::shared_ptr <styagov::Shape>[size_ + 1]);
  for (size_t i = 0; i < size_; i++)
  {
    tmp[i] = shapes_[i];
  }

  tmp[size_++] = shape;

  shapes_.swap(tmp);
}

void styagov::CompositeShape::remove(const size_t index)
{
  if (size_ == 0)
  {
    throw std::out_of_range("Composite Shape: Shape is empty");
  }

  if (index >= size_)
  {
    throw std::out_of_range("Composite Shape: Index is out of range");
  }

  if (size_ == 1)
  {
    this->clearShapes();
    
    return;
  }

  std::unique_ptr <std::shared_ptr <styagov::Shape>[]> tmp (new std::shared_ptr <styagov::Shape>[size_ - 1]);
  for (size_t i = 0; i < index; i++)
  {
    tmp[i] = shapes_[i];
  }
  for (size_t i = index; i < size_ - 1; i++)
  {
    tmp[i] = shapes_[i + 1];
  }

  shapes_.swap(tmp);
  size_--;
}
