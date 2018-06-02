#include <iostream>
#include <cmath>
#include "composite-shape.hpp"

using namespace starikov;

CompositeShape::CompositeShape(const std::shared_ptr<Shape> shape):
  sizeArray_(0),
  arrayShape_(nullptr)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Can't be nullptr!");
  }
  if ((shape->getFrameRect().height < 0.0) || (shape->getFrameRect().width < 0.0))
  {
    throw std::invalid_argument("Warning! Incorrect values...");
  }
  addShape(shape);
}
CompositeShape::CompositeShape():
sizeArray_(0),
arrayShape_(nullptr)
{
}
const Shape &CompositeShape::operator [](int index) const
{
  if (index >= sizeArray_)
  {
    throw std::out_of_range("Array's index is out of range!");
  }
  return *arrayShape_[index];
}
double CompositeShape::getArea() const
{
  return getFrameRect().width * getFrameRect().height;
}
rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t modelComposite = modelComposite_;
  rectangle_t modelRect;
  point_t centre, compositeCentre = {0,0};
  point_t max = {(arrayShape_[0]->getFrameRect().pos.x + arrayShape_[0]->getFrameRect().width / 2),(arrayShape_[0]->getFrameRect().pos.y + arrayShape_[0]->getFrameRect().height / 2)};
  point_t min = {(arrayShape_[0]->getFrameRect().pos.x - arrayShape_[0]->getFrameRect().width / 2),(arrayShape_[0]->getFrameRect().pos.y - arrayShape_[0]->getFrameRect().height / 2)};
  for(int i = 0; i < sizeArray_; i++)
  {
    modelRect = arrayShape_[i]->getFrameRect();
    compositeCentre.x += modelRect.pos.x;
    compositeCentre.y += modelRect.pos.y;
    if ((modelRect.pos.x + modelRect.width / 2) > max.x)
    {
      max.x = (modelRect.pos.x + modelRect.width / 2);
    }
    if ((modelRect.pos.y + modelRect.height / 2) > max.y)
    {
      max.y = (modelRect.pos.y + modelRect.height / 2);
    }
    if ((modelRect.pos.x - modelRect.width / 2) < min.x)
    {
      min.x = (modelRect.pos.x - modelRect.width / 2);
    }
    if ((modelRect.pos.y - modelRect.height / 2) < min.y)
    {
      min.y = (modelRect.pos.y - modelRect.height / 2);
    }
  }
  centre = {(compositeCentre.x / sizeArray_), (compositeCentre.y / sizeArray_)};
  modelComposite.height = (max.y - centre.y) + (centre.y - min.y);
  modelComposite.width = (max.x - centre.x) + (centre.x - min.x);
  modelComposite.pos.x = centre.x;
  modelComposite.pos.y = centre.y;
  return modelComposite;
}
void CompositeShape::move(const point_t &centre)
{
  modelComposite_.pos = centre;
}
void CompositeShape::move(const double offsetAxisX, const double offsetAxisY)
{
  modelComposite_.pos.x += offsetAxisX;
  modelComposite_.pos.y += offsetAxisY;
}
void CompositeShape::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Warning! Incorrect ratio...");
  }
  modelComposite_ = getFrameRect();
  modelComposite_.height *= ratio;
  modelComposite_.width *= ratio;
}
void CompositeShape::addShape(const std::shared_ptr<Shape> newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Cant't be nullptr!");
  }
  if ((newShape->getFrameRect().height < 0.0) || (newShape->getFrameRect().width < 0.0))
  {
    throw std::invalid_argument("Warning! Incorrect values...");
  }
  std::unique_ptr <std::shared_ptr <Shape> []> tempArray(new std::shared_ptr <Shape> [sizeArray_ + 1]);
  for (int i = 0; i < sizeArray_; i++)
  {
    tempArray[i] = arrayShape_[i];
  }
  tempArray[sizeArray_] = newShape;
  arrayShape_.swap(tempArray);
  sizeArray_++;
}
rectangle_t CompositeShape::getShapeInfo() const
{
  rectangle_t modelRect = modelComposite_;
  return modelRect;
}
void CompositeShape::rotate(const double angleDeg)
{
  angleDeg_ += angleDeg;
  if (angleDeg_ >= 360)
  {
    angleDeg_ = fmod(angleDeg_,360);
  }
  double angleRad = angleDeg_ * M_PI / 180;
  modelComposite_ = getFrameRect();
  point_t compositeCentre = modelComposite_.pos;
  for(int i = 0; i < sizeArray_; i++)
  {
    point_t shapeCentre = arrayShape_[i]->getFrameRect().pos;
    arrayShape_[i]->move({(compositeCentre.x + (((shapeCentre.x - compositeCentre.x) * fabs(cos(angleRad)))
      - ((shapeCentre.y - compositeCentre.y) * fabs(sin(angleRad))))),
          (compositeCentre.y + (((shapeCentre.x - compositeCentre.x) * fabs(sin(angleRad)))
            - ((shapeCentre.y - compositeCentre.y) * fabs(cos(angleRad)))))});
    arrayShape_[i]->rotate(angleDeg_);
  }
}
