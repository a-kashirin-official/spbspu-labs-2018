#include "composite-shape.hpp"
#include <memory>
#include <iostream>
namespace vasilev
{
CompositeShape::CompositeShape(const std::shared_ptr<Shape> shape):
  arr_(nullptr),
  quant_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Ptr is empty");
  }
  addShape(shape);
}
CompositeShape::CompositeShape(const CompositeShape &figure):
  arr_(new std::shared_ptr<Shape>[figure.quant_]),
  quant_(figure.quant_)
{
  for(size_t i=0; i < quant_; i++)
  {
    arr_[i] = figure.arr_[i];
  }
}
CompositeShape::CompositeShape(CompositeShape &&figure):
  arr_(nullptr),
  quant_(figure.quant_)
{
  arr_.swap(figure.arr_);
  figure.quant_ = 0;
  figure.arr_.reset();
}

Shape &CompositeShape::operator[](size_t n) const
{
  if (n>=quant_)
  {
    std::invalid_argument("Out of range");
  }
  return *arr_[n];
}
CompositeShape &CompositeShape::operator=(const CompositeShape &figure)
{
  arr_.reset(new std::shared_ptr<Shape>[figure.quant_]);
  for (size_t i = 0; i < figure.quant_; i++)
  {
    arr_[i] = figure.arr_[i];
  }
  quant_ = figure.quant_;
  return *this;
}
CompositeShape &CompositeShape::operator=(CompositeShape &&figure)
{
  arr_.swap(figure.arr_);
  quant_ = figure.quant_;
  figure.quant_ = 0;
  figure.arr_.reset();
  return *this;
}
void CompositeShape::addShape(const std::shared_ptr<Shape> newshape)
{
  if (newshape == nullptr)
  {
    throw std::invalid_argument("Wrong ptr");
  }
  for (size_t i = 0; i < quant_; i++)
  {
    if (newshape == arr_[i])
    {
      throw std::invalid_argument("Shape is already in the array");
    }
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newcomposite(new std::shared_ptr<Shape>[quant_ + 1]);
  for (size_t i = 0; i < quant_; i++)
  {
    newcomposite[i] = arr_[i];
  }
  newcomposite[quant_++] = newshape;
  arr_.swap(newcomposite);
}
void CompositeShape::deleteShape(size_t n)
{
  if(quant_ == 0)
  {
    throw std::out_of_range("Empty composite shape");
  }
  else if (n > quant_)
  {
    throw std::invalid_argument("Not existing cell");
  }
  else if (quant_== 1)
  {
    arr_.reset();
    quant_ = 0;
  }
  else
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> newcomposite(new std::shared_ptr<Shape>[quant_ - 1]);
    for(size_t i = 0; i < (n - 1); i++)
    {
      newcomposite[i] = arr_[i];
    }
    for(size_t i = n; i < quant_;++i)
    {
      newcomposite[i-1] = arr_[i];
    }
    arr_.swap(newcomposite);
    --quant_;
  }
}
double CompositeShape::getArea() const
{
  double areas = 0;
  for (size_t i = 0; i < quant_; i++)
  {
    areas += arr_[i]->getArea();
  }
  return areas;
}
rectangle_t CompositeShape::getFrameRect() const
{

  if (quant_ == 0)
  {
    return {0, 0, {0, 0}};
  }
  else
  {
    rectangle_t frame = arr_[0]->getFrameRect();
    double right = frame.pos.x + frame.width / 2.0;
    double left = frame.pos.x - frame.width / 2.0;
    double top = frame.pos.y + frame.height / 2.0;
    double bottom = frame.pos.y - frame.height / 2.0;
    for(size_t i = 1; i < quant_; ++i)
    {
      frame = arr_[i]->getFrameRect();
      double max_right = frame.pos.x + frame.width / 2.0;
      double max_left = frame.pos.x - frame.width / 2.0;
      double max_top = frame.pos.y + frame.height / 2.0;
      double max_bottom = frame.pos.y - frame.height / 2.0;
      if(max_right > right)
      {
        right = max_right;
      }
      if(max_left < left)
      {
        left = max_left;
      }
      if(max_top > top)
      {
        top = max_top;
      }
      if(max_bottom < bottom)
      {
        bottom = max_bottom;
      }
    }
    return {(top - bottom), (right - left), {((right + left) / 2.0), ((top + bottom) / 2.0)}};
  }
}
void CompositeShape::move(const double dx, const double dy)
{
  for(size_t i = 0; i < quant_; i++)
  {
    arr_[i]->move(dx, dy);
  }
}
void CompositeShape::move(const point_t &point)
{
  point_t figure_center = getFrameRect().pos;
  for(size_t i = 0; i < quant_; i++)
  {
    arr_[i]->move(point.x - figure_center.x, point.y - figure_center.y);
  }
}
void CompositeShape::scale(const double mult)
{
  if (mult < 0.0)
  {
    throw std::invalid_argument("Invalid multiplier");
  }
  point_t figure_center = getFrameRect().pos;
  for(size_t i = 0; i < quant_; i++)
  {
    arr_[i]->move({mult * (arr_[i]->getFrameRect().pos.x - figure_center.x) + figure_center.x,
        mult * (arr_[i]->getFrameRect().pos.y - figure_center.y) + figure_center.y});
    arr_[i]->scale(mult);
  }
}
size_t CompositeShape::getQuantity() const
{
  return quant_;
}
std::shared_ptr<Shape> CompositeShape::getShape(const size_t number) const
{
  if(quant_ == 0)
  {
    throw std::out_of_range("Empty composite shape");
  }
  else if (number >= quant_)
  {
    throw std::invalid_argument("Not existing cell");
  }
  else
  {
    return arr_[number];
  }
}
void CompositeShape::getInfo() const
{
  if (quant_ != 0)
  {
    for (size_t i = 0; i < quant_; i++)
    {
      getShape(i)->getInfo();
    }
  }
  else
  {
    std::cout << "No shapes in compositeshape" << std::endl;
  }
}
}
