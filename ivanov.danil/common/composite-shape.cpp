#include "composite-shape.hpp"

#include <iostream>
#include <stdexcept>

using namespace ivanov;

CompositeShape::CompositeShape():
  size_(0),
  shapes_(nullptr)
  {
  };

CompositeShape::CompositeShape(const std::shared_ptr<Shape> &newShape):
    size_(0),
    shapes_(nullptr)
  {
    if (newShape == nullptr)
    {
      throw std::invalid_argument("Empty shape!");
    }
    addShape(newShape);
  }

CompositeShape::CompositeShape(const CompositeShape & shape):
  size_(shape.getSize())
{
  std::unique_ptr<std::shared_ptr<Shape>[]> copyArr(new std::shared_ptr<Shape>[shape.getSize()]);
  for(size_t i = 0; i < shape.getSize(); i++)
  {
    copyArr[i] = shape.shapes_[i];
  }
  shapes_.swap(copyArr);
}

CompositeShape::CompositeShape(CompositeShape && Obj):
  size_(Obj.getSize())
{
  shapes_.swap(Obj.shapes_);
}

CompositeShape & CompositeShape::operator = (const CompositeShape & Obj)
{
  if (this != & Obj)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> copyArr(new std::shared_ptr<Shape>[Obj.getSize()]);
    for(size_t i = 0; i < Obj.getSize(); i++)
    {
      copyArr[i] = Obj.shapes_[i];
    }
    shapes_.swap(copyArr);
  }
  return *this;
}

CompositeShape & CompositeShape::operator = (CompositeShape && Obj)
{
  if (this != & Obj)
  {
    shapes_=std::move(Obj.shapes_);
    Obj.shapes_=(nullptr);
    Obj.size_=0;
  }
  return *this;
}

CompositeShape::~CompositeShape()
{
}

std::shared_ptr<Shape> CompositeShape::operator [] (const unsigned int index)
{
  if (index >= getSize())
  {
    throw std::out_of_range("Index out of range!");
  }
  return shapes_[index];
}

void CompositeShape::addShape(const std::shared_ptr<Shape> & newShape)
{
  if (!newShape)
  {
    throw std::invalid_argument("Invalid pointer!");
  }
  if (newShape.get() == this)
  {
    throw std::invalid_argument("The same shape");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> copyArr(new std::shared_ptr<Shape>[getSize() + 1]);

  for (size_t i = 0; i < getSize(); i++)
  {
    copyArr[i] = shapes_[i];
  }
  copyArr[size_] = newShape;
  shapes_.swap(copyArr);
  size_++;
}

void CompositeShape::deleteShape(const unsigned int index)
{
  if (index >= getSize())
  {
    std::out_of_range("Index out of range!");
  }
  if (getSize() == 0)
  {
    std::invalid_argument("CompositeShape is empty!");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> copyArr(new std::shared_ptr<Shape>[getSize() - 1]);
  for (size_t i = 0; i < index; i++)
  {
    copyArr[i] = shapes_[i];
  }
  for (size_t i = index; i < (getSize() - 1); i++)
  {
    copyArr[i] = shapes_[i+1];
  }
  shapes_.swap(copyArr);
  size_--;
}

double CompositeShape::getArea() const
{
  double compositeArea = 0.0;
  for (size_t i = 0; i < getSize(); i++)
  {
    compositeArea += shapes_[i]->getArea();
  }
  return compositeArea;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (getSize() == 0)
  {
    return {0.0, 0.0, {0.0, 0.0}};
  }
  rectangle_t rectangle = shapes_[0]->getFrameRect();
  double minX = rectangle.pos.x - rectangle.width / 2;
  double maxX = rectangle.pos.x + rectangle.width / 2;
  double minY = rectangle.pos.y - rectangle.height / 2;
  double maxY = rectangle.pos.y + rectangle.height / 2;

  for (size_t i = 0; i < getSize(); i++)
  {
    rectangle_t rectangle = shapes_[i]->getFrameRect();
    double newMinX = rectangle.pos.x - rectangle.width / 2;
    double newMaxX = rectangle.pos.x + rectangle.width / 2;
    double newMinY = rectangle.pos.y - rectangle.height / 2;
    double newMaxY = rectangle.pos.y + rectangle.height / 2;

    minX = std::min(minX, newMinX);
    maxX = std::max(maxX, newMaxX);
    minY = std::min(minY, newMinY);
    maxY = std::max(maxY, newMaxY);
  }
  return {maxX - minX, maxY - minY, {((minX + maxX) / 2.0), ((minY + maxY) / 2.0)}};
}

void CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < getSize(); i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void CompositeShape::move(const point_t & newCentrePoint)
{
  double dx = newCentrePoint.x - getFrameRect().pos.x;
  double dy = newCentrePoint.y - getFrameRect().pos.y;

  for (size_t i = 0; i < getSize(); i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Invalid ratio!");
  }

  for (size_t i = 0; i < getSize(); i++)
  {
    shapes_[i]->scale(ratio);
    shapes_[i]->move((shapes_[i]->getFrameRect().pos.x - getFrameRect().pos.x) * ratio,
                      (shapes_[i]->getFrameRect().pos.y - getFrameRect().pos.y) * ratio);
  }
}

size_t CompositeShape::getSize() const
{
  return size_;
}

void CompositeShape::printInfo()
{
  std::cout << "Area >> " << getArea() << std::endl
           << "Frame Width >> " << getFrameRect().width << std::endl
           << "Frame Height >> " << getFrameRect().height << std::endl
           << "Frame pos x >> " <<  getFrameRect().pos.x << std::endl
           << "Frame pos y >> " << getFrameRect().pos.y << std::endl
           << "Count of shapes >> " << getSize() << std::endl << std::endl;

}
