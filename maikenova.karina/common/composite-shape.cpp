#include <stdexcept>
#include <cmath>
#include "composite-shape.hpp"

maikenova::CompositeShape::CompositeShape() :
  amount_(0),
  complexShape_(nullptr),
  pos_({0.0, 0.0})
{
}

maikenova::CompositeShape::CompositeShape(const CompositeShape & newShape):
  amount_(newShape.getAmount()),
  complexShape_(new Shape*[amount_]),
  pos_(newShape.getFrameRect().pos)

{
  for (size_t i = 0; i < amount_; i++)
  {
    complexShape_[i] = newShape[i];
  }
}

maikenova::CompositeShape::CompositeShape(CompositeShape && newShape):
  amount_(newShape.getAmount()),
  complexShape_(newShape.complexShape_),
  pos_(newShape.getFrameRect().pos)
{
  newShape.amount_ = 0;
  newShape.complexShape_ = nullptr;
  newShape.pos_ = {0.0, 0.0};
}


maikenova::Shape * maikenova::CompositeShape::operator[](size_t index) const
{
  if (index >= amount_)
  {
    throw std::out_of_range("Index is out of range.");
  }
  return complexShape_[index];
}

maikenova::CompositeShape & maikenova::CompositeShape::operator=(const CompositeShape & newShape)
{
  if (this != & newShape)
  {
    pos_ = newShape.getFrameRect().pos;
    Shape ** newComp = new Shape*[newShape.amount_];
    amount_ = newShape.amount_;
    delete[] complexShape_;
    complexShape_ = newComp;

    for (size_t i = 0; i < newShape.getAmount(); i++)
    {
      complexShape_[i] = newShape[i];
    }
  }

  return * this;
}

maikenova::CompositeShape & maikenova::CompositeShape::operator=(CompositeShape && newShape)
{
  if (this != & newShape)
  {
    pos_ = newShape.getFrameRect().pos;
    delete[] complexShape_;
    complexShape_ = newShape.complexShape_;
    amount_ = newShape.amount_;
    newShape.amount_ = 0;
    newShape.complexShape_ = nullptr;
  }

  return * this;
}


double maikenova::CompositeShape::getArea() const
{
  double totalArea = 0;

  for (size_t i = 0; i < amount_; i++)
  {
    totalArea += complexShape_[i]->getArea();
  }

  return totalArea;
}

maikenova::rectangle_t maikenova::CompositeShape::getFrameRect() const
{
  if (amount_ == size_t(0))
  {
    throw std::invalid_argument("There are no components in composite shape.");
  }

  rectangle_t myRec = complexShape_[0]->getFrameRect();
  double minX = myRec.pos.x - myRec.width/2;
  double maxX = myRec.pos.x + myRec.width/2;
  double minY = myRec.pos.y - myRec.height/2;
  double maxY = myRec.pos.y + myRec.height/2;

  for (size_t i = 1; i < amount_; i++)
  {
    myRec = complexShape_[i]->getFrameRect();
    minX = std::min(minX, myRec.pos.x - myRec.width/2);
    maxX = std::max(maxX, myRec.pos.x + myRec.width/2);
    minY = std::min(minY, myRec.pos.y - myRec.height/2);
    maxY = std::max(maxY, myRec.pos.y + myRec.height/2);
  }

  myRec.width = maxX - minX;
  myRec.height = maxY - minY;
  myRec.pos = {(minX + myRec.width/2), (maxY - myRec.height/2)};

  return myRec;
}

void maikenova::CompositeShape::move(const point_t & newPos)
{
  const double dx = newPos.x - pos_.x;
  const double dy = newPos.y - pos_.y;

  for (size_t i = 0; i < amount_; i++)
  {
    complexShape_[i]->move(dx, dy);
  }

  pos_ = newPos;

}

void maikenova::CompositeShape::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;

  for (size_t i = 0; i < amount_; i++)
  {
    complexShape_[i]->move(dx, dy);
  }
}


void maikenova::CompositeShape::scale(const double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("Ratio must be positive.");
  }

  for (size_t i = 0; i < amount_; i++)
  {
    double dx = (complexShape_[i]->getPos().x - pos_.x)*(ratio - 1);
    double dy = (complexShape_[i]->getPos().y - pos_.y)*(ratio - 1);

    complexShape_[i]->scale(ratio);
    complexShape_[i]->move(dx, dy);
  }
}

void maikenova::CompositeShape::pushBack(Shape * newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("There is no shape to add.");
  }

  Shape ** newComp = new Shape*[amount_ + 1];

  if (amount_>0)
  {
    for (size_t i = 0; i < amount_; i++)
    {
      newComp[i] = complexShape_[i];
    }
  }

  newComp[amount_] = newShape;
  delete[] complexShape_;
  complexShape_ = newComp;
  amount_++;
  pos_ = getFrameRect().pos;
}

void maikenova::CompositeShape::remove(Shape * currentShape)
{
  if (amount_ <= 0)
  {
    throw std::invalid_argument("The composition contains no shapes.");
  }

  for (size_t i = 0; i < amount_; ++i)
  {
    if (complexShape_[i] == currentShape)
    {
      size_t index = i;
      Shape ** newComp = new Shape*[amount_ - 1];
      for (size_t i = 0; i < index; ++i)
      {
        newComp[i] = complexShape_[i];
      }
      for (size_t i = index; i < amount_ - 1; ++i)
      {
        newComp[i] = complexShape_[i + 1];
      }
      delete [] complexShape_;
      complexShape_ = newComp;
      amount_--;
      pos_ = getFrameRect().pos;
    }
    else
    {
      throw std::invalid_argument("This shape is not a part of composite shape.");
    }
  }
}

maikenova::point_t maikenova::CompositeShape::getPos() const
{
  return pos_;
}

size_t maikenova::CompositeShape::getAmount() const
{
  return amount_;
}

void maikenova::CompositeShape::rotate(double phi)
{
  point_t curPos = getPos();
  double radAngle = (phi*M_PI) / 180.0;
  for (size_t i = 0; i < amount_; i++)
  {
    complexShape_[i]->move({
      curPos.x + (complexShape_[i]->getPos().x - curPos.x) * cos(radAngle) - (complexShape_[i]->getPos().y - curPos.y) * sin(radAngle),
      curPos.y + (complexShape_[i]->getPos().y - curPos.y) * cos(radAngle) + (complexShape_[i]->getPos().x - curPos.x) * sin(radAngle)
    });

    complexShape_[i]->rotate(radAngle);
  }
}

maikenova::CompositeShape::~CompositeShape()
{
  delete[] complexShape_;
}
