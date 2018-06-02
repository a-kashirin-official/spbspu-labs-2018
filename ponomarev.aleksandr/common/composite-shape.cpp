#include "composite-shape.hpp"

#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace ponomarev;

CompositeShape::CompositeShape():
  figuresInArray_(0),
  figures_(nullptr)
{
}

CompositeShape::CompositeShape(const CompositeShape &obj):
  figuresInArray_(obj.figuresInArray_)
{
  std::unique_ptr <std::shared_ptr <Shape>[]> copyObj (new std::shared_ptr <Shape>[obj.getQuantity()]);
  for (size_t i = 0; i < obj.getQuantity(); i++)
  {
    copyObj[i] = obj.figures_[i];
  }
  figures_.swap(copyObj);
}

CompositeShape::CompositeShape(CompositeShape &&obj) noexcept:
  figuresInArray_(obj.getQuantity())
{
  figures_.swap(obj.figures_);
}

CompositeShape::~CompositeShape()
{
}

CompositeShape &CompositeShape::operator=(const CompositeShape &rhs)
{
  if (this != &rhs)
  {
    figuresInArray_ = rhs.getQuantity();
    std::unique_ptr <std::shared_ptr <Shape>[]> copyObj (new std::shared_ptr <Shape>[rhs.getQuantity()]);
    for (size_t i = 0; i < rhs.getQuantity(); i++)
    {
      copyObj[i] = rhs.figures_[i];
    }
    figures_.swap(copyObj);
  }
  return *this;
}

CompositeShape &CompositeShape::operator=(ponomarev::CompositeShape &&rhs) noexcept
{
  if (this != &rhs)
  {
    figuresInArray_ = rhs.figuresInArray_;
    figures_.swap(rhs.figures_);
    rhs.figures_ = nullptr;
    rhs.figuresInArray_ = 0;
  }
  return *this;
}

std::shared_ptr<Shape> CompositeShape::operator[](const unsigned int index) const
{
  if (index >= figuresInArray_ || index <= 0)
  {
    throw std::out_of_range("Index out of range of array;");
  }
  return figures_[index];
}

void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("invalid ptr;");
  }
  if (shape.get() == this)
  {
    throw std::invalid_argument("It's the same shape;");
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> temporaryArray (new std::shared_ptr<Shape>[figuresInArray_ + 1]);

  for (size_t i = 0; i < figuresInArray_; ++i)
  {
    temporaryArray[i] = figures_[i];
  }

  temporaryArray[figuresInArray_++] = shape;
  figures_.swap(temporaryArray);
}

void CompositeShape::removeShape(const unsigned int index)
{
  if (index >= figuresInArray_)
  {
    throw std::out_of_range("index out of range of array;");
  }
  if (figuresInArray_ <= 0)
  {
    throw std::invalid_argument("There is 0 shapes in composite shape");
  }

  figures_[figuresInArray_ - 1].reset();
  figuresInArray_--;
}

size_t CompositeShape::getQuantity() const
{
  return figuresInArray_;
}

void CompositeShape::move(const point_t &center)
{
  const  point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < figuresInArray_; i++)
  {
    figures_[i]->move(center.x - pos.x, center.y - pos.y);
  }
}

void CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < figuresInArray_; i++)
  {
    figures_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  if (coefficient != 1.0)
  {
    const point_t pos = getFrameRect().pos;
    for (size_t i = 0; i < figuresInArray_; i++)
    {
      figures_[i]->move({pos.x + (figures_[i]->getFrameRect().pos.x - pos.x) * coefficient,
        pos.y + (figures_[i]->getFrameRect().pos.y - pos.y) * coefficient});
      figures_[i]->scale(coefficient);
    }
  }
}

void CompositeShape::rotate(const double angle)
{
  double msin = sin(angle * M_PI / 180);
  double mcos = cos(angle * M_PI / 180);

  point_t center = getFrameRect().pos;
  for (size_t i = 0; i < 4; i++)
  {
    point_t shapeCenter = figures_[i]->getFrameRect().pos;
    double newX = center.x + (shapeCenter.x - center.x) * mcos - (shapeCenter.y - center.y) * msin;
    double newY = center.y + (shapeCenter.y - center.y) * mcos + (shapeCenter.x - center.x) * msin;

    figures_[i]->move({newX, newY});
    figures_[i]->rotate(angle);
  }
}

double CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < figuresInArray_; i++)
  {
    area += figures_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (figuresInArray_ == 0)
  {
    return  {0.0, 0.0, {0.0, 0.0}};
  }

  else
  {
    rectangle_t rectangle = figures_[0]->getFrameRect();

    double maxX = rectangle.pos.x + rectangle.width / 2.0;
    double maxY = rectangle.pos.y + rectangle.height / 2.0;
    double minX = rectangle.pos.x - rectangle.width / 2.0;
    double minY = rectangle.pos.y - rectangle.height / 2.0;


    for (size_t i = 1; i < figuresInArray_; i++) {
      rectangle = figures_[i]->getFrameRect();
      point_t pos = figures_[i]->getFrameRect().pos;

      double nowMaxX = pos.x + rectangle.width / 2.0;
      double nowMinX = pos.x - rectangle.width / 2.0;
      double nowMaxY = pos.y + rectangle.height / 2.0;
      double nowMinY = pos.y - rectangle.height / 2.0;
      if (nowMinX < minX) {
        minX = nowMinX;
      }
      if (nowMaxX > maxX) {
        maxX = nowMaxX;
      }
      if (nowMinY < minY) {
        minY = nowMinY;
      }
      if (nowMaxY > maxY) {
        maxY = nowMaxY;
      }
    }
    return {(maxX - minX), (maxY - minY), {((maxX + minX) / 2.0), ((maxY + minY) / 2.0)}};
  }
}

void CompositeShape::printShape() const
{
  std::cout << "CompositeShape";
}

MatrixShape CompositeShape::split() const
{
  MatrixShape matrix;
  for (size_t i = 0; i < figuresInArray_; i++)
  {
    matrix.addShape(figures_[i]);
  }
  return matrix;
}

