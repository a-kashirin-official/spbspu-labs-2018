#include "composite-shape.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>

strashko::CompositeShape::CompositeShape():
  count_(0),
  arrayOfShapes_(nullptr),
  angle_(0.0)
{
}

strashko::CompositeShape::CompositeShape(std::shared_ptr< strashko::Shape > shape):
  count_(0),
  arrayOfShapes_(nullptr),
  angle_(0.0)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Invalid pointer!");
  }
  addShape(shape);
}

strashko::CompositeShape::~CompositeShape()
{
  deleteAllShapes();
}

strashko::CompositeShape::CompositeShape(const strashko::CompositeShape & rhs) :
  count_(rhs.count_),
  arrayOfShapes_(new std::shared_ptr< strashko::Shape >[count_])
{
  for (int i = 0; i < count_; i++) {
    arrayOfShapes_[i] = rhs.arrayOfShapes_[i];
  }
}

strashko::CompositeShape::CompositeShape(strashko::CompositeShape && rhs) :
  count_(rhs.count_)
{
  arrayOfShapes_ = std::move(rhs.arrayOfShapes_);
  rhs.arrayOfShapes_ = nullptr;
  rhs.count_ = 0;
}

std::shared_ptr< strashko::Shape > & strashko::CompositeShape::operator[](const int i) const
{
  if (i >= count_) {
    throw std::out_of_range("Index out of range");
  }
  return arrayOfShapes_[i];
}

strashko::CompositeShape & strashko::CompositeShape::operator=(const strashko::CompositeShape & rhs)
{
  if (this != &rhs)
  {
    std::unique_ptr<std::shared_ptr<strashko::Shape>[]> tmp(new std::shared_ptr<strashko::Shape>[rhs.count_]);
    for (int i = 0; i < rhs.count_; i++)
    {
      tmp[i] = rhs.arrayOfShapes_[i];
    }
    arrayOfShapes_.swap(tmp);
    count_ = rhs.count_;
  }
  return *this;
}

strashko::CompositeShape & strashko::CompositeShape::operator=(strashko::CompositeShape && rhs)
{
  if (this == &rhs) {
    return *this;
  }
  count_ = rhs.count_;
  arrayOfShapes_.reset(new std::shared_ptr< strashko::Shape >[count_]);
  arrayOfShapes_ = std::move(rhs.arrayOfShapes_);
  rhs.arrayOfShapes_ = nullptr;
  rhs.count_ = 0;
  return *this;
}

double strashko::CompositeShape::getArea() const noexcept
{
  double area = 0.0;
  for (int i = 0; i < count_; ++i) {
    area += arrayOfShapes_[i]->getArea();
  }
  return area;
}

strashko::rectangle_t strashko::CompositeShape::getFrameRect() const noexcept
{
  if (count_ == 0) {
    return{{0, 0}, 0, 0};
  }
  else {
    strashko::rectangle_t standartRect = arrayOfShapes_[0]->getFrameRect();
    double minX = standartRect.pos.x - standartRect.width / 2.0;
    double maxX = standartRect.pos.x + standartRect.width / 2.0;
    double minY = standartRect.pos.y - standartRect.height / 2.0;
    double maxY = standartRect.pos.y + standartRect.height / 2.0;
    for (int i = 1; i < count_; ++i)
    {
      standartRect = arrayOfShapes_[i]->getFrameRect();
      if (minX > standartRect.pos.x - standartRect.width / 2.0) {
        minX = standartRect.pos.x - standartRect.width / 2.0 ;
      }
      if (maxX < standartRect.pos.x + standartRect.width / 2.0) {
        maxX = standartRect.pos.x + standartRect.width / 2.0;
      }
      if (minY > standartRect.pos.y - standartRect.height / 2.0) {
        minY = standartRect.pos.y - standartRect.height / 2.0;
      }
      if (maxY < standartRect.pos.y + standartRect.height / 2.0) {
        maxY = standartRect.pos.y + standartRect.height / 2.0;
      }
    }
    return {{((minX+maxX)/2.0), ((minY+maxY)/2.0)}, (maxX - minX), (maxY - minY)};
  }
}

void strashko::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < count_; ++i) {
    arrayOfShapes_[i]->move(dx, dy);
  }
}

void strashko::CompositeShape::move(const strashko::point_t &newcentre) noexcept
{
  const strashko::point_t pos = getFrameRect().pos;
  move(newcentre.x - pos.x, newcentre.y - pos.y);
}

void strashko::CompositeShape::scale(const double factor)
{
  if (factor < 0.0) {
    throw std::invalid_argument("Invalid factor!");
  }
  const strashko::point_t posNow = getFrameRect().pos;
  for (int i = 0; i < count_; ++i) {
    const strashko::point_t posShape = arrayOfShapes_[i]->getFrameRect().pos;
    arrayOfShapes_[i]->move((factor - 1) * (posShape.x - posNow.x), (factor - 1) * (posShape.y - posNow.y));
    arrayOfShapes_[i]->scale(factor);
  }
}

void strashko::CompositeShape::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
  const double sine = sin(angle * M_PI / 180);
  const double cosine = cos(angle * M_PI / 180);
  const strashko::point_t currPos = getFrameRect().pos;
  for (int i = 0; i < count_; ++i)
  {
    const strashko::point_t shapePos = arrayOfShapes_[i]->getFrameRect().pos;
    arrayOfShapes_[i]->move({(shapePos.x - currPos.x) * cosine - (shapePos.y - currPos.y) * sine + currPos.x,
      (shapePos.y - currPos.y) * cosine + (shapePos.x - currPos.x) * sine + currPos.y});
    arrayOfShapes_[i]->rotate(angle);
  }
}

void strashko::CompositeShape::addShape(const std::shared_ptr< strashko::Shape > shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Invalid pointer!");
  }
  for (int i = 0; i < count_; ++i) {
    if (shape == arrayOfShapes_[i]) {
      throw std::invalid_argument("This shape is already added!");
    }
  }
  std::unique_ptr< std::shared_ptr< strashko::Shape>[] > tmp(new std::shared_ptr< strashko::Shape >[count_ + 1]);
  for (int i = 0; i < count_; ++i) {
    tmp[i] = arrayOfShapes_[i];
  }
  tmp[count_++] = shape;
  arrayOfShapes_.swap(tmp);
}

void strashko::CompositeShape::removeShape(const int shapeNumber)
{
  if (count_ == 0) {
    throw std::out_of_range("Composite Shape is empty!");
  }
  else {
    if ((shapeNumber <= 0) || (shapeNumber >= count_)) {
      throw std::out_of_range("Invalid shape number!");
    }
  }
  if (count_ == 1) {
    deleteAllShapes();
  }
  else {
    std::unique_ptr< std::shared_ptr< strashko::Shape >[] > tmp(new std::shared_ptr< strashko::Shape >[count_ - 1]);
    for (int i = 0; i < (shapeNumber - 1); ++i) {
      tmp[i] = arrayOfShapes_[i];
    }
    for (int i = shapeNumber; i < count_; ++i) {
      tmp[i-1] = arrayOfShapes_[i];
    }
    arrayOfShapes_.swap(tmp);
    --count_;
  }
}

void strashko::CompositeShape::deleteAllShapes() noexcept
{
  arrayOfShapes_.reset();
  arrayOfShapes_ = nullptr;
  count_ = 0;
}

int strashko::CompositeShape::getCount() const noexcept
{
  return count_;
}

std::unique_ptr<strashko::Shape> strashko::CompositeShape::getCopy() const noexcept
{
  return std::unique_ptr<strashko::Shape>(new CompositeShape(*this));
}

void strashko::CompositeShape::printInfo() const
{
  std::cout << "CompositeShape:";
  std::cout << "  Size - " << count_ << ";  Area - " << getArea() << ";";
  std::cout << "  FrameRectangle:";
  const rectangle_t rectangle = getFrameRect();
  std::cout << " Width - " << rectangle.width << ", ";
  std::cout << "Height - " << rectangle.height << ", ";
  std::cout << "x = " << rectangle.pos.x << ", ";
  std::cout << "y = " << rectangle.pos.y << std::endl;
}
