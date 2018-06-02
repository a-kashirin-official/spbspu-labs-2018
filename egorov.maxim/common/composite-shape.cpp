#include "composite-shape.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>

using namespace egorov;

CompositeShape::CompositeShape():
  cout_(0),
  figures_(nullptr)
{
}

CompositeShape::CompositeShape(const CompositeShape &object):
  cout_(object.getQuantity())
{
  std::unique_ptr<std::shared_ptr <Shape>[]> copyObject (new std::shared_ptr<Shape> [object.getQuantity()]);

  for (size_t i = 0; i < object.getQuantity(); i++)
  {
    copyObject[i] = object.figures_[i];
  }
  figures_.swap(copyObject);
}

CompositeShape::CompositeShape(CompositeShape &&object) noexcept:
  cout_(object.getQuantity())
{
  figures_.swap(object.figures_);
}

CompositeShape &CompositeShape::operator=(const CompositeShape &rhs)
{
  if (this != &rhs)
  {
    cout_ = rhs.getQuantity();
    std::unique_ptr <std::shared_ptr <Shape>[]> copyObject (new std::shared_ptr <Shape>[rhs.getQuantity()]);
    for (size_t i = 0; i < rhs.getQuantity(); i++)
    {
      copyObject[i] = rhs.figures_[i];
    }
    figures_.swap(copyObject);
  }
  return *this;
}

CompositeShape &CompositeShape::operator=(CompositeShape &&rhs) noexcept
{
  if (this != &rhs)
  {
    cout_ = rhs.cout_;
    figures_.swap(rhs.figures_);
    figures_.reset();
    rhs.cout_ = 0;
  }
  return *this;
}

std::shared_ptr<Shape> CompositeShape::operator[](const unsigned int index) const
{
  if (index >= cout_ || index <= 0){
    throw std::out_of_range("Invalid index");
  }
  return figures_[index];
}

void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("invalid pointer");
  }
  if (shape.get() == this)
  {
    throw std::invalid_argument("Such a figure already exists");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> temp (new std::shared_ptr<Shape>[cout_+1]);

  for (size_t i = 0; i < cout_; i++)
  {
    temp[i] = figures_[i];
  }

  temp[cout_] = shape;
  figures_.swap(temp);
  cout_++;
}

void CompositeShape::removeShape(const unsigned int index)
{
  if (index >= cout_)
  {
    throw std::invalid_argument("Invalid index");
  }

  if (cout_ <= 0)
  {
    throw std::invalid_argument("array is empty");
  }

  if (cout_ == 1)
  {
    clear();
    return;
  }
  else
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp (new std::shared_ptr<Shape>[cout_-1]);
    for (size_t i = 0; i < index; i++)
    {
      temp[i] = figures_[i];
    }
    for (size_t i = index; i < cout_-1; i++)
    {
      temp[i] = figures_[i+1];
    }
    figures_.swap(temp);
    cout_--;
  }
}

size_t CompositeShape::getQuantity() const noexcept
{
  return cout_;
}

double CompositeShape::getArea() const noexcept
{
  double area = 0.0;
  for (size_t i = 0; i < cout_; i++)
  {
    area += figures_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const noexcept
{
  if (cout_ <= 0)
  {
    return  {0, 0, {0, 0}};
  }
  else
  {
    rectangle_t rectangle = figures_[0]->getFrameRect();

    double maxX = rectangle.pos.x + rectangle.width / 2;
    double maxY = rectangle.pos.y + rectangle.height / 2;
    double minX = rectangle.pos.x - rectangle.width / 2;
    double minY = rectangle.pos.y - rectangle.height / 2;


    for (size_t i = 1; i < cout_; i++)
    {
      rectangle = figures_[i]->getFrameRect();
      point_t pos = figures_[i]->getFrameRect().pos;

      double newMaxX = pos.x + rectangle.width / 2;
      double newMinX = pos.x - rectangle.width / 2;
      double newMaxY = pos.y + rectangle.height / 2;
      double newMinY = pos.y - rectangle.height / 2;
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
    return {(maxX - minX), (maxY - minY), {((maxX + minX) / 2), ((maxY + minY) / 2)}};
  }
}

void CompositeShape::move(const point_t &point) noexcept
{
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < cout_; i++)
  {
    figures_[i]->move(point.x - pos.x, point.y - pos.y);
  }
}

void CompositeShape::move(const double deltax, const double deltay) noexcept
{
  for (size_t i = 0; i < cout_; i++)
  {
    figures_[i]->move(deltax,deltay);
  }
}

void CompositeShape::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < cout_; i++)
  {
    figures_[i]->move({pos.x + (figures_[i]->getFrameRect().pos.x - pos.x) * coefficient,
                 pos.y + (figures_[i]->getFrameRect().pos.y - pos.y) * coefficient});
    figures_[i]->scale(coefficient);
  }
}

void CompositeShape::rotate(double angle) noexcept
{
  double cosA = cos(angle * M_PI / 180);
  double sinA = sin(angle * M_PI / 180);

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < cout_; i++)
  {
  point_t shape_center = figures_[i]->getFrameRect().pos;

  figures_[i]->move({center.x + cosA * (shape_center.x - center.x) - sinA * (shape_center.y - center.y),
  center.y + cosA * (shape_center.y - center.y) + sinA * (shape_center.x - center.x)});

  figures_[i]->rotate(angle);
  }
}

void CompositeShape::clear() noexcept
{
  figures_.reset();
  figures_ = nullptr;
  cout_ = 0;
}

std::string CompositeShape::getName() const noexcept
{
  return "CompositeShape";
}
