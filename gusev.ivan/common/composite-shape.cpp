#include "composite-shape.hpp"
#include <cmath>
#include <stdexcept>
#include <memory>

gusev::CompositeShape::CompositeShape(const std::shared_ptr<gusev::Shape> figure):
  figures_(nullptr),
  count_(0)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("null ptr");
  }
  addShape(figure);
}

gusev::CompositeShape::~CompositeShape()
{
  removeAll();
}

void gusev::CompositeShape::removeAll()
{
  figures_.reset();
  figures_ = nullptr;
  count_ = 0;
}

int gusev::CompositeShape::getCount() const
{
  return count_;
}

void gusev::CompositeShape::addShape(const std::shared_ptr<Shape> figure)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("null ptr");
  }
  for (int i = 0; i < count_; ++i)
  {
    if (figure == figures_[i])
    {
      throw std::invalid_argument("such a figure already exists");
    }
  }
  std::unique_ptr < std::shared_ptr < gusev::Shape > [] > newFigure( new std::shared_ptr < gusev::Shape > [count_ + 1]);
  for (int i = 0; i < count_; ++i)
  {
    newFigure[i] = figures_[i];
  }
  newFigure[count_++] = figure;
  figures_.swap(newFigure);
}

void gusev::CompositeShape::removeFigure(const int index)
{
  if (count_ == 0)
  {
    throw std::out_of_range("empty");
  }
  else
  {
    if ((index <= 0) || (index >= count_))
    {
      throw std::out_of_range("invalid index");
    }
  }
  if (count_ == 1)
  {
    removeAll();
  }
  else
  {
    std::unique_ptr< std::shared_ptr< gusev::Shape > [] > newFigure(new std::shared_ptr< gusev::Shape > [count_ - 1]);
    for (int i = 0; i < (index - 1); ++i)
    {
      newFigure[i] = figures_[i];
    }
    for (int i = index; i < count_; ++i)
    {
      newFigure[i-1] = figures_[i];
    }
    figures_.swap(newFigure);
    --count_;
  }
}

double gusev::CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < count_; ++i)
  {
    area += figures_[i]->getArea();
  }
  return area;
}

void gusev::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < count_; ++i)
  {
    figures_[i]->move(dx, dy);
  }
}

void gusev::CompositeShape::move(const gusev::point_t & point)
{
  move(point.x - getFrameRect().pos.x, point.y - getFrameRect().pos.y);
}

gusev::rectangle_t gusev::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    return{ 0, 0, { 0, 0 } };
  }
  else
  {
    gusev::rectangle_t frameRect = figures_[0]->getFrameRect();
    double minX = frameRect.pos.x - frameRect.width / 2;
    double maxX = frameRect.pos.x + frameRect.width / 2;
    double minY = frameRect.pos.y - frameRect.height / 2;
    double maxY = frameRect.pos.y + frameRect.height / 2;
    
    for (int i =1; i < count_; ++i)
    {
      frameRect = figures_[i]->getFrameRect();
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
    return { (maxX - minX), (maxY - minY), { ((minX + maxX) / 2), ((maxY + minY) / 2) } };
  }
}

void gusev::CompositeShape::scale(const double coef)
{
  if (coef < 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
  const gusev::point_t pos = getFrameRect().pos;
  for (int i = 0; i < count_; ++i)
  {
    const gusev::point_t posFigure = figures_[i]->getCenter();
    figures_[i]->move((coef - 1) * (posFigure.x - pos.x), (coef - 1) * (posFigure.y - pos.y));
    figures_[i]->scale(coef);
  }
}

gusev::point_t gusev::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}
