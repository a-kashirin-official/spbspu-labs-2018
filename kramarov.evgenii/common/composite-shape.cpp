#include "composite-shape.hpp"
#include <stdexcept>

using namespace kramarov;

kramarov::CompositeShape::CompositeShape (Shape * shape):
  arr_(nullptr),
  qtt_(0)
{
  if (!shape)
  {
    throw std::invalid_argument ("Unexpected null pointer");
  }
  addShape (shape);
}

kramarov::CompositeShape::~CompositeShape()
{
  this->clear();
}

double kramarov::CompositeShape::getArea() const
{
  double area=0;
  for (int i=0; i < qtt_; i++)
  {
    area += arr_[i]->getArea();
  }
  return area;
}

rectangle_t kramarov::CompositeShape::getFrameRect() const
{
  if (qtt_ > 0)
  {
    double left = arr_[0]->getFrameRect().pos.x - arr_[0]->getFrameRect().width/2;
    double right = arr_[0]->getFrameRect().pos.x + arr_[0]->getFrameRect().width/2;
    double top = arr_[0]->getFrameRect().pos.y + arr_[0]->getFrameRect().height/2;
    double bottom = arr_[0]->getFrameRect().pos.y - arr_[0]->getFrameRect().height/2;

    for (int i=1; i < qtt_; i++)
    {
      if ((arr_[i]->getFrameRect().pos.x - arr_[i]->getFrameRect().width/2) < left)
      {
        left = arr_[i]->getFrameRect().pos.x - arr_[i]->getFrameRect().width/2;
      }
      if ((arr_[i]->getFrameRect().pos.x + arr_[i]->getFrameRect().width/2) > right)
      {
        right = arr_[i]->getFrameRect().pos.x + arr_[i]->getFrameRect().width/2;
      }
      if ((arr_[i]->getFrameRect().pos.y - arr_[i]->getFrameRect().height/2) < left)
      {
        bottom = arr_[i]->getFrameRect().pos.y - arr_[i]->getFrameRect().height/2;
      }
      if ((arr_[i]->getFrameRect().pos.y + arr_[i]->getFrameRect().height/2) < left)
      {
        top = arr_[i]->getFrameRect().pos.y + arr_[i]->getFrameRect().height/2;
      }
    }
    return {{(left + (right - left)/2), (bottom + (top - bottom)/2)}, (right - left), (top - bottom)};
  }
  else
  {
    return {{0, 0}, 0, 0};
  }
}

void kramarov::CompositeShape::move (const point_t & newLocation)
{
  const point_t curXY = getXY();
  move (newLocation.x - curXY.x, newLocation.y - curXY.y);
}

void kramarov::CompositeShape::move (const double dx, const double dy)
{
  for (int i=0; i < qtt_; i++)
  {
    arr_[i]->move (dx,dy);
  }
}

void kramarov::CompositeShape::scale (const double scaleRate)
{
  if (scaleRate < 0)
  {
    throw std::invalid_argument ("Rate must be above 0");
  }
  const point_t curXY = getXY();
  for (int i = 0; i < qtt_; i++)
  {
    const point_t iXY = arr_[i]->getXY();
    arr_[i]->move({curXY.x + scaleRate * (iXY.x - curXY.x),
                      curXY.y + scaleRate * (iXY.y - curXY.y)});
    arr_[i]->scale(scaleRate);
  }
}

int kramarov::CompositeShape::getQtt() const
{
  return qtt_;
}

point_t kramarov::CompositeShape::getXY() const
{
  return getFrameRect().pos;
}

void kramarov::CompositeShape::addShape (Shape * newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Pointer to no shape");
  }
  for (int i = 0; i < qtt_; ++i)
  {
    if (arr_[i] == newShape)
    {
      throw std::invalid_argument("Shape exists");
    }
  }
  Shape ** temp = new Shape * [qtt_ + 1];
  for (int i = 0; i < qtt_; ++i)
  {
    temp[i] = arr_[i];
  }
  temp[qtt_++] = newShape;
  delete [] arr_;
  arr_ = temp;
}

void kramarov::CompositeShape::deleteShape (const int numb)
{
  if (numb >= qtt_)
  {
    throw std::out_of_range("Out of range");
  }
  if (qtt_ <= 0)
  {
    throw std::out_of_range("Shapes list is empty");
  }
  if (numb < 0)
  {
    throw std::out_of_range("Out of range");
  }
  if ((qtt_ == 1) && (numb == 0))
  {
    clear();
    return;
  }
  Shape ** temp = new Shape * [qtt_ - 1];
  for (int i = 0; i < numb; ++i)
  {
    temp[i] = arr_[i];
  }
  for (int i = numb; i < qtt_ - 1; ++i)
  {
    temp[i] = arr_[i + 1];
  }
  delete [] arr_;
  arr_ = temp;
  qtt_--;
}

void kramarov::CompositeShape::clear()
{
  qtt_ = 0;
  delete [] arr_;
  arr_ = nullptr;
}

CompositeShape & kramarov::CompositeShape::operator=(const CompositeShape & rValue)
{
  if (this != &rValue)
  {
    delete [] arr_;
    arr_ = new Shape * [rValue.qtt_];
    for (int i = 0; i < rValue.getQtt(); ++i)
    {
      arr_[i] = rValue.arr_[i];
    }
    qtt_ = rValue.qtt_;
  }
  return *this;
}

Shape * kramarov::CompositeShape::operator[](const int i) const
{
  if (i >= qtt_)
  {
    throw std::out_of_range("Index overflow");
  }
  return arr_[i];
}
