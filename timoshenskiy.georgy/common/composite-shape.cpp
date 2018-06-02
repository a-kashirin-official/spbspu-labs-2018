//
//  composite-shape.cpp
//  A3
//
//  Created by Георгий Тимошенский on 06.05.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#include "composite-shape.hpp"
#include <cmath>

timoshenskiy::CompositeShape::CompositeShape(std::shared_ptr < Shape > shape):
  shapes_(nullptr),
  size_(0),
  angle_(0.0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid_figures");
  }
  addShape(shape);
}

timoshenskiy::CompositeShape::CompositeShape(const CompositeShape &compositeShape):
  shapes_(new std::shared_ptr < timoshenskiy::Shape > [compositeShape.size_]),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  for (int i = 0; i < size_; ++i)
    {
    shapes_[i] = compositeShape.shapes_[i];
    }
}

timoshenskiy::CompositeShape::CompositeShape(CompositeShape && compositeShape):
  shapes_(nullptr),
  size_(compositeShape.size_),
  angle_(compositeShape.angle_)
{
  shapes_.swap(compositeShape.shapes_);
  compositeShape.deleteAllShapes();
}

timoshenskiy::CompositeShape &timoshenskiy::CompositeShape::operator = (const timoshenskiy::CompositeShape & compositeShape)
{
  if (this != &compositeShape)
  {
    std::unique_ptr< std::shared_ptr< timoshenskiy::Shape >[] >
      newShapes(new std::shared_ptr< timoshenskiy::Shape >[compositeShape.size_]);
    size_ = compositeShape.size_;
    for (int i = 0; i < size_; i++)
    {
      shapes_[i] = compositeShape.shapes_[i];
    }
  }
  return * this;
}

bool timoshenskiy::CompositeShape::operator == (const timoshenskiy::CompositeShape &compositeShape) const
{
  if ((this->size_ != compositeShape.size_) || (this->angle_ != compositeShape.angle_))
  {
    return false;
  }
  for (int i = 0; i < size_; ++i)
  {
    if (this->shapes_[i] != compositeShape.shapes_[i])
    {
      return false;
    }
  }
  return true;
}

bool timoshenskiy::CompositeShape::operator != (const timoshenskiy::CompositeShape &compositeShape) const
{
  if ((this->size_ != compositeShape.size_) || (this->angle_ != compositeShape.angle_))
  {
    return true;
  }
  for (int i = 0; i < size_; ++i)
  {
    if (this->shapes_[i] != compositeShape.shapes_[i])
    {
      return true;
    }
  }
  return false;
}

void timoshenskiy::CompositeShape::addShape(const std::shared_ptr < Shape > shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Nullptr");
  }

  for (int i = 0; i < size_; ++i)
  {
    if (shape == shapes_[i])
    {
      throw std::invalid_argument("Shape is already added");
    }
  }

  std::unique_ptr < std::shared_ptr < Shape > [] > newShapes(new std::shared_ptr < Shape > [size_ +1]);

  for (int i = 0; i < size_; ++i)
  {
    newShapes[i] = shapes_[i];
  }
  newShapes[size_++] = shape;
  shapes_.swap(newShapes);
}

double timoshenskiy::CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < size_; ++i)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

timoshenskiy::rectangle_t timoshenskiy::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return {0, 0, {0, 0}};
  }
  else
  {
    timoshenskiy::rectangle_t frameRect = shapes_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2.0;
    double right = frameRect.pos.x + frameRect.width / 2.0;
    double bottom = frameRect.pos.y - frameRect.height / 2.0;
    double top = frameRect.pos.y + frameRect.height / 2.0;

    for (int i = 0; i < size_; ++i)
    {
      frameRect = shapes_[i]->getFrameRect();
      double left_ = frameRect.pos.x - frameRect.width / 2.0;
      double right_ = frameRect.pos.x + frameRect.width / 2.0;
      double bottom_ = frameRect.pos.y - frameRect.height / 2.0;
      double top_ = frameRect.pos.y + frameRect.height / 2.0;

      if (left_ < left)
      {
        left = left_;
      }
      if (right_ > right)
      {
        right = right_;
      }
      if (bottom_ < bottom)
      {
        bottom = bottom_;
      }
      if (top_ > top)
      {
        top = top_;
      }
    }
    return {(right - left), (top - bottom), {((left + right) / 2.0), ((top + bottom) / 2.0)}};
  }
}

void timoshenskiy::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i]->move(dx, dy);
  }
}

void timoshenskiy::CompositeShape::move(const timoshenskiy::point_t &position)
{
   move(position.x - getFrameRect().pos.x, position.y - getFrameRect().pos.y);
}

void timoshenskiy::CompositeShape::scale(const double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument("Invalide scale coefficient");
  }
  else
  {
    const point_t FRAME_CENTER = getFrameRect().pos;
    for(int i = 0; i < size_; i++)
    {
      shapes_[i]->move((multiplier - 1.0) * (shapes_[i]->getFrameRect().pos.x - FRAME_CENTER.x),
                       (multiplier - 1.0) * (shapes_[i]->getFrameRect().pos.y - FRAME_CENTER.y));
      shapes_[i]->scale(multiplier);
    }
  }
}

void timoshenskiy::CompositeShape::deleteShape(const int shapeNumber)
{
  if ((shapeNumber <= 0) || (shapeNumber >= size_))
  {
    throw std::invalid_argument("Invalide shape number");
  }
  if (size_ == 1)
  {
    deleteAllShapes();
  }
  else
  {
    std::unique_ptr < std::shared_ptr < Shape > [] > newShapes(new std::shared_ptr< Shape > [size_ - 1]);
    for (int i = 0; i < (shapeNumber - 1); ++i)
    {
      newShapes[i] = shapes_[i];
    }
    for (int i = shapeNumber; i < size_; ++i)
    {
      newShapes[i-1] = shapes_[i];
    }
    shapes_.swap(newShapes);
    --size_;
  }
}

void timoshenskiy::CompositeShape::rotate(double degrees)
{
  angle_ += degrees;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }

  const point_t center = getFrameRect().pos;
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i]->rotate(degrees);
    shapes_[i]->move(rotatePoint(center, shapes_[i]->getFrameRect().pos, degrees));
  }
}

timoshenskiy::point_t timoshenskiy::CompositeShape::rotatePoint(const point_t &center, const point_t &p, double degrees)
{
  const double rad = degrees * M_PI / 180;
  const double newX = center.x + (p.x - center.x) * cos(rad) - (p.y - center.y) * sin(rad);
  const double newY = center.y + (p.x - center.x) * sin(rad) + (p.y - center.y) * cos(rad);
  return {newX, newY};
}

void timoshenskiy::CompositeShape::deleteAllShapes()
{
  shapes_.reset();
  shapes_ = nullptr;
  size_ = 0;
}

std::string timoshenskiy::CompositeShape::printInformation() const
{
  std::stringstream info;
  if (size_ != 0)
  {
    info << "\t Width of the frame: " << getFrameRect().width << "\n"
    << "\t Height of the frame: " << getFrameRect().height << "\n"
    << " \tCenter: "<< "(" << getFrameRect().pos.x << ","
    << getFrameRect().pos.y << ")" << "\n"
    << "\t Sum of the areas: " << getArea() << "\n"
    << "\t Angle: " << angle_ << "\n"
    << "\t Number of shapes: " << size_ << "\n"
    << "________________________" << std::endl;
  }
  else
  {
    info << "Number of shapes: " << size_ << std::endl;
  }
  return info.str();
}
