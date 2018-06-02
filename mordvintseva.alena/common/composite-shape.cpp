#include "composite-shape.hpp"
#include <stdexcept>

using namespace mordvintseva;
using std::invalid_argument;
using std::out_of_range;

CompositeShape::CompositeShape(Shape *shape):
  list_(new Shape *[1]),
  count_(1)
{
  list_[0] = shape;
}

CompositeShape::CompositeShape(const CompositeShape &rhs):
  list_(new Shape *[rhs.count_]),
  count_(rhs.count_)
{
  for (int i = 0; i < count_; i++)
  {
    list_[i] = rhs.list_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape &&rhs):
  list_(nullptr),
  count_(0)
{
  *this = std::move(rhs);
}

CompositeShape::~CompositeShape()
{
  this->clear();
}

double CompositeShape::getArea() const noexcept
{
  double area = 0.0;

  for (int i = 0; i < count_; i++)
  {
    area += list_[i]->getArea();
  }

  return area;
}

rectangle_t CompositeShape::getFrameRect() const noexcept
{
  if (!count_)
  {
    return { 0.0, 0.0, {0.0, 0.0}};
  } 
  else
  {
    rectangle_t frameRect = list_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2;
    double right = frameRect.pos.x + frameRect.width / 2;
    double top = frameRect.pos.y - frameRect.height / 2;
    double bottom = frameRect.pos.y + frameRect.height / 2;

    for (int i = 1; i < count_; i++)
    {
      frameRect = list_[i]->getFrameRect();
      double tmpLeft = frameRect.pos.x - frameRect.width / 2;
      double tmpRight = frameRect.pos.x + frameRect.width / 2;
      double tmpTop = frameRect.pos.y - frameRect.height / 2;
      double tmpBottom = frameRect.pos.y + frameRect.height / 2;
 
      if (tmpLeft < left)
      {
        left = tmpLeft;
      }
      if (tmpRight > right)
      {
        right = tmpRight;
      }
      if (tmpTop < top)
      {
        top = tmpTop;
      }
      if (tmpBottom > bottom)
      {
        bottom = tmpBottom;
      }
    }

    return { right - left, bottom - top, { (right - left) / 2, (bottom - top) / 2} };
  }
}

void CompositeShape::move(const point_t & point) noexcept
{
  point_t center_ = getFrameRect().pos;
  double dx = point.x - center_.x;
  double dy = point.y - center_.y;
  move(dx, dy);
}

void CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < count_; i++)
  {
    list_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  else
  {
    const point_t center = getFrameRect().pos;
    for (int i = 0; i < count_; i++)
    {
      const point_t shapeCenter = list_[i]->getFrameRect().pos;
      double dx = shapeCenter.x - center.x;
      double dy = shapeCenter.y - center.y;

      list_[i]->move({ center.x + factor * dx, center.y + factor * dy });
      list_[i]->scale(factor);
    }
  }
}

int CompositeShape::getCount() const noexcept
{
  return count_;
}

void CompositeShape::add(Shape *shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid argument");
  }

  for (int i = 0; i < count_; i++)
  {
    if (list_[i] == shape)
    {
      throw std::invalid_argument("Shape is already added");
    }
  }

  std::unique_ptr<Shape *[]> tmp (new Shape* [count_ + 1]);
  for (int i = 0; i < count_; i++)
  {
    tmp[i] = list_[i];
  }

  tmp[count_] = shape;
  count_++;
  list_.swap(tmp);
}

void CompositeShape::remove(const int index)
{
  if ((count_ <= 0) || (index >= count_))
  {
    throw std::out_of_range("Invalid index");
  }

  std::unique_ptr<Shape *[]> tmp (new Shape * [count_ - 1]);
  int count = 0;
  for (int i = 0; i < count_; i++)
  {
    if (i != index)
    {
      tmp[count] = list_[i];
      count++;
    }
  }

  list_.swap(tmp);
  count_--;
}

void CompositeShape::clear()
{
  list_.reset();
  list_ = nullptr;
  count_ = 0;
}

CompositeShape& CompositeShape::operator=(CompositeShape& rhs)
{
  if (this != &rhs)
  {
    count_= rhs.count_;
    list_.swap(rhs.list_);
  }
  return *this;
}

CompositeShape& CompositeShape::operator=(CompositeShape&& rhs)
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    list_.swap(rhs.list_);
    rhs.list_ = nullptr;
    rhs.count_ = 0;
  }

  return *this;
}

Shape* CompositeShape::operator[](const int index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Invalid index");
  }
  return list_[index];
}
