#include "composite-shape.hpp"

#include <memory>
#include <stdexcept>
#include <math.h>

shapoval::CompositeShape::CompositeShape(std::shared_ptr <shapoval::Shape> new_shape):
  parts_(nullptr),
  size_(0),
  angle_(0)
{
  if (new_shape == nullptr)
  {
    throw std::invalid_argument("Null pointer!!");
  }
  addShape(new_shape);
}

shapoval::CompositeShape::CompositeShape(const shapoval::CompositeShape & copy):
  size_(copy.size_),
  angle_(copy.angle_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> CopyParts_(new std::shared_ptr<Shape>[size_]);
  {
    for (int i = 0; i < size_; ++i)
    {
      CopyParts_[i] = copy.parts_[i];
    }
  parts_.swap(CopyParts_);
  }
}

shapoval::CompositeShape & shapoval::CompositeShape::operator=(const shapoval::CompositeShape & copy)
{
  if (this != & copy)
  {
  size_ = copy.size_;
 std::unique_ptr< std::shared_ptr< shapoval::Shape >[] > new_parts_(new std::shared_ptr< shapoval::Shape >[size_]);
  for (int i = 0; i < size_; ++i)
    {
      new_parts_[i] = copy.parts_[i];
    }
    parts_.swap(new_parts_);
  }
  return *this;
}

shapoval::CompositeShape & shapoval::CompositeShape::operator=(shapoval::CompositeShape && move)
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

double shapoval::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += parts_[i]->getArea();
  }
  return area;
}

double shapoval::CompositeShape::getAngle() const noexcept
{
  return angle_;
}

shapoval::rectangle_t shapoval::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0)
  {
    return{{0, 0}, 0, 0};
  }
  else
  {
    shapoval::rectangle_t frameRect = parts_[0]->getFrameRect();
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

void shapoval::CompositeShape::move(const shapoval::point_t & new_centre) noexcept
{
  const shapoval::point_t currentCentre = getFrameRect().pos;
  move(new_centre.x - currentCentre.x, new_centre.y - currentCentre.y);
}

void shapoval::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < size_; ++i)
  {
    parts_[i]->move(dx, dy);
  }
}

void shapoval::CompositeShape::scale(const double k)
{
  if (k < 0)
  {
    throw std::invalid_argument("Invalid k!!");
  }
  const shapoval::point_t currentCentre = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const shapoval::point_t shapeCentre = parts_[i]->getFrameRect().pos;
    parts_[i]->move((k - 1) * (shapeCentre.x - currentCentre.x), (k - 1) * (shapeCentre.y - currentCentre.y));
    parts_[i]->scale(k);
  }
}

void shapoval::CompositeShape::rotate(const double a) noexcept
{
  angle_ += a;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360);
  }
  const double sine = sin(a * M_PI / 180);
  const double cosine = cos(a * M_PI / 180);
  const shapoval::point_t currentCentre = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    const shapoval::point_t shapeCentre = parts_[i]->getFrameRect().pos;
    parts_[i]->move({(shapeCentre.x - currentCentre.x) * cosine + (shapeCentre.y - currentCentre.y) * sine + currentCentre.x,
      (shapeCentre.y - currentCentre.y) * cosine + (shapeCentre.x - currentCentre.x) * sine + currentCentre.y});
    parts_[i]->rotate(a);
  } 
}

void shapoval::CompositeShape::addShape(const std::shared_ptr <shapoval::Shape> new_shape)
{
  if (new_shape == nullptr)
  {
    throw std::invalid_argument("Null pointer!!");
  }
  for (int i = 0; i < size_; ++i)
  {
    if (new_shape == parts_[i])
    {
      throw std::invalid_argument("This part is already in Composite Shape!!");
    }
  }
  std::unique_ptr <std::shared_ptr <shapoval::Shape>[] > new_parts(new std::shared_ptr <shapoval::Shape> [size_ + 1]);
  for (int i =0; i < size_; ++i)
  {
    new_parts[i] = parts_[i];
  }
  new_parts[size_++] = new_shape;
  parts_.swap(new_parts);
}

std::shared_ptr < shapoval::Shape > shapoval::CompositeShape::getShape(int const shapeNumber) const
{
  return parts_[shapeNumber];
}

void shapoval::CompositeShape::removeShape(const int shapeNumber)
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
    std::unique_ptr <std::shared_ptr <shapoval::Shape>[] > new_parts(new std::shared_ptr <shapoval::Shape> [size_ - 1]);
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

void shapoval::CompositeShape::deleteShapes() noexcept
{
  parts_.reset();
  parts_ = nullptr;
  size_ = 0;
}

int shapoval::CompositeShape::getSize() const noexcept
{
  return size_;
}
